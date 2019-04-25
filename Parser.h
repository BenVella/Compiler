//
// Created by bennet.vella on 25/03/2019.
//

#ifndef COMPILER_PARSER_H
#define COMPILER_PARSER_H

#include <map>
#include "Lexer.h"
#include "ASTNode/ASTExpressionNode/Data/Var.h"
#include "ASTNode/ASTExpressionNode/Expr.h"
#include "ASTNode/ASTStatementNode/Statement.h"
#include "ASTNode/ASTStatementNode/Function.h"
#include "ASTNode/Program.h"

class Parser {
private:
    typedef std::map<std::string, AST::Var> VarTable;

    Parser(Lexer *p_lexer);
    Lexer* m_Lexer;
    Lexer::Token CurrentToken;
    VarTable m_varTable;    // ToDo this might need to be moved outside to main in order to not lose references

    // Helper Functions
    bool isToken(Lexer::TOK_TYPE p_type);
    void nextToken();

    // Expression Parsing
    AST::Expr* Error (const char *str);
    AST::Program* ParseProgram();
    AST::Expr* ParseExpr();
    AST::Expr* ParseSumExpr();
    AST::Expr* ParseSumExprRest(AST::Expr *pExpr1);
    AST::Expr* ParseMulExpr();
    AST::Expr* ParseMulExprRest(AST::Expr *pExpr1);
    AST::Expr* ParseUnExpr();
    AST::Expr* ParsePrimExpr();

    // Statement Parsing
    AST::Statement* ParseAssignmentStatement();
    AST::Statement* ParseVarDeclareStatement();
    AST::Statement* ParsePrintStatement();
    AST::Statement* ParseReturnStatement();
    AST::Statement* ParseIfStatement();
    AST::Statement* ParseForStatement();
    AST::Statement* ParseStatement();
    AST::Statement* ParseBlockStatement();
    AST::Statement* ParseIdentifierStatement();

    // Function Parsing
    AST::Function* ParseFunctionPrototype();

public:
    static AST::Program* Parse(Lexer *p_lexer);
    virtual ~Parser() {}
};

#endif //COMPILER_PARSER_H