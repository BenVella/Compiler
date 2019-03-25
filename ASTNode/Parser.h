//
// Created by bennet.vella on 25/03/2019.
//

#ifndef COMPILER_PARSER_H
#define COMPILER_PARSER_H

#include "../Lexer.h"
#include "ASTExprNode.h"

class Parser {
public:
    ASTNode * Parse();

private:
    Lexer Lex;
    Lexer::Token CurrentToken;

    ASTExprNode * Error (const char *Str);
    ASTExprNode * ParseNumberExpr();
    ASTExprNode * ParseParenthesisExpr();
    ASTExprNode * ParseIdentifierExpr();
    ASTExprNode * ParseUnaryExpr();
    ASTExprNode * ParseBinaryExpr(int p_Precedence, ASTExprNode * p_LHS);
};

#endif //COMPILER_PARSER_H
