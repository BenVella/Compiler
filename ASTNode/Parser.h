//
// Created by bennet.vella on 25/03/2019.
//

#ifndef COMPILER_PARSER_H
#define COMPILER_PARSER_H

#include "../Lexer.h"
#include "ASTExprNode.h"
#include "ASTStatementNode.h"
#include "ASTFuncPrototypeNode.h"
#include "ASTReturnStatementNode.h"

class Parser {
public:
    ASTNode * Parse();

    virtual ~Parser();

private:
    Lexer Lex;
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
};

#endif //COMPILER_PARSER_H
