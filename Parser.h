//
// Created by bennet.vella on 25/03/2019.
//

#ifndef COMPILER_PARSER_H
#define COMPILER_PARSER_H

#include <map>
#include "Lexer.h"
#include "ASTNode/ASTExpressionNode/Expr.h"
#include "ASTNode/ASTStatementNode/ASTStatementNode.h"
#include "ASTNode/ASTStatementNode/ASTReturnNode.h"
#include "ASTNode/ASTStatementNode/ASTFunctionNode.h"

class Parser {
public:
    ASTNode * Parse();
    Parser(Lexer * p_Lexer);
    virtual ~Parser();

private:
    typedef std::map<std::string, Var> VarTable;

    Lexer* m_Lexer;
    Lexer::Token CurrentToken;

    //Helper Functions
    bool isToken(Lexer::TOK_TYPE p_type);
    void nextToken();

    ASTExprNode * Error (const char *Str);
    ASTExprNode * ParseExpression();
    ASTSimpleExprNode * ParseSimpleExpression();
    ASTTermExprNode * ParseTermExpression();
    ASTFactorExprNode * ParseFactorExpression();

    ASTExprNode * ParseNumberExpr();
    ASTExprNode * ParseParenthesisExpr();
    ASTExprNode * ParseIdentifierExpr();
    ASTExprNode * ParseUnaryExpr();
    //Expr * ParseBinaryExpr(int p_Precedence, Expr * p_LHS);
    ASTExprNode * ParseBinaryExpr();

    ASTStatementNode * ParseReturnStatement();
    ASTStatementNode * ParseAssignmentStatement();


    ASTFunctionNode * ParseFunctionPrototype();
    ASTStatementNode * ParseStatement();

    ASTStatementNode *ParseIdStatement();
    ASTStatementNode *ParseIfStatement();
};

#endif //COMPILER_PARSER_H
