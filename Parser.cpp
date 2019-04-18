//
// Created by bennet.vella on 25/03/2019.
//

#include <vector>
#include "Parser.h"
#include "ASTNode/ASTProgramNode.h"
#include "ASTNode/ASTStatementNode/ASTAssignmentStatementNode.h"
#include "ASTNode/ASTExpressionNode/Unary/ASTUnaryExprNode.h"
#include "ASTNode/ASTExpressionNode/Unary/ASTUnaryNotExprNode.h"
#include "ASTNode/ASTExpressionNode/Unary/ASTUnaryNegExprNode.h"
#include "ASTNode/ASTExpressionNode/ASTNumberExprNode.h"
#include "ASTNode/ASTExpressionNode/Literal/ASTIntegerLiteralExprNode.h"
#include "ASTNode/ASTExpressionNode/Literal/ASTFloatLiteralExprNode.h"
#include "ASTNode/ASTExpressionNode/ASTBinaryExprNode.h"

Parser::Parser(Lexer * p_Lexer) {
    m_Lexer = p_Lexer;
}

Parser::~Parser() {

}
// Handle Expressions Only
ASTNode *Parser::Parse() {
    ASTProgramNode * root = new ASTProgramNode();

    nextToken();

    switch (CurrentToken.token_type) {
        case Lexer::TOK_INT_NUMBER:
        case Lexer::TOK_FLOAT_NUMBER:
        case Lexer::TOK_ID:
        case Lexer::TOK_KEY_NOT:
        case Lexer::TOK_PUNC:
            auto * result = ParseBinaryExpr();
            break;
    }

    return nullptr;
}

/*
ASTExprNode * Parser::ParseExpression() {
    auto LHS = ParseUnaryExpr();
    if (!LHS)
        return nullptr;
    return ParseBinaryExpr(0,std::move(LHS));
}


ASTExprNode * Parser::ParseBinaryExpr(int p_Precedence,ASTExprNode * p_LHS) {
    while(true) {
        if (isToken(Lexer::TOK_ARITHMETICOP)) {
            float op_prec = CurrentToken.number_value;
            std::string op_sym = CurrentToken.id_name;

            nextToken();

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
*/

ASTExprNode * Parser::ParseBinaryExpr() {

    auto * mainNode = new ASTBinaryExprNode();

    if (isToken(Lexer::TOK_ID)) {
        mainNode->LHS = new ASTIdentifierExprNode(CurrentToken.id_name);
    } else if (isToken(Lexer::TOK_FLOAT_NUMBER)){
        mainNode->LHS = new ASTFloatLiteralExprNode(CurrentToken.number_value);
    } else if (isToken(Lexer::TOK_INT_NUMBER)) {
        mainNode->LHS = new ASTIntegerLiteralExprNode(CurrentToken.number_value);
    }

    nextToken(); // Expecting Op

    if (isToken(Lexer::TOK_ARITHMETICOP)) {
        mainNode->op = CurrentToken.id_name;
    }

    nextToken();

    if (isToken(Lexer::TOK_ID)) {
        mainNode->RHS = new ASTIdentifierExprNode(CurrentToken.id_name);
    } else if (isToken(Lexer::TOK_FLOAT_NUMBER)){
        mainNode->RHS = new ASTFloatLiteralExprNode(CurrentToken.number_value);
    } else if (isToken(Lexer::TOK_INT_NUMBER)) {
        mainNode->RHS = new ASTIntegerLiteralExprNode(CurrentToken.number_value);
    }

    return mainNode;
}

