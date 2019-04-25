//
// Created by bennet.vella on 23/04/2019.
//

#ifndef COMPILER_EXPRBINOPPDIV_H
#define COMPILER_EXPRBINOPPDIV_H

#include "../Expr.h"
#include "ExprBinOp.h"

namespace AST {
    class ExprBinOpDiv: public ExprBinOp {
    public:
        ExprBinOpDiv(Expr *pArg1, Expr *pArg2): ExprBinOp(pArg1, pArg2) { }
        virtual ~ExprBinOpDiv() = default;
        virtual float solve() const
        {
            return get_pArg1()->solve() / get_pArg2()->solve();
        }

        void Accept(Visitor& v) override {v.Visit(*this);}
    };

}

#endif //COMPILER_EXPRBINOPPDIV_H