//
// Created by bennet.vella on 25/03/2019.
//

#ifndef COMPILER_ASTIFSTATEMENTNODE_H
#define COMPILER_ASTIFSTATEMENTNODE_H

#include "ASTNode.h"
#include "ASTStatementNode.h"
#include "../Visitor.h"
#include "ASTExprNode.h"

class ASTIfStatementNode: public ASTStatementNode {
public:
    ASTIfStatementNode();
    virtual ~ASTIfStatementNode();

    ASTExprNode * condition = nullptr;
    ASTNode * LHS = nullptr;
    ASTNode * RHS = nullptr;

    virtual void Accept (Visitor * v);
    virtual void PrintInfo (int p_level) override;
};

#endif //COMPILER_ASTIFSTATEMENTNODE_H
