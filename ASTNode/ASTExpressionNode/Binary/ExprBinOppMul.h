//
// Created by bennet.vella on 23/04/2019.
//

#ifndef COMPILER_EXPRBINOPPMUL_H
#define COMPILER_EXPRBINOPPMUL_H

#include "../Expr.h"
#include "ExprBinOp.h"

namespace AST {
    class ExprBinOpMul: public ExprBinOp {
    public:
        ExprBinOpMul(Expr *pArg1, Expr *pArg2): ExprBinOp(pArg1, pArg2) { }
        virtual ~ExprBinOpMul() = default;
        virtual double solve() const
        {
            return _pArg1->solve() * _pArg2->solve();
        }

        void Accept(Visitor& v) override {};
    };
}

#endif //COMPILER_EXPRBINOPPMUL_H
