//
// Created by bennet.vella on 22/04/2019.
//

#ifndef COMPILER_ASTEXPRCONSTINT_H
#define COMPILER_ASTEXPRCONSTINT_H

#include "../Expr.h"

namespace AST {
    class ExprConstInt: public Expr {
    private:
        int _value;
    public:
        int get_value() const { return _value; }

    public:
        ExprConstInt(float value): Expr(), _value(value) { }
        virtual ~ExprConstInt() = default;

        void Accept(Visitor& v) override { v.Visit(*this); }
    };
}
#endif //COMPILER_ASTEXPRCONSTINT_H
