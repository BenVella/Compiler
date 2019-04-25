//
// Created by bennet.vella on 22/04/2019.
//

#ifndef COMPILER_EXPRBINOPSUB_H
#define COMPILER_EXPRBINOPSUB_H

#include "../Expr.h"
#include "ExprBinOp.h"

namespace AST {
    class ExprBinOpSub: public ExprBinOp {
    public:
        ExprBinOpSub(Expr *pArg1, Expr *pArg2): ExprBinOp(pArg1, pArg2) { }
        virtual ~ExprBinOpSub() = default;
        virtual double solve() const
        {
            return get_pArg1()->solve() - get_pArg2()->solve();
        }

        void Accept(Visitor& v) override { v.Visit(*this); }
    };
}
#endif //COMPILER_EXPRBINOPSUB_H
