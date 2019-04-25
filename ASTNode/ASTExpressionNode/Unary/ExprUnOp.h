//
// Created by bennet.vella on 22/04/2019.
//

#ifndef COMPILER_EXPRUNOP_H
#define COMPILER_EXPRUNOP_H

#include "../Expr.h"

namespace AST {
    class ExprUnOp: public Expr {
    private:
        Expr *_pArg1;
    protected:
        ExprUnOp(Expr *pArg1): Expr(), _pArg1(pArg1) { }
        virtual ~ExprUnOp() { delete _pArg1; }

        void Accept(Visitor& v) override {
            v.Visit(*this);
        };
    public:
        Expr *get_pArg1() const { return _pArg1; }
    };
}
#endif //COMPILER_EXPRUNOP_H
