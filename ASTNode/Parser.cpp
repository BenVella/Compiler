//
// Created by bennet.vella on 25/03/2019.
//

#include "Parser.h"
#include "ASTStatementNode.h"

ASTStatementNode * Parser::ParseReturnStatement() {
    CurrentToken = Lex.GetNextToken();
    auto expr_node = ParseExpression();
    if (!expr_node)
        return nullptr;

    auto node = new ASTReturnStatementNode();
    node->LHS = expr_node;
    return node;
}

ASTExprNode * Parser::ParseExpression() {
    auto LHS = ParseUnaryExpr();
    if (!LHS)
        return nullptr;
    return ParseBinaryExpr(0,std::move(LHS));
}

ASTStatementNode * Parser:ParseStatement() {
    ASTStatementNode * node = nullptr;
    switch(CurrentToken.token_type) {
        case Lexer::TOK_RETURN:
            node = ParseReturnStatement();
            break;
        case Lexer::TOK_IF:
            node = ParseIfStatement();
            break;
        case Lexer::TOK_ID:
            node = ParseIdStatement();
            break;
        default:
            break;
    }
};

ASTFuncPrototypeNode * Parser::ParsEFunctionPrototype() {
    if (CurrentToken.token_type != Lexer::TOK_ID) {
        Error("Expecting function name");
        return nullptr;
    }

    std::string functionName = CurrentToken.id_name;
    auto functionParameters = std::vector<std::string>();

    CurrentToken = Lex.GetNextToken();

}

ASTExprNode * Parser::ParseBinaryExpr(int p_Precedence,ASTExprNode * p_LHS) {
    while(true) {
        if (CurrentToken.token_type == Lexer::TOK_ARITHMETICOP) {
            float op_prec = CurrentToken.number_value;
            std::string op_sym = CurrentToken.id_name;

            CurrentToken = Lex.GetNextToken();

            auto RHS = ParseUnaryExpr();

            if (!RHS)
                return nullptr;
            float nxt_op_prec = CurrentToken.number_value;

            if (op_prec < nxt_op_prec) {
                RHS = ParseBinaryExpr(op_prec+1, RHS);
                if (!RHS) {

                }
            }

        }
    }
}