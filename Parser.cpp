//
// Created by bennet.vella on 25/03/2019.
//

#include <vector>
#include "Parser.h"
#include "ASTNode/ASTProgramNode.h"

Parser::Parser(Lexer * p_Lexer) {
    m_Lexer = p_Lexer;
}

Parser::~Parser() {

}

ASTNode *Parser::Parse() {
    ASTNode * root = new ASTProgramNode();

    CurrentToken = m_Lexer->GetNextToken();


    //
}


ASTStatementNode * Parser::ParseReturnStatement() {
    CurrentToken = m_Lexer->GetNextToken();
    auto expr_node = ParseExpression();
    if (!expr_node)
        return nullptr;

    auto node = new ASTReturnNode();
    node->LHS = expr_node;
    return node;
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
    CurrentToken = m_Lexer->GetNextToken();
    if (CurrentToken.token_type == Lexer::TOK_PUNC && CurrentToken.id_name == "(") {
        auto condition = ParseExpression();

        CurrentToken = m_Lexer->GetNextToken();
        if (CurrentToken.token_type == Lexer::TOK_PUNC && CurrentToken.id_name == ")") {
            auto thenBlock = ParseBlock();
        }
    } else {
        Error ("Expecting open bracket for if-condition-start");
    }

}

ASTStatementNode * Parser::ParseStatement() {
    ASTStatementNode * node = nullptr;
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
    return node;
}

ASTFunctionNode * Parser::ParseFunctionPrototype() {
    if (CurrentToken.token_type != Lexer::TOK_ID) {
        Error("Expecting function name");
        return nullptr;
    }

    std::string functionName = CurrentToken.id_name;
    auto functionParameters = std::vector<std::string>();

    CurrentToken = m_Lexer->GetNextToken();

    return nullptr; // ToDo remove nullptr;
}

ASTExprNode * Parser::ParseBinaryExpr(int p_Precedence,ASTExprNode * p_LHS) {
    while(true) {
        if (CurrentToken.token_type == Lexer::TOK_ARITHMETICOP) {
            float op_prec = CurrentToken.number_value;
            std::string op_sym = CurrentToken.id_name;

            CurrentToken = m_Lexer->GetNextToken();

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
    if (CurrentToken.token_type == Lexer::TOK_KEY_NOT || (CurrentToken.token_type == Lexer::TOK_ARITHMETICOP && CurrentToken.id_name == "-")) {
        auto
    }
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
