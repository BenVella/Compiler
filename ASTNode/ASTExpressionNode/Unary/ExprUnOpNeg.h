//
// Created by bennet.vella on 22/04/2019.
//

#ifndef COMPILER_EXPRUNOPNEG_H
#define COMPILER_EXPRUNOPNEG_H

#include "../Expr.h"
#include "ExprUnOp.h"

namespace AST {
    class ExprUnOpNeg: public ExprUnOp {
    public:
        explicit ExprUnOpNeg(Expr *pArg1): ExprUnOp(pArg1) { }
        ~ExprUnOpNeg() override = default;

        void Accept(Visitor& v) override {
            v.Visit(*this);
        }
    };
}
#endif //COMPILER_EXPRUNOPNEG_H
