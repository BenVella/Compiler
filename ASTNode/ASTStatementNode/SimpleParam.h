//
// Created by bennet.vella on 26/04/2019.
//

#ifndef COMPILER_SIMPLEPARAM_H
#define COMPILER_SIMPLEPARAM_H

#include <string>
#include "Statement.h"

namespace AST {
    class SimpleParam : public Statement {
    private:
        Expr *_expr;

    public:
        SimpleParam(AST::Expr * p_expr) : _expr(p_expr) {}

        void Accept(Visitor& v) override { v.Visit(*this); };

        Expr *getExpr() const { return _expr; }
    };
}

#endif //COMPILER_SIMPLEPARAM_H
