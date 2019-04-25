//
// Created by bennet.vella on 22/04/2019.
//

#ifndef COMPILER_VAR_H
#define COMPILER_VAR_H

namespace AST {
    class Var {
    private:
        float _value;
    public:
        Var(): _value() { }
        ~Var() = default;
        double get() const { return _value; }
        void set(double value) { _value = value; }
    };
}

#endif //COMPILER_VAR_H