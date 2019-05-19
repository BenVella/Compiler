//
// Created by bennet.vella on 17/05/2019.
//

#ifndef COMPILER_EXPRBINOPSMALLER_H
#define COMPILER_EXPRBINOPSMALLER_H

#include "ExprBinOp.h"

namespace AST {
    class ExprBinOpSmaller: public ExprBinOp {
    public:
        ExprBinOpSmaller(Expr *pArg1, Expr *pArg2): ExprBinOp(pArg1, pArg2) { }
        virtual ~ExprBinOpSmaller() = default;

        void Accept(Visitor& v) override {v.Visit(*this);}
    };
}

#endif // COMPILER_EXPRBINOPSMALLER_H
