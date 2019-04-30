//
// Created by bennet.vella on 22/04/2019.
//

#ifndef COMPILER_ASTEXPRCONSTFLOAT_H
#define COMPILER_ASTEXPRCONSTFLOAT_H

#include "../Expr.h"

namespace AST {
    class ExprConstFloat: public Expr {
    private:
        float _value;
    public:
        double get_value() const { return _value; }

    public:
        ExprConstFloat(float value): Expr(), _value(value) { }
        virtual ~ExprConstFloat() = default;

        void Accept(Visitor& v) override { v.Visit(*this); }
    };
}
#endif //COMPILER_ASTEXPRCONSTFLOAT_H
