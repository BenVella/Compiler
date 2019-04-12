//
// Created by bennet.vella on 10/04/2019.
//

#ifndef COMPILER_ASTASSIGNMENTSTATEMENTNODE_H
#define COMPILER_ASTASSIGNMENTSTATEMENTNODE_H

#include "ASTStatementNode.h"
#include "../ASTExpressionNode/ASTIdentifierExprNode.h"

class ASTAssignmentStatementNode : public ASTStatementNode {
public:
    ASTAssignmentStatementNode(std::string p_name, ASTExprNode * p_node);
    virtual ~ASTAssignmentStatementNode();

    ASTIdentifierExprNode * LHS;
    ASTExprNode * RHS;

    void PrintInfo (int p_level);
    void Accept (Visitor * v);

};
#endif //COMPILER_ASTASSIGNMENTSTATEMENTNODE_H
