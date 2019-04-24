//
// Created by bennet.vella on 22/04/2019.
//

#ifndef COMPILER_EXPRUNOP_H
#define COMPILER_EXPRUNOP_H

#include "../Expr.h"

namespace AST {
    class ExprUnOp: public Expr {
    protected:
        Expr *_pArg1;
    protected:
        ExprUnOp(Expr *pArg1): Expr(), _pArg1(pArg1) { }
        virtual ~ExprUnOp() { delete _pArg1; }

        void Accept(Visitor& v) override {};
    };
}
#endif //COMPILER_EXPRUNOP_H
