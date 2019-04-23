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
        ExprUnOpNeg(Expr *pArg1): ExprUnOp(pArg1) { }
        virtual ~ExprUnOpNeg() = default;
        virtual double solve() const
        {
            return -_pArg1->solve();
        }
    };
}
#endif //COMPILER_EXPRUNOPNEG_H
