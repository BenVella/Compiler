//
// Created by bennet.vella on 10/04/2019.
//

#ifndef COMPILER_PRINTINFOVISITOR_H
#define COMPILER_PRINTINFOVISITOR_H

#include <iostream>
#include "Visitor.h"
#include "../ASTNode/ASTExpressionNode/Expr.h"

class PrintInfoVisitor : public Visitor {
private:
    void println(std::string p_str) {
        std::cout << p_str << std::endl;
    }

public:
    virtual void Visit(AST::Expr *p_node) {
        println("Visit Expr Node");
    }
};
#endif //COMPILER_PRINTINFOVISITOR_H
