//
// Created by bennet.vella on 22/04/2019.
//

#ifndef COMPILER_EXPRBINOPADD_H
#define COMPILER_EXPRBINOPADD_H

#include "../Expr.h"
#include "ExprBinOp.h"

namespace AST {
    class ExprBinOpAdd: public ExprBinOp {
    public:
        ExprBinOpAdd(Expr *pArg1, Expr *pArg2): ExprBinOp(pArg1, pArg2) { }
        virtual ~ExprBinOpAdd() = default;
        virtual double solve() const
        {
            return _pArg1->solve() + _pArg2->solve();
        }
    };
}
#endif //COMPILER_EXPRBINOPADD_H
