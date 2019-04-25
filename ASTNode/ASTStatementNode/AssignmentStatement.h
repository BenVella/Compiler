//
// Created by bennet.vella on 10/04/2019.
//

#ifndef COMPILER_ASTASSIGNMENTSTATEMENTNODE_H
#define COMPILER_ASTASSIGNMENTSTATEMENTNODE_H

#include <string>
#include "Statement.h"

namespace AST {
    class AssignmentStatement : public Statement {
    private:
        std::string _name;
        AST::Expr *RHS;
    public:
        AssignmentStatement(std::string p_name, AST::Expr *p_node) : RHS (p_node) {}
        ~AssignmentStatement() = default;

        void Accept(Visitor& v) override { v.Visit(*this); }

        const std::string &get_name() const { return _name; }
        Expr *getRHS() const { return RHS; }
    };
}

#endif //COMPILER_ASTASSIGNMENTSTATEMENTNODE_H
