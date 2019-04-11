//
// Created by bennet.vella on 25/03/2019.
//

#ifndef COMPILER_ASTIFSTATEMENTNODE_H
#define COMPILER_ASTIFSTATEMENTNODE_H

#include "../ASTNode.h"
#include "ASTStatementNode.h"
#include "../../Visitor/Visitor.h"
#include "../ASTExpressionNode/ASTExprNode.h"

class ASTIfNode: public ASTStatementNode {
public:
    ASTIfNode();
    virtual ~ASTIfNode();

    ASTExprNode * condition = nullptr;
    ASTNode * LHS = nullptr;
    ASTNode * RHS = nullptr;

    void Accept (Visitor * v) override;
    void PrintInfo (int p_level) override;
};

#endif //COMPILER_ASTIFSTATEMENTNODE_H