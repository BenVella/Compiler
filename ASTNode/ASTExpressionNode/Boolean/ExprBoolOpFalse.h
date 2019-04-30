//
// Created by bennet.vella on 30/04/2019.
//

#ifndef COMPILER_EXPRBOOLOPFALSE_H
#define COMPILER_EXPRBOOLOPFALSE_H

#include "ExprBoolOp.h"

namespace AST {
    class ExprBoolOpFalse : public ExprBoolOp {
    public:
        ExprBoolOpFalse() {}
        ~ExprBoolOpFalse() = default;
        void Accept(Visitor &v) override { v.Visit(*this); }
    };
}

#endif //COMPILER_EXPRBOOLOPFALSE_H
