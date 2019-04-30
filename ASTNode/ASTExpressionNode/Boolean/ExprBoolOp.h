//
// Created by bennet.vella on 30/04/2019.
//

#ifndef COMPILER_EXPRBOOLOP_H
#define COMPILER_EXPRBOOLOP_H

#include "../Expr.h"

namespace AST {
    class ExprBoolOp: public Expr {
    public:
        ExprBoolOp() {}
        ~ExprBoolOp() override = default;
        void Accept(Visitor &v) override = 0;
    };
}

#endif //COMPILER_EXPRBOOLOP_H
