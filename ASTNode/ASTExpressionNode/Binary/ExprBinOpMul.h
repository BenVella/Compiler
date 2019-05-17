//
// Created by bennet.vella on 23/04/2019.
//

#ifndef COMPILER_EXPRBINOPMUL_H
#define COMPILER_EXPRBINOPMUL_H

#include "../Expr.h"
#include "ExprBinOp.h"

namespace AST {
    class ExprBinOpMul: public ExprBinOp {
    public:
        ExprBinOpMul(Expr *pArg1, Expr *pArg2): ExprBinOp(pArg1, pArg2) { }
        virtual ~ExprBinOpMul() = default;

        void Accept(Visitor& v) override {v.Visit(*this);}
    };
}

#endif //COMPILER_EXPRBINOPMUL_H
