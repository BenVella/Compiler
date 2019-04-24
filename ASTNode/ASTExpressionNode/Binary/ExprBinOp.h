//
// Created by bennet.vella on 22/04/2019.
//

#ifndef COMPILER_EXPRBINOP_H
#define COMPILER_EXPRBINOP_H

#include "../Expr.h"

namespace AST {
    class ExprBinOp: public Expr {
    protected:
        Expr *_pArg1, *_pArg2;
    protected:
        ExprBinOp(Expr *pArg1, Expr *pArg2):
                Expr(), _pArg1(pArg1), _pArg2(pArg2)
        { }
        virtual ~ExprBinOp() { delete _pArg1; delete _pArg2; }

        void Accept(Visitor *v) override {};
        void PrintInfo(int p_level) override {};
    };
}
#endif //COMPILER_EXPRBINOP_H
