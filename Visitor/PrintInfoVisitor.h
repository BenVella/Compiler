//
// Created by bennet.vella on 10/04/2019.
//

#ifndef COMPILER_PRINTINFOVISITOR_H
#define COMPILER_PRINTINFOVISITOR_H

#include <iostream>
#include "Visitor.h"
#include "../ASTNode/ASTExpressionNode/Expr.h"
#include "../ASTNode/ASTExpressionNode/Binary/ExprBinOpAdd.h"
#include "../ASTNode/ASTExpressionNode/Binary/ExprBinOpSub.h"

class PrintInfoVisitor : public Visitor {
private:
    void println(std::string p_str) {
        std::cout << p_str << std::endl;
    }

public:
    virtual void Visit(AST::Expr& p_node) override {
        println("Visit Expr Node");
    }

    virtual void Visit(AST::ExprBinOpAdd& p_node) override {
        println("<BinOpAdd>");
        p_node._pArg1->Accept(*this);
        p_node._pArg2->Accept(*this);
        println("</BinOpAdd>");
    }

    virtual void Visit(AST::ExprBinOpSub& p_node) override {
        println("<BinOpSub>");
        p_node._pArg1->Accept(*this);
        p_node._pArg2->Accept(*this);
        println("</BinOpSub>");
    }
};
#endif //COMPILER_PRINTINFOVISITOR_H
