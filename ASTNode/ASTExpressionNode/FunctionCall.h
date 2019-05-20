//
// Created by bennet.vella on 30/04/2019.
//

#ifndef COMPILER_FUNCTIONCALL_H
#define COMPILER_FUNCTIONCALL_H

#include <string>

namespace AST {
    class FunctionCall : public Expr {
    private:
        std::string _name;
        Statement*_params;
    public:
        FunctionCall(const std::string &name, Statement *params) : _name(name), _params(params) {}
        virtual ~FunctionCall() override = default;

        void Accept(Visitor &v) override { v.Visit(*this); }

        const std::string &getName() const {return _name;}
        Statement *getParams() const {return _params;}
    };

}

#endif //COMPILER_FUNCTIONCALL_H
