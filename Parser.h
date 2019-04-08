//
// Created by bennet.vella on 25/03/2019.
//

#ifndef COMPILER_PARSER_H
#define COMPILER_PARSER_H

#include "Lexer.h"
#include "ASTNode/ASTExprNode.h"
#include "ASTNode/ASTStatementNode/ASTStatementNode.h"
#include "ASTNode/ASTFuncPrototypeNode.h"
#include "ASTNode/ASTStatementNode/ASTReturnNode.h"

class Parser {
public:
    ASTNode * Parse();
    Parser(Lexer * p_Lexer);
    virtual ~Parser();

private:
    Lexer* m_Lexer;
    Lexer::Token CurrentToken;

    ASTExprNode * Error (const char *Str);
    ASTExprNode * ParseExpression();
    ASTExprNode * ParseNumberExpr();
    ASTExprNode * ParseParenthesisExpr();
    ASTExprNode * ParseIdentifierExpr();
    ASTExprNode * ParseUnaryExpr();
    ASTExprNode * ParseBinaryExpr(int p_Precedence, ASTExprNode * p_LHS);

    ASTStatementNode * ParseReturnStatement();


    ASTFuncPrototypeNode * ParseFunctionPrototype();
    ASTStatementNode * ParseStatement();

    ASTStatementNode *ParseIdStatement();
    ASTStatementNode *ParseIfStatement();
};

#endif //COMPILER_PARSER_H