ASTExprNode *Parser::ParseUnaryExpr() {
    // Check if we have a unary expression
    ASTExprNode * test;

    if (isToken(Lexer::TOK_KEY_NOT) || (isToken(Lexer::TOK_ARITHMETICOP) && CurrentToken.id_name == "-")) {
        auto * node = new ASTUnaryExprNode();

        if (isToken(Lexer::TOK_KEY_NOT))
            node->modifier = new ASTUnaryNotExprNode();
        else
            node->modifier = new ASTUnaryNegExprNode();

        nextToken();

        if (isToken(Lexer::TOK_INT_NUMBER)) {
            auto * intVal = new ASTIntegerLiteralExprNode(CurrentToken.number_value);
            node->LHS = new ASTNumberExprNode(intVal);
        } else if (isToken(Lexer::TOK_FLOAT_NUMBER)) {
            auto * floatVal = new ASTFloatLiteralExprNode(CurrentToken.number_value);
            node->LHS = new ASTNumberExprNode(floatVal);
        } else if (isToken(Lexer::TOK_ID)) {
            node->LHS = new ASTIdentifierExprNode(CurrentToken.id_name);
        } else {
            std::string error = "Expecting a token type of integer or float, instead found: " + CurrentToken.ToString();
            Error(error.c_str());
            return nullptr;
        }

        return node;
    } else if (isToken(Lexer::TOK_INT_NUMBER) || isToken(Lexer::TOK_FLOAT_NUMBER) || isToken(Lexer::TOK_ID)) {
        auto * node = new ASTBinaryExprNode();
        if (isToken(Lexer::TOK_INT_NUMBER)) {
            auto *intVal = new ASTIntegerLiteralExprNode(CurrentToken.number_value);
            node->LHS = new ASTNumberExprNode(intVal);
        } else if (isToken(Lexer::TOK_FLOAT_NUMBER)) {
            auto *floatVal = new ASTFloatLiteralExprNode(CurrentToken.number_value);
            node->LHS = new ASTNumberExprNode(floatVal);
        } else if (isToken(Lexer::TOK_ID)) {
            node->LHS = new ASTIdentifierExprNode(CurrentToken.id_name);
        } else {
            std::string error = "Expecting a token type of integer or float, instead found: " + CurrentToken.ToString();
            Error(error.c_str());
            return nullptr;
        }

        return node;
    }

    CurrentToken = m_Lexer->GetNextToken();

    if (isToken(Lexer::TOK_INT_NUMBER)) {
        auto * intVal = new ASTIntegerLiteralExprNode(CurrentToken.number_value);
        unary->LHS = new ASTNumberExprNode(intVal);
    } else if (isToken(Lexer::TOK_FLOAT_NUMBER)) {
        auto * floatVal = new ASTFloatLiteralExprNode(CurrentToken.number_value);
        unary->LHS = new ASTNumberExprNode(floatVal);
    } else {
        std::string error = "Expecting a token type of integer or float, instead found: " + CurrentToken.ToString();
        Error(error.c_str());
        return nullptr;
    }

    return unary;
}

ASTExprNode * Parser::ParseSimpleExpression () {
    ParseTermExpression();

}

ASTExprNode * Parser::ParseTermExpression() {
    if (isToken(Lexer::TOK_INT_NUMBER)) {
        auto *fac1 = ParseFactorExpression();

        nextToken();

        if (isToken(Lexer::TOK_ARITHMETICOP) && (CurrentToken.id_name == "*" || CurrentToken.id_name == "/")) {
            nextToken();
            auto *fac2 = ParseFactorExpression();

            auto * result = new ASTBinaryExprNode();
            result->op = CurrentToken.id_name;
            result->LHS = fac1;
            result->RHS = fac2;

            return result;
        } else {
            auto * result = new ASTUnaryExprNode();
            result->LHS = fac1;
            return result;
        }
    }
}

ASTExprNode * Parser::ParseFactorExpression() {
    if (isToken(Lexer::TOK_INT_NUMBER)){
        return new ASTIntegerLiteralExprNode(CurrentToken.number_value);
    }
}

ASTStatementNode * Parser::ParseReturnStatement() {
    CurrentToken = m_Lexer->GetNextToken();
    auto expr_node = ParseExpression();
    if (!expr_node)
        return nullptr;

    auto node = new ASTReturnNode(expr_node);
    return node;
}

ASTStatementNode *Parser::ParseIdStatement() {
    return nullptr;
}

ASTStatementNode * Parser::ParseIfStatement() {
    CurrentToken = m_Lexer->GetNextToken();
    if (isToken(Lexer::TOK_PUNC && CurrentToken.id_name == "(") {
        auto condition = ParseExpression();

        CurrentToken = m_Lexer->GetNextToken();
        if (isToken(Lexer::TOK_PUNC && CurrentToken.id_name == ")") {
            // auto thenBlock = ParseBlock();   // ToDo create a block node?
        }
    } else {
        Error ("Expecting open bracket for if-condition-start");
    }
    return nullptr;
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
    return node; //nullptr is not set
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

ASTStatementNode * Parser::ParseAssignmentStatement() {
    CurrentToken = m_Lexer->GetNextToken();
    std::string var_name;
    if (isToken(Lexer::TOK_ID) {
        var_name = CurrentToken.id_name;
        CurrentToken = m_Lexer->GetNextToken();
    } else {
        Error("Expecting Id Token for Assignment Start");
        return nullptr;
    }

    if (CurrentToken.token_type != Lexer::TOK_ASSIGNOP) {
        Error("Expecting '=' while parsing an assignment statement");
        return nullptr;
    }
    CurrentToken = m_Lexer->GetNextToken();
    auto expr_node = ParseExpression();
    auto ass_node = new ASTAssignmentStatementNode(var_name.c_str(), expr_node);
    return ass_node;
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

// Helper Methods
bool Parser::isToken(Lexer::TOK_TYPE p_type) {
    return CurrentToken.token_type == p_type;
}

void Parser::nextToken() {
    CurrentToken = m_Lexer->GetNextToken();
}