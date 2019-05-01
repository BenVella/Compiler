//
// Created by bennet.vella on 25/03/2019.
//

#include <vector>
#include "Parser.h"
#include "ASTNode/Program.h"

#include "ASTNode/ASTExpressionNode/Binary/ExprBinOpAdd.h"
#include "ASTNode/ASTExpressionNode/Binary/ExprBinOpSub.h"
#include "ASTNode/ASTExpressionNode/Binary/ExprBinOppMul.h"
#include "ASTNode/ASTExpressionNode/Binary/ExprBinOppDiv.h"
#include "ASTNode/ASTExpressionNode/Unary/ExprUnOpNeg.h"
#include "ASTNode/ASTExpressionNode/Data/ExprConstInt.h"
#include "ASTNode/ASTExpressionNode/Data/ExprConstFloat.h"
#include "ASTNode/ASTExpressionNode/Data/ExprVar.h"
#include "ASTNode/ASTExpressionNode/Boolean/ExprBoolOpTrue.h"
#include "ASTNode/ASTExpressionNode/Boolean/ExprBoolOpFalse.h"

#include "ASTNode/ASTStatementNode/Assignment.h"
#include "ASTNode/ASTStatementNode/Return.h"
#include "ASTNode/ASTStatementNode/VarDeclare.h"
#include "ASTNode/ASTStatementNode/Print.h"
#include "ASTNode/ASTStatementNode/If.h"
#include "ASTNode/ASTStatementNode/Block.h"
#include "ASTNode/ASTStatementNode/For.h"
#include "ASTNode/ASTStatementNode/FunctionCall.h"
#include "ASTNode/ASTStatementNode/FunctionDeclare.h"
#include "ASTNode/ASTStatementNode/Param.h"
#include "ASTNode/ASTStatementNode/Params.h"

Parser::Parser(Lexer * p_lexer, VarTable &p_varTable): _lexer(p_lexer), _varTable(p_varTable) {
    nextToken();
}

// Handle Expressions Only
AST::Program* Parser::Parse(Lexer *p_lexer, VarTable& p_varTable) {
    auto *parser = new Parser(p_lexer, p_varTable);
    return parser->ParseProgram();
}

