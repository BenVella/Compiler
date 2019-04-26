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
        AST::Expr *_expr;
    public:
        Assignment(std::string p_name, AST::Expr *p_node) : _name(p_name), _expr (p_node) {}
        ~Assignment() = default;

        void Accept(Visitor& v) override { v.Visit(*this); }

        const std::string &getName() const { return _name; }
        Expr *getExpr() const { return _expr; }
    };
}

#endif //COMPILER_ASTASSIGNMENT_H
