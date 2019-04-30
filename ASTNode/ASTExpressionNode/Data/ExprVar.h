//
// Created by bennet.vella on 22/04/2019.
//

#ifndef COMPILER_ASTEXPRVAR_H
#define COMPILER_ASTEXPRVAR_H

#include "../Expr.h"
#include "Var.h"

namespace AST {
    class ExprVar: public Expr {
    private:
        std::string _name;
        Var *_var;
    public:
        ExprVar(const std::string &name, Var *var) : _name(name), _var(var) {}

        ~ExprVar() override = default;
        void Accept(Visitor& v) override { v.Visit(*this); }

        Var *getVar() const {return _var;}
        const std::string &getName() const { return _name; }
    };
}
#endif //COMPILER_ASTEXPRVAR_H
