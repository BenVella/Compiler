//
// Created by bennet.vella on 17/05/2019.
//

#ifndef COMPILER_EXPRBINOPGREATER_H
#define COMPILER_EXPRBINOPGREATER_H

#include "ExprBinOp.h"

namespace AST {
    class ExprBinOpGreater: public ExprBinOp {
    public:
        ExprBinOpGreater(Expr *pArg1, Expr *pArg2): ExprBinOp(pArg1, pArg2) { }
        virtual ~ExprBinOpGreater() = default;

        void Accept(Visitor& v) override {v.Visit(*this);}
    };
}

#endif //COMPILER_EXPRBINOPGREATER_H
