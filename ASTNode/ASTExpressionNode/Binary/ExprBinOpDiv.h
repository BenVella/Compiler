//
// Created by bennet.vella on 23/04/2019.
//

#ifndef COMPILER_EXPRBINOPDIV_H
#define COMPILER_EXPRBINOPDIV_H

#include "../Expr.h"
#include "ExprBinOp.h"

namespace AST {
    class ExprBinOpDiv: public ExprBinOp {
    public:
        ExprBinOpDiv(Expr *pArg1, Expr *pArg2): ExprBinOp(pArg1, pArg2) { }
        virtual ~ExprBinOpDiv() = default;

        void Accept(Visitor& v) override {v.Visit(*this);}
    };

}

#endif //COMPILER_EXPRBINOPDIV_H