//
// Created by bennv on 4/25/2019.
//

#ifndef COMPILER_PRINT_H
#define COMPILER_PRINT_H

#include "Statement.h"
#include "../ASTExpressionNode/Expr.h"

namespace AST {
    class Print : public Statement {
    private:
        AST::Expr *_expr;
    public:
        Print(AST::Expr *p_node) : _expr (p_node) {}
        ~Print() = default;

        void Accept(Visitor& v) override { v.Visit(*this); }

        Expr *getExpr() const { return _expr; }
    };
}

#endif //COMPILER_PRINT_H