AST::Program* Parser::ParseProgram() {
    // right recursive rule
    // -> can be done as iteration
    auto* _program = new AST::Program();

    //std::vector<AST::Expr*> pExprs;
    while (true){
        if (auto *pStmt = ParseStatement()) {
            // Add to function if it's of type function
            auto* pFunc = dynamic_cast<AST::FunctionDeclare*>(pStmt);
            if (pFunc != nullptr)
                _program->functions->push_back(pFunc);

            _program->main_impl->push_back(pStmt);
        } else break;
        if (isToken(Lexer::TOK_EOF)) return _program;
    }
    // We didn't make it to EOF - delete all and return empty
    Error("End of File not reached!");

    for (auto *pStmt : *_program->main_impl) delete pStmt;
    for (auto *pFnc : *_program->functions) delete pFnc;

    _program->main_impl->clear();
    _program->functions->clear();

    return _program;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// Statements //////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

AST::Statement * Parser::ParseStatement() {
    AST::Statement * node = nullptr;
    switch(_currentToken.token_type) {
        case Lexer::TOK_ID:
            node = ParseIdentifierStatement();
            break;
        case Lexer::TOK_KEY_VAR:
            node = ParseVarDeclareStatement();
            break;
        case Lexer::TOK_KEY_PRINT:
            node = ParsePrintStatement();
            break;
        case Lexer::TOK_KEY_RETURN:
            node = ParseReturnStatement();
            break;
        case Lexer::TOK_KEY_IF:
            node = ParseIfStatement();
            break;
        case Lexer::TOK_KEY_FOR:
            node = ParseForStatement();
            break;
        case Lexer::TOK_KEY_FN:
            node = ParseFunctionDeclaration();
            break;
        case Lexer::TOK_OPEN_SCOPE:
            node = ParseFunctionDeclaration();
        default:
            break;
    }
    return node; //nullptr is not set
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// Expression //////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

AST::Expr* Parser::ParseExpr() {
    return ParseSumExpr();
}

AST::Expr* Parser::ParseSumExpr() {
    if (AST::Expr *pExpr1 = ParseMulExpr()) {
        return ParseSumExprRest(pExpr1);
    } else {
        Error ("When parsing Sum expecting a Mult Expr");
        return nullptr; // Error
    }
}

AST::Expr* Parser::ParseSumExprRest(AST::Expr *pExpr1) {
    while(true) {
        switch(_currentToken.token_type) {
            case Lexer::TOK_ARITHMETIC_PLUS:
                nextToken();
                if (AST::Expr *pExpr2 = ParseMulExpr()) {
                    pExpr1 = new AST::ExprBinOpAdd(pExpr1,pExpr2);
                } else {
                    delete pExpr1;
                    return nullptr; // Error
                }
                break;
            case Lexer::TOK_ARITHMETIC_MINUS:
                nextToken();
                if (AST::Expr *pExpr2 = ParseMulExpr()) {
                    pExpr1 = new AST::ExprBinOpSub(pExpr1,pExpr2);
                } else {
                    delete pExpr1;
                    return nullptr; // Error
                }
                break;
            case Lexer::TOK_SYNTAX_ERR:
                Error("SYNTAX ERROR! Unexpected Token in ParseSumExprRest()");
                delete pExpr1;
                return nullptr;
            default:
                return pExpr1;  // If we're not expanding this node with another, just return it as is
        }
    }
}
AST::Expr* Parser::ParseMulExpr()
{
    if (AST::Expr *pExpr1 = ParseUnExpr()) {
        return ParseMulExprRest(pExpr1);
    } else return nullptr; // ERROR!
}

AST::Expr* Parser::ParseMulExprRest(AST::Expr *pExpr1)
{
    // right recursive rule for left associative operators
    // -> can be done as iteration
    for (;;) {
        switch (_currentToken.token_type) {
            case Lexer::TOK_ARITHMETIC_MULT:
                nextToken(); // consume token
                if (AST::Expr *pExpr2 = ParseUnExpr()) {
                    pExpr1 = new AST::ExprBinOpMul(pExpr1, pExpr2);
                } else {
                    delete pExpr1;
                    return nullptr; // ERROR!
                }
                break;
            case Lexer::TOK_ARITHMETIC_DIV:
                nextToken(); // consume token
                if (AST::Expr *pExpr2 = ParseUnExpr()) {
                    pExpr1 = new AST::ExprBinOpDiv(pExpr1, pExpr2);
                } else {
                    delete pExpr1;
                    return nullptr; // ERROR!
                }
                break;
            case Lexer::TOK_SYNTAX_ERR:
                Error("SYNTAX ERROR! Unexpected Token in ParseSumExprRest()");
                delete pExpr1;
                return nullptr;
            default:
                return pExpr1;  // If we're not expanding this node with another, just return it as is
        }
    }
}

AST::Expr* Parser::ParseUnExpr()
{
    // right recursive rule for right associative operators
    // -> must be done as recursion
    switch (_currentToken.token_type) {
        case Lexer::TOK_ARITHMETIC_PLUS:
            nextToken(); // Unary plus has no effect, we skip it
            return ParseUnExpr();
        case Lexer::TOK_ARITHMETIC_MINUS:
            nextToken();
            if (AST::Expr *pExpr = ParseUnExpr()) {
                return new AST::ExprUnOpNeg(pExpr);
            } else return nullptr; // ERROR!
        default:
            return ParsePrimExpr();
    }
}

AST::Expr* Parser::ParsePrimExpr()
{
    AST::Expr *pExpr = nullptr;
    switch (_currentToken.token_type) {
        case Lexer::TOK_INT_NUMBER:
            pExpr = new AST::ExprConstInt(_currentToken.number_value);
            nextToken(); // consume int value token
            break;
        case Lexer::TOK_FLOAT_NUMBER:
            pExpr = new AST::ExprConstFloat(_currentToken.number_value);
            nextToken(); // consume float value token
            break;
        case Lexer::TOK_ID: {
            AST::Var &var = _varTable[_currentToken.id_name]; // find or create
            pExpr = new AST::ExprVar(_currentToken.id_name,&var);
            nextToken(); // consume id token
        } break;
        case Lexer::TOK_PUNC:
            if (_currentToken.id_name=="(") {
                nextToken(); // consume token
                if (!(pExpr = ParseExpr())) return nullptr; // ERROR!
                if (!isToken(Lexer::TOK_PUNC) || _currentToken.id_name != ")") {
                    delete pExpr;
                    Error ("Subexpression did not match a closing parenthesis");
                    return nullptr; // ERROR!
                }
            } else {
                Error ("Unexpected punctuation.  Was expecting opening parenthesis");
                return nullptr;
            }
            break;
        case Lexer::TOK_KEY_TRUE:
            pExpr = new AST::ExprBoolOpTrue();
            nextToken(); // consume true token
            break;
        case Lexer::TOK_KEY_FALSE:
            pExpr = new AST::ExprBoolOpFalse();
            nextToken(); // consume false token
            break;
        case Lexer::TOK_EOF:
            Error("SYNTAX ERROR: Premature EOF when parsing primary expression");
            return nullptr;
        case Lexer::TOK_SYNTAX_ERR:
        case Lexer::TOK_NUM_ERROR:
        default:
            Error("SYNTAX ERROR: Unexpected Primary Expression Token");
            return nullptr;
    }
    return pExpr;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// Statements //////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

AST::Statement* Parser::ParseIdentifierStatement() {
    // Get Identifier
    if (!isToken(Lexer::TOK_ID)) {
        Error("Expecting Id Token for Assignment Start");
        return nullptr;
    }
    std::string var_name = _currentToken.id_name;

    nextToken();

    if (isToken(Lexer::TOK_PUNC) && _currentToken.id_name=="(")
        return ParseFunctionCall(var_name);
    else if (isToken(Lexer::TOK_ASSIGNOP)) {
        return ParseAssignmentStatement(var_name);
    } else {
        Error ("After identifier expecting ' ( ' or ' = ' for function call / assignment respectively");
        return nullptr;
    }
}

AST::Statement * Parser::ParseAssignmentStatement() {
    // Get Identifier in preparation for ParseAssignment
    if (!isToken(Lexer::TOK_ID)) {
        Error("Expecting Id Token for Assignment Start");
        return nullptr;
    }
    std::string var_name = _currentToken.id_name;

    nextToken();

    return ParseAssignmentStatement(var_name);
}

AST::Statement * Parser::ParseAssignmentStatement(std::string p_name) {
    // Check for ' = ' symbol
    if (_currentToken.token_type != Lexer::TOK_ASSIGNOP) {
        Error("Expecting '=' while parsing an assignment statement");
        return nullptr;
    }

    // Handle expression
    nextToken(); // skip ' = '
    auto pExpr = ParseExpr();   // ToDo - Solve the self reference when assigning expression to itself
    _varTable[p_name].set(pExpr);
    auto pAssign = new AST::Assignment(std::move(p_name), pExpr);

    if (!isToken(Lexer::TOK_STMT_DELIMITER)) {
        Error ("Expecting ' ; ' to terminate statement");
        return nullptr;
    }
    nextToken(); // Consume delimeter
    return pAssign;
}

AST::Statement * Parser::ParseVarDeclareStatement() {
    // Check for Identifier
    nextToken();
    if (!isToken(Lexer::TOK_ID)) {
        Error ("Expecting identifier for Variable Declaration");
        return nullptr;
    }
    std::string var_name = _currentToken.id_name;

    // Check for ' : ' keyword
    nextToken();
    if (!isToken(Lexer::TOK_PUNC) || _currentToken.id_name != ":") {
        Error ("Expecting colon for Variable Declaration");
        return nullptr;
    }

    nextToken();
    std::string var_type;
    switch(_currentToken.token_type) {
        case Lexer::TOK_KEY_INT:
            var_type="int";
            break;
        case Lexer::TOK_KEY_FLOAT:
            var_type = "float";
            break;
        case Lexer::TOK_KEY_BOOL:
            var_type = "bool";
            break;
        default:
            Error("Expecting a type ( 'int' , 'float' or 'bool' for Variable Declaration");
            return nullptr;
    }

    nextToken();    // Check for ' = '
    if (!isToken(Lexer::TOK_ASSIGNOP)) {
        Error("Expecting ' = ' for Variable Declaration");
        return nullptr;
    }

    nextToken();    // Parse remaining expression and return VarDeclare AST Node
    AST::Expr *pExpr = ParseExpr();
    _varTable[var_name].set(pExpr);
//    AST::Var &var = _varTable[var_name];
//    var.set(pExpr);
    if (!isToken(Lexer::TOK_STMT_DELIMITER)) {
        Error("Expecting ' ; ' for termination of Variable Declaration");
        return nullptr;
    }
    nextToken();
    return new AST::VarDeclare(var_name,var_type,pExpr);
}

AST::Statement* Parser::ParsePrintStatement() {
    nextToken();
    if (auto* pExpr = ParseExpr()) {
        if (!isToken(Lexer::TOK_STMT_DELIMITER)) {
            Error ("Expecting ' ; ' to terminate print statement");
            return nullptr;
        }
        nextToken();
        return new AST::Print(pExpr);
    } else {
        Error ("Expecting expression for print statement");
        return nullptr;
    }
}

AST::Statement* Parser::ParseReturnStatement() {
    nextToken();
    if (auto *pExpr = ParseExpr()) {
        if (!isToken(Lexer::TOK_STMT_DELIMITER)) {
            Error ("Expecting ' ; ' to terminate print statement");
            return nullptr;
        }
        nextToken();
        return new AST::Return(pExpr);
    } else {
        Error ("Expecting expression for return statement");
        return nullptr;
    }
}

AST::Statement * Parser::ParseIfStatement() {
    nextToken();
    if (!isToken(Lexer::TOK_PUNC) || _currentToken.id_name != "(") {
        Error("Expecting open parenthesis for ' IF ' statement");
        return nullptr;
    }

    auto *pExpr = ParseExpr();

    if (!isToken(Lexer::TOK_PUNC) || _currentToken.id_name != ")") {
        Error("Expecting close parenthesis for ' IF ' statement");
        return nullptr;
    }

    // Get primary behaviour
    nextToken();
    if (auto *pBlock1 = ParseBlockStatement()) {
        if (isToken(Lexer::TOK_KEY_ELSE)) {
            nextToken(); // Consume else token
            if (auto *pBlock2 = ParseBlockStatement()) {
                return new AST::If(pExpr,pBlock1,pBlock2);
            } else {
                Error ("Expecting second Block code for ' IF ' statement!");
                return nullptr;
            }
        } else {
            return new AST::If(pExpr,pBlock1);
        }
    } else {
        Error ("Expecting first Block code for ' IF ' statement");
        return nullptr;
    }
}

AST::Statement* Parser::ParseForStatement() {
    nextToken();
    if (!isToken(Lexer::TOK_PUNC) || _currentToken.id_name != "(") {
        Error ("Expecting Open Parenthesis for function definition");
        return nullptr;
    }

    nextToken();

    AST::Statement *pVar = nullptr;
    if (isToken(Lexer::TOK_KEY_VAR)) {
        pVar = ParseVarDeclareStatement();
        nextToken();
    }

    if (!isToken(Lexer::TOK_STMT_DELIMITER)) {
        Error ("Expecting ' ; ' between for statement definitions");
    }

    nextToken();
    auto *pExpr = ParseExpr();

    if (!isToken(Lexer::TOK_STMT_DELIMITER)) {
        Error ("Expecting ' ; ' between for statement definitions");
    }

    nextToken();
    AST::Statement *pAssign = nullptr;
    if (!isToken(Lexer::TOK_PUNC) || _currentToken.id_name != ")") {
        // Handle Assignment
        if (!(pAssign = ParseAssignmentStatement())) {
            Error ("Expecting an Assignment statement or Close Parenthesis to end For definition");
            return nullptr;
        }
        nextToken();

    }

    nextToken(); // Consume ' ) ' token

    if (auto* pBlock = ParseBlockStatement()) {
        return new AST::For(pVar,pExpr,pAssign,pBlock);
    } else {
        Error ("For missing Block Statement");
        return nullptr;
    }
}

AST::Statement* Parser::ParseFunctionCall(const std::string& pName) {
    // Handle Params
    nextToken(); // skip ' = '
    auto *pParams = ParseParams();

    nextToken();
    if (!isToken(Lexer::TOK_PUNC) || _currentToken.id_name != ")") {
        Error ("Expecting Close Parenthesis for FunctionDeclare Call");
        return nullptr;
    }

    nextToken(); // Consume delimeter
    return new AST::FunctionCall(pName,pParams);
}

AST::Statement* Parser::ParseFunctionDeclaration() {
    nextToken(); // Consume TOK_KEY_FN
    if (!isToken(Lexer::TOK_ID)) {
        Error ("Expecting identifier for FunctionDeclare Declaration");
        return nullptr;
    }
    std::string pName = _currentToken.id_name;

    nextToken();
    if (!isToken(Lexer::TOK_PUNC) || _currentToken.id_name != "(") {
        Error ("Expecting Open Parenthesis for FunctionDeclare Delcaration");
        return nullptr;
    }

    nextToken();
    auto *pParams = ParseParams();

    if (!isToken(Lexer::TOK_PUNC) || _currentToken.id_name != ")") {
        Error ("Expecting Close Parenthesis for FunctionDeclare Delcaration");
        return nullptr;
    }

    nextToken();
    if (!isToken(Lexer::TOK_PUNC) || _currentToken.id_name != ":") {
        Error ("Expecting Colon for FunctionDeclare Delcaration");
        return nullptr;
    }

    nextToken();
    std::string pType;
    switch(_currentToken.token_type) {
        case Lexer::TOK_KEY_INT:
            pType="int";
            break;
        case Lexer::TOK_KEY_FLOAT:
            pType = "float";
            break;
        case Lexer::TOK_KEY_BOOL:
            pType = "bool";
            break;
        default:
            Error("Expecting a type ( 'int' , 'float' or 'bool' for Variable Declaration");
            return nullptr;
    }

    nextToken();
    if (auto  *pBlock = ParseBlockStatement()) {
        return new AST::FunctionDeclare(std::move(pName),pParams,std::move(pType),pBlock);
    } else {
        Error("Expecting a block statement for FunctionDeclare Defintion");
        return nullptr;
    }
}

AST::Statement* Parser::ParseParams() {
    auto* pParams = new AST::Params();
    while (true){
        if (auto* pSingle = ParseSingleParam()) {
            pParams->addParam(pSingle);

            if (!isToken(Lexer::TOK_PUNC) || _currentToken.id_name!= ",") {
                break;
            } else {
                nextToken(); // Consume ' , ' and loop again
            }
        }
    }
    return pParams;
}

AST::Statement* Parser::ParseSingleParam() {
    if (!isToken(Lexer::TOK_ID)) {
        Error ("Expecting identifier for new Parameter");   // This might not be in Error, simply no more params to parse
        return nullptr;
    }
    std::string pName = _currentToken.id_name;

    nextToken();
    if (!isToken(Lexer::TOK_PUNC) || _currentToken.id_name != ":") {
        Error ("Expecting ' : ' for Parameter");
        return nullptr;
    }

    nextToken();
    std::string pType;
    switch(_currentToken.token_type) {
        case Lexer::TOK_KEY_INT:
            pType="int";
            break;
        case Lexer::TOK_KEY_FLOAT:
            pType = "float";
            break;
        case Lexer::TOK_KEY_BOOL:
            pType = "bool";
            break;
        default:
            Error("Expecting a type ( 'int' , 'float' or 'bool' for Variable Declaration");
            return nullptr;
    }
    nextToken(); //Consume pType tokekn
    return new AST::Param(pName,pType);
}

AST::Statement* Parser::ParseBlockStatement() {
    if (!isToken(Lexer::TOK_OPEN_SCOPE)) {
        Error ("Expecting ' { ' to begin statement block");
        return nullptr;
    }
    nextToken(); // consume Open Scope statement

    auto* pBlock = new AST::Block();
    while (true) {
        if (auto* pStmt = ParseStatement()) {
            pBlock->addStatement(pStmt);
        } else {
            if (!isToken(Lexer::TOK_CLOSE_SCOPE)) {
                Error ("Expecting ' } ' to close statement block");
                return nullptr;
            }
            nextToken(); // consume close scope token
            return pBlock;
        }
    }
}

//////////////////////////////////////////
///////////// HELPER METHODS /////////////
//////////////////////////////////////////

AST::Expr * Parser::Error(const char *str) {
    std::cerr << "[ERROR]: " << str << "; [Token]: " << _currentToken.ToString() << "; [Line]: " << _lexer->getLine() << std::endl;
    return nullptr;
}

// Helper Methods
bool Parser::isToken(Lexer::TOK_TYPE p_type) {
    return _currentToken.token_type == p_type;
}

void Parser::nextToken() {
    _currentToken = _lexer->GetNextToken();
}