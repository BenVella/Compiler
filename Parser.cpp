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

Parser::Parser(Lexer * p_lexer, VarTable &p_varTable): m_Lexer(p_lexer), m_varTable(p_varTable) {
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
    auto *pNodes = new AST::Program();

    //std::vector<AST::Expr*> pExprs;
    while (true){
        if (auto *pStmt = ParseStatement()) {
            pNodes->main_impl->push_back(pStmt);
        } else break;
        /*// special error checking for missing ';' (usual error)
        if (!isToken(Lexer::TOK_STMT_DELIMITER)) {
            std::cerr << "SYNTAX ERROR: Semicolon expected!" << std::endl;
            break;
        }*/
        if (isToken(Lexer::TOK_EOF)) return pNodes;
    }
    // We didn't make it to EOF - delete all and return empty
    Error("End of File not reached!");
    for (auto *pStmt : *pNodes->main_impl) delete pStmt;
    pNodes->main_impl->clear();
    return pNodes;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// Statements //////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

AST::Statement * Parser::ParseStatement() {
    AST::Statement * node = nullptr;
    switch(CurrentToken.token_type) {
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
        switch(CurrentToken.token_type) {
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
        switch (CurrentToken.token_type) {
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
    switch (CurrentToken.token_type) {
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
    switch (CurrentToken.token_type) {
        case Lexer::TOK_INT_NUMBER:
            pExpr = new AST::ExprConstInt(CurrentToken.number_value);
            nextToken();
            break;
        case Lexer::TOK_FLOAT_NUMBER:
            pExpr = new AST::ExprConstFloat(CurrentToken.number_value);
            nextToken(); // consume token
            break;
        case Lexer::TOK_ID: {
            AST::Var &var = m_varTable[CurrentToken.id_name]; // find or create
            pExpr = new AST::ExprVar(CurrentToken.id_name,&var);
            nextToken(); // consume token
        } break;
        case Lexer::TOK_PUNC:
            if (CurrentToken.id_name=="(") {
                nextToken(); // consume token
                if (!(pExpr = ParseExpr())) return nullptr; // ERROR!
                if (!isToken(Lexer::TOK_PUNC) || CurrentToken.id_name != ")") {
                    delete pExpr;
                    Error ("Subexpression did not match a closing parenthesis!");
                    return nullptr; // ERROR!
                }
            } else {
                Error ("Unexpected punctuation.  Was expecting opening parenthesis");
            }
            break;
        case Lexer::TOK_EOF:
            Error("SYNTAX ERROR: Premature EOF when parsing primary expression!");
            break;
        case Lexer::TOK_SYNTAX_ERR:
        case Lexer::TOK_NUM_ERROR:
            Error("SYNTAX ERROR: Unexpected character!");
            break;
        default:
            Error("SYNTAX ERROR: Unexpected token!");
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
    std::string var_name = CurrentToken.id_name;

    nextToken();

    if (isToken(Lexer::TOK_PUNC) && CurrentToken.id_name=="(")
        return ParseFunctionCall(var_name);
    else if (isToken(Lexer::TOK_ASSIGNOP)) {
        return ParseAssignmentStatement(var_name);
    } else {
        Error ("After identifier expecting ' ( ' or ' = ' for function call / assignment respectively");
        return nullptr;
    }
}

AST::Statement * Parser::ParseAssignmentStatement(std::string p_name) {
    // Check for ' = ' symbol
    if (CurrentToken.token_type != Lexer::TOK_ASSIGNOP) {
        Error("Expecting '=' while parsing an assignment statement");
        return nullptr;
    }

    // Handle expression
    nextToken(); // skip ' = '
    auto pExpr = ParseExpr();   // ToDo - Solve the self reference when assigning expression to itself
    m_varTable[p_name].set(pExpr);
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
    std::string var_name = CurrentToken.id_name;

    // Check for ' : ' keyword
    nextToken();
    if (!isToken(Lexer::TOK_PUNC) || CurrentToken.id_name != ":") {
        Error ("Expecting colon for Variable Declaration");
        return nullptr;
    }

    nextToken();
    std::string var_type;
    switch(CurrentToken.token_type) {
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
    m_varTable[var_name].set(pExpr);
//    AST::Var &var = m_varTable[var_name];
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
    auto pExpr = ParseExpr();

    return new AST::Print(pExpr);
}

AST::Statement* Parser::ParseReturnStatement() {
    nextToken();
    auto *pExpr = ParseExpr();
    if (!pExpr)
        return nullptr;
    return new AST::Return(pExpr);
}

AST::Statement * Parser::ParseIfStatement() {
    nextToken();
    if (!isToken(Lexer::TOK_PUNC) || CurrentToken.id_name != "(") {
        Error("Expecting open parenthesis for ' IF ' statement");
        return nullptr;
    }

    auto *pExpr = ParseExpr();

    if (!isToken(Lexer::TOK_PUNC) || CurrentToken.id_name != ")") {
        Error("Expecting close parenthesis for ' IF ' statement");
        return nullptr;
    }

    // Get primary behaviour
    nextToken();
    if (auto *pBlock1 = ParseBlockStatement()) {
        nextToken();
        if (!isToken(Lexer::TOK_CLOSE_SCOPE)) {
            Error ("Expecting ' } ' to close Primary Block code for ' IF ' statement!");
            return nullptr;
        }
        nextToken();
        if (isToken(Lexer::TOK_KEY_ELSE)) {
            nextToken();
            if (auto *pBlock2 = ParseBlockStatement()) {
                if (!isToken(Lexer::TOK_STMT_DELIMITER)) {
                    Error("Expecting delimeter to end statement");
                    return nullptr;
                }
                nextToken(); // consume delimeter
                if (!isToken(Lexer::TOK_CLOSE_SCOPE)) {
                    Error("Expecting ' } ' to Close Block Scope");
                    return nullptr;
                }
                nextToken();
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
    if (!isToken(Lexer::TOK_PUNC) || CurrentToken.id_name != "(") {
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

    nextToken();
    if (!isToken(Lexer::TOK_STMT_DELIMITER)) {
        Error ("Expecting ' ; ' between for statement definitions");
    }

    nextToken();
    AST::Statement *pAssign = nullptr;
    if (!isToken(Lexer::TOK_PUNC) || CurrentToken.id_name != ")") {
        // Get Identifier
        if (!isToken(Lexer::TOK_ID)) {
            Error("Expecting Id Token for Assignment Start");
            return nullptr;
        }
        std::string var_name = CurrentToken.id_name;

        nextToken();

        if (!(pAssign = ParseAssignmentStatement(var_name))) {
            Error ("Expecting an Assignment statement or Close Parenthesis to end For definition");
            return nullptr;
        }

        nextToken();
        if (isToken(Lexer::TOK_PUNC) && CurrentToken.id_name == ")") {
            return new AST::For(pVar,pExpr,pAssign);
        } else {
            Error ("Expecting close parenthesis to end for definition");
            return nullptr;
        }
    } else {
        return new AST::For(pVar,pExpr,pAssign);
    }
}

AST::Statement* Parser::ParseFunctionCall(const std::string& pName) {
    // Handle Params
    nextToken(); // skip ' = '
    auto *pParams = ParseParams();

    nextToken();
    if (!isToken(Lexer::TOK_PUNC) || CurrentToken.id_name != ")") {
        Error ("Expecting Close Parenthesis for FunctionDeclare Call");
        return nullptr;
    }

    nextToken(); // Consume delimeter
    return new AST::FunctionCall(pName,pParams);
}

AST::Statement* Parser::ParseFunctionDeclaration() {
    if (!isToken(Lexer::TOK_ID)) {
        Error ("Expecting identifier for FunctionDeclare Declaration");
        return nullptr;
    }
    std::string pName = CurrentToken.id_name;

    nextToken();
    if (!isToken(Lexer::TOK_PUNC) || CurrentToken.id_name != "(") {
        Error ("Expecting Open Parenthesis for FunctionDeclare Delcaration");
        return nullptr;
    }

    nextToken();
    auto *pParams = ParseParams();

    nextToken();
    if (!isToken(Lexer::TOK_PUNC) || CurrentToken.id_name != ")") {
        Error ("Expecting Close Parenthesis for FunctionDeclare Delcaration");
        return nullptr;
    }

    nextToken();
    if (!isToken(Lexer::TOK_PUNC) || CurrentToken.id_name != ":") {
        Error ("Expecting Colon for FunctionDeclare Delcaration");
        return nullptr;
    }

    nextToken();
    std::string pType;
    switch(CurrentToken.token_type) {
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
        } else {
            return pParams;
        }
    }
}

AST::Statement* Parser::ParseSingleParam() {
    if (!isToken(Lexer::TOK_ID)) {
        Error ("Expecting identifier for new Parameter");   // This might not be in Error, simply no more params to parse
        return nullptr;
    }
    std::string pName = CurrentToken.id_name;

    nextToken();
    if (!isToken(Lexer::TOK_PUNC) || CurrentToken.id_name != ":") {
        Error ("Expecting ' : ' for Parameter");
        return nullptr;
    }

    nextToken();
    std::string pType;
    switch(CurrentToken.token_type) {
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

    return new AST::Param(pName,pType);
}

AST::Statement* Parser::ParseBlockStatement() {
    if (!isToken(Lexer::TOK_OPEN_SCOPE)) {
        Error ("Expecting ' { ' to begin statement block");
        return nullptr;
    }

    nextToken();
    auto* pBlock = new AST::Block();
    while (true) {
        if (auto* pStmt = ParseStatement()) {
            pBlock->addStatement(pStmt);
        } else {
            return pBlock;
        }
    }
}

//////////////////////////////////////////
///////////// HELPER METHODS /////////////
//////////////////////////////////////////

AST::Expr * Parser::Error(const char *str) {
    std::cerr << "[ERROR]: " << str << std::endl;
    return nullptr;
}

// Helper Methods
bool Parser::isToken(Lexer::TOK_TYPE p_type) {
    return CurrentToken.token_type == p_type;
}

void Parser::nextToken() {
    CurrentToken = m_Lexer->GetNextToken();
}