//
// Created by bennet.vella on 27/03/2019.
//

#ifndef COMPILER_ASTRETURNSTATEMENTNODE_H
#define COMPILER_ASTRETURNSTATEMENTNODE_H


#include "../ASTExpressionNode/ASTExprNode.h"
#include "ASTStatementNode.h"

class ASTReturnNode: public ASTStatementNode {
public:
    ASTReturnNode(ASTExprNode * p_node);
    virtual ~ASTReturnNode() {}

    ASTExprNode * LHS;

    void Accept (Visitor * v) override;
    void PrintInfo (int p_level) override;
};

#endif //COMPILER_ASTRETURNSTATEMENTNODE_H
