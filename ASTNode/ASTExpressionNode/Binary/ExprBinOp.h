//
// Created by bennet.vella on 22/04/2019.
//

#ifndef COMPILER_EXPRBINOP_H
#define COMPILER_EXPRBINOP_H

#include "../Expr.h"

namespace AST {
    class ExprBinOp: public Expr {
    public:
        Expr *_pArg1, *_pArg2;
    protected:
        ExprBinOp(Expr *pArg1, Expr *pArg2):
                Expr(), _pArg1(pArg1), _pArg2(pArg2)
        { }
        virtual ~ExprBinOp() { delete _pArg1; delete _pArg2; }

        virtual void Accept(Visitor& v) = 0;
    };
}
#endif //COMPILER_EXPRBINOP_H
