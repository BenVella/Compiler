//
// Created by bennet.vella on 25/03/2019.
//

#include <vector>
#include "Parser.h"
#include "ASTNode/Program.h"
#include "ASTNode/ASTStatementNode/AssignmentStatement.h"
#include "ASTNode/ASTStatementNode/Return.h"
#include "ASTNode/ASTExpressionNode/Binary/ExprBinOpAdd.h"
#include "ASTNode/ASTExpressionNode/Binary/ExprBinOpSub.h"
#include "ASTNode/ASTExpressionNode/Binary/ExprBinOppMul.h"
#include "ASTNode/ASTExpressionNode/Binary/ExprBinOppDiv.h"
#include "ASTNode/ASTExpressionNode/Unary/ExprUnOpNeg.h"
#include "ASTNode/ASTExpressionNode/Data/ExprConstInt.h"
#include "ASTNode/ASTExpressionNode/Data/ExprConstFloat.h"
#include "ASTNode/ASTExpressionNode/Data/ExprVar.h"

Parser::Parser(Lexer * p_lexer): m_Lexer(p_lexer) {
    nextToken();
}

// Handle Expressions Only
AST::Program* Parser::Parse(Lexer *p_lexer) {
    Parser *parser = new Parser(p_lexer);
    return parser->ParseProgram();
}

AST::Program* Parser::ParseProgram() {
    // right recursive rule
    // -> can be done as iteration
    auto *pNodes = new AST::Program();

    //std::vector<AST::Expr*> pExprs;
    while (true){
        if (AST::Expr *pExpr = ParseExpr()) {
            //pExprs.push_back(pExpr);
            pNodes->tempExprs->push_back(pExpr);
        } else break;
        // special error checking for missing ';' (usual error)
        if (!isToken(Lexer::TOK_PUNC) || CurrentToken.id_name != ";") {
            std::cerr << "SYNTAX ERROR: Semicolon expected!" << std::endl;
            break;
        }
        nextToken(); // consume semicolon
        if (isToken(Lexer::TOK_EOF)) return pNodes;
    }
    // We didn't make it to EOF - delete all and return empty
    Error("End of File not reached!");
    for (AST::Expr *pExpr : *pNodes->tempExprs) delete pExpr;
    pNodes->tempExprs->clear();
    return pNodes;
}

//////////////////////////////////////
///////////// EXPRESSION /////////////
//////////////////////////////////////

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
            pExpr = new AST::ExprVar(&var);
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

//////////////////////////////////////
///////////// STATEMENTS /////////////
//////////////////////////////////////

AST::Statement * Parser::ParseAssignmentStatement() {
    // Get Identifier
    if (!isToken(Lexer::TOK_ID)) {
        Error("Expecting Id Token for Assignment Start");
        return nullptr;
    }
    std::string var_name = CurrentToken.id_name;

    // Check for ' = ' symbol
    nextToken();
    if (CurrentToken.token_type != Lexer::TOK_ASSIGNOP) {
        Error("Expecting '=' while parsing an assignment statement");
        return nullptr;
    }

    // Handle expression
    nextToken(); // skip ' = '
    auto pExpr = ParseExpr();
    auto ass_node = new AST::AssignmentStatement(var_name.c_str(), pExpr);

    return ass_node;
}

AST::Statement * Parser::ParseVarDeclareStatement() {
    // Check for 'var' keyword
    if (!isToken(Lexer::TOK_KEY_VAR)) {
        Error("Expecting 'var' keyword for Variable Declaration");
        return nullptr;
    }

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
    switch(CurrentToken.token_type) {
        case Lexer::TOK_KEY_INT:
            nextToken();
            if (!isToken(Lexer::TOK_ASSIGNOP)) {
                Error ("Expecting ' = ' for Variable Declaration");
                return nullptr;
            }
            nextToken();
            auto pExpr = ParseExpr();
            AST::Var &var = m_varTable[var_name];
            // Todo create a variable declaration object and store data within it, and update var table
    }

    CurrentToken = m_Lexer->GetNextToken();
    if (CurrentToken.token_type != Lexer::TOK_ASSIGNOP) {
        Error("Expecting '=' while parsing an assignment statement");
        return nullptr;
    }
    CurrentToken = m_Lexer->GetNextToken();
    auto pExpr = ParseExpr();
    auto ass_node = new AST::AssignmentStatement(var_name.c_str(), pExpr);
    return ass_node;
}

AST::Statement * Parser::ParseReturnStatement() {
    CurrentToken = m_Lexer->GetNextToken();
    auto expr_node = ParseExpr();
    if (!expr_node)
        return nullptr;

    auto node = new AST::Return(expr_node);
    return node;
}

AST::Statement *Parser::ParseIdStatement() {
    return nullptr;
}

AST::Statement * Parser::ParseIfStatement() {
    CurrentToken = m_Lexer->GetNextToken();
    if (isToken(Lexer::TOK_PUNC) && CurrentToken.id_name == "(") {
        auto condition = ParseExpr();

        CurrentToken = m_Lexer->GetNextToken();
        if (isToken(Lexer::TOK_PUNC) && CurrentToken.id_name == ")") {
            // auto thenBlock = ParseBlock();   // ToDo create a block node?
        }
    } else {
        Error ("Expecting open bracket for if-condition-start");
    }
    return nullptr;
}

AST::Statement * Parser::ParseStatement() {
    AST::Statement * node = nullptr;
    switch(CurrentToken.token_type) {
        case Lexer::TOK_KEY_IF:
            node = ParseIfStatement();
            break;
        case Lexer::TOK_KEY_RETURN:
            node = ParseReturnStatement();
            break;
        case Lexer::TOK_ID:
            node = ParseIdStatement();
            break;
        default:
            break;
    }
    return node; //nullptr is not set
}

AST::Function * Parser::ParseFunctionPrototype() {
    if (CurrentToken.token_type != Lexer::TOK_ID) {
        Error("Expecting function name");
        return nullptr;
    }

    std::string functionName = CurrentToken.id_name;
    auto functionParameters = std::vector<std::string>();

    CurrentToken = m_Lexer->GetNextToken();

    return nullptr; // ToDo remove nullptr;
}

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


