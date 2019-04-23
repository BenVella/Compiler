//
// Created by bennet.vella on 10/04/2019.
//

#ifndef COMPILER_ASTASSIGNMENTSTATEMENTNODE_H
#define COMPILER_ASTASSIGNMENTSTATEMENTNODE_H

#include <string>
#include "ASTStatementNode.h"

namespace AST {
    class ASTAssignmentStatementNode : public ASTStatementNode {
    public:
        ASTAssignmentStatementNode(std::string p_name, AST::Expr *p_node);
        virtual ~ASTAssignmentStatementNode();

        AST::Expr *LHS;
        AST::Expr *RHS;

        void PrintInfo(int p_level);
        void Accept(Visitor *v);
    };
}

#endif //COMPILER_ASTASSIGNMENTSTATEMENTNODE_H
