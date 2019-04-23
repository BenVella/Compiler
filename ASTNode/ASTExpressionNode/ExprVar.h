//
// Created by bennet.vella on 22/04/2019.
//

#ifndef COMPILER_ASTEXPRVAR_H
#define COMPILER_ASTEXPRVAR_H

#include "Expr.h"
#include "Var.h"

namespace AST {
    class ExprVar: public Expr {
    private:
        Var *_pVar;
    public:
        ExprVar(Var *pVar): Expr(), _pVar(pVar) { }
        virtual ~ExprVar() = default;
        virtual double solve() const { return _pVar->get(); }
    };
}
#endif //COMPILER_ASTEXPRVAR_H
