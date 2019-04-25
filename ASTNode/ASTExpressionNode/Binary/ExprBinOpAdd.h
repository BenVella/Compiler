//
// Created by bennet.vella on 22/04/2019.
//

#ifndef COMPILER_EXPRBINOPADD_H
#define COMPILER_EXPRBINOPADD_H

#include "../Expr.h"
#include "ExprBinOp.h"
#include "../../../Visitor/Visitor.h"

namespace AST {
    class ExprBinOpAdd: public ExprBinOp {
    public:
        ExprBinOpAdd(Expr *pArg1, Expr *pArg2): ExprBinOp(pArg1, pArg2) { }

        ~ExprBinOpAdd() override = default;

        double solve() const override {
            return _pArg1->solve() + _pArg2->solve();
        }

        void Accept(Visitor& v) override {
            v.Visit(*this);
        };
    };
}
#endif //COMPILER_EXPRBINOPADD_H
