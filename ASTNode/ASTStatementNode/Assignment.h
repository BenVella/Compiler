//
// Created by bennet.vella on 10/04/2019.
//

#ifndef COMPILER_ASTASSIGNMENT_H
#define COMPILER_ASTASSIGNMENT_H

#include <string>
#include "Statement.h"

namespace AST {
    class Assignment : public Statement {
    private:
        std::string _name;
        AST::Expr *RHS;
    public:
        Assignment(std::string p_name, AST::Expr *p_node) : RHS (p_node) {}
        ~Assignment() = default;

        void Accept(Visitor& v) override { v.Visit(*this); }

        const std::string &get_name() const { return _name; }
        Expr *getRHS() const { return RHS; }
    };
}

#endif //COMPILER_ASTASSIGNMENT_H
