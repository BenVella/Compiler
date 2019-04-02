//
// Created by bennet.vella on 25/03/2019.
//

#include <vector>
#include "Parser.h"

ASTStatementNode * Parser::ParseReturnStatement() {
    CurrentToken = m_Lexer.GetNextToken();
    auto expr_node = ParseExpression();
    if (!expr_node)
        return nullptr;

    /*auto node = new ASTReturnStatementNode();
    node->LHS = expr_node;
    return node; */ // ToDo: Uncomment when ASTReturnStatementNode has been implemented.
    return nullptr; // ToDo remove nullptr and return above node
}

Parser::~Parser() {

}

ASTExprNode * Parser::ParseExpression() {
    auto LHS = ParseUnaryExpr();
    if (!LHS)
        return nullptr;
    return ParseBinaryExpr(0,std::move(LHS));
}

ASTStatementNode *Parser::ParseIdStatement() {
    return nullptr;
}

ASTStatementNode * Parser::ParseIfStatement() {
    return nullptr;
}

ASTStatementNode * Parser::ParseStatement() {
    ASTStatementNode * node = nullptr;
    switch(CurrentToken.token_type) {
        case Lexer::TOK_KEY_RETURN:
            node = ParseReturnStatement();
            break;
        case Lexer::TOK_KEY_IF:
            node = ParseIfStatement();
            break;
        case Lexer::TOK_ID:
            node = ParseIdStatement();
            break;
        default:
            break;
    }
    return nullptr; // Todo remove this
}

ASTFuncPrototypeNode * Parser::ParseFunctionPrototype() {
    if (CurrentToken.token_type != Lexer::TOK_ID) {
        Error("Expecting function name");
        return nullptr;
    }

    std::string functionName = CurrentToken.id_name;
    auto functionParameters = std::vector<std::string>();

    CurrentToken = m_Lexer.GetNextToken();

    return nullptr; // ToDo remove nullptr;
}

ASTExprNode * Parser::ParseBinaryExpr(int p_Precedence,ASTExprNode * p_LHS) {
    while(true) {
        if (CurrentToken.token_type == Lexer::TOK_ARITHMETICOP) {
            float op_prec = CurrentToken.number_value;
            std::string op_sym = CurrentToken.id_name;

            CurrentToken = m_Lexer.GetNextToken();

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

ASTExprNode *Parser::ParseUnaryExpr() {
    return nullptr;
}

ASTExprNode *Parser::ParseIdentifierExpr() {
    return nullptr;
}

ASTExprNode *Parser::ParseParenthesisExpr() {
    return nullptr;
}

ASTExprNode *Parser::ParseNumberExpr() {
    return nullptr;
}

ASTExprNode *Parser::Error(const char *Str) {
    return nullptr;
}

