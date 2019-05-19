//
// Created by bennet.vella on 26/04/2019.
//

#ifndef COMPILER_FOR_H
#define COMPILER_FOR_H

#include "Statement.h"

namespace AST {
    class For : public Statement {
    private:
        Statement *_var;
        Expr *_expr;
        Statement *_assign;
        Statement *_block;

    public:
        For(Statement *p_var,Expr *p_expr, Statement *p_assign, Statement*p_block) : _var(p_var), _expr(p_expr), _assign(p_assign), _block(p_block) {}
        void Accept(Visitor& v) override { v.Visit(*this); }

        Statement *getVar() const { return _var; }
        Expr *getExpr() const { return _expr; }
        Statement *getAssign() const { return _assign; }
        Statement *getBlock() const { return _block; }
    };
}

#endif //COMPILER_FOR_H
