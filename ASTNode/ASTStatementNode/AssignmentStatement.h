//
// Created by bennet.vella on 10/04/2019.
//

#ifndef COMPILER_ASTASSIGNMENTSTATEMENTNODE_H
#define COMPILER_ASTASSIGNMENTSTATEMENTNODE_H

#include <string>
#include "Statement.h"

namespace AST {
    class AssignmentStatement : public Statement {
    public:
        AssignmentStatement(std::string p_name, AST::Expr *p_node) : LHS (p_node) {}
        ~AssignmentStatement() = default;

        AST::Expr *LHS;
        AST::Expr *RHS;

        void Accept(Visitor& v) override {};
    };
}

#endif //COMPILER_ASTASSIGNMENTSTATEMENTNODE_H
