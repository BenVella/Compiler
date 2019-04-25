//
// Created by bennet.vella on 22/04/2019.
//

#ifndef COMPILER_VAR_H
#define COMPILER_VAR_H

#include "../Expr.h"

namespace AST {
    class Var {
    private:
        Expr *_value;
    public:
        Var(): _value() { }
        ~Var() = default;
        Expr* get() const { return _value; }
        void set(Expr *value) { _value = value; }
    };
}

#endif //COMPILER_VAR_H