#include <utility>

//
// Created by bennet.vella on 26/04/2019.
//

#ifndef COMPILER_PARAM_H
#define COMPILER_PARAM_H

#include <string>
#include "Statement.h"

namespace AST {
    class Param : public Statement {
    private:
        std::string _name;
        std::string _type;

    public:
        Param(std::string _name, std::string _type) : _name(std::move(_name)), _type(std::move(_type)) {}

        void Accept(Visitor& v) override { v.Visit(*this); };

        const std::string &getName() const { return _name; }
        const std::string &getType() const { return _type; }
    };
}

#endif //COMPILER_PARAM_H
