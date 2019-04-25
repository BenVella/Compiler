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
        Var *get_pVar() const {return _pVar;}
        explicit ExprVar(Var *pVar): Expr(), _pVar(pVar) { }
        ~ExprVar() override = default;
        double solve() const override { return _pVar->get(); }
        void Accept(Visitor& v) override {
            v.Visit(*this);
        };
    };
}
#endif //COMPILER_ASTEXPRVAR_H
