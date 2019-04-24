//
// Created by bennet.vella on 22/04/2019.
//

#ifndef COMPILER_ASTEXPRCONST_H
#define COMPILER_ASTEXPRCONST_H

#include "Expr.h"

namespace AST {
    class ExprConst: public Expr {
    private:
        double _value;
    public:
        ExprConst(double value): Expr(), _value(value) { }
        virtual ~ExprConst() = default;
        virtual double solve() const { return _value; }

        void Accept(Visitor *v) override {};
        void PrintInfo(int p_level) override {};
    };
}
#endif //COMPILER_ASTEXPRCONST_H
