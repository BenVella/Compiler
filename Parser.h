//
// Created by bennet.vella on 25/03/2019.
//

#ifndef COMPILER_PARSER_H
#define COMPILER_PARSER_H

#include "Lexer.h"
#include "ASTNode/ASTExpressionNode/ASTExprNode.h"
#include "ASTNode/ASTStatementNode/ASTStatementNode.h"
#include "ASTNode/ASTStatementNode/ASTReturnNode.h"
#include "ASTNode/ASTStatementNode/ASTFunctionNode.h"

class Parser {
public:
    ASTNode * Parse();
    Parser(Lexer * p_Lexer);
    virtual ~Parser();

private:
    Lexer* m_Lexer;
    Lexer::Token CurrentToken;

    //Helper Functions
    bool isToken(Lexer::TOK_TYPE p_type);
    void nextToken();

    ASTExprNode * Error (const char *Str);
    ASTExprNode * ParseExpression();
    ASTExprNode * ParseSimpleExpression();
    ASTExprNode * ParseTermExpression();
    ASTExprNode * ParseFactorExpression();

    ASTExprNode * ParseNumberExpr();
    ASTExprNode * ParseParenthesisExpr();
    ASTExprNode * ParseIdentifierExpr();
    ASTExprNode * ParseUnaryExpr();
    //ASTExprNode * ParseBinaryExpr(int p_Precedence, ASTExprNode * p_LHS);
    ASTExprNode * ParseBinaryExpr();

    ASTStatementNode * ParseReturnStatement();
    ASTStatementNode * ParseAssignmentStatement();


    ASTFunctionNode * ParseFunctionPrototype();
    ASTStatementNode * ParseStatement();

    ASTStatementNode *ParseIdStatement();
    ASTStatementNode *ParseIfStatement();
};

#endif //COMPILER_PARSER_H
