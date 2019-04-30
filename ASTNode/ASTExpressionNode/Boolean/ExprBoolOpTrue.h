//
// Created by bennet.vella on 30/04/2019.
//

#ifndef COMPILER_EXPRBOOLOPTRUE_H
#define COMPILER_EXPRBOOLOPTRUE_H

#include "ExprBoolOp.h"

namespace AST {
    class ExprBoolOpTrue : public ExprBoolOp {
    public:
        ExprBoolOpTrue() {}
        ~ExprBoolOpTrue() = default;
        void Accept(Visitor &v) override { v.Visit(*this); }
    };
}

#endif //COMPILER_EXPRBOOLOPTRUE_H
