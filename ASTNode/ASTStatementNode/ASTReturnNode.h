//
// Created by bennet.vella on 27/03/2019.
//

#ifndef COMPILER_ASTRETURNSTATEMENTNODE_H
#define COMPILER_ASTRETURNSTATEMENTNODE_H


#include "../ASTExprNode.h"
#include "ASTStatementNode.h"

class ASTReturnNode: public ASTStatementNode {
public:
    ASTReturnNode();
    virtual ~ASTReturnNode();

    ASTExprNode * LHS = nullptr;

    void Accept (Visitor * v);
    void PrintInfo (int p_level) override;
};

#endif //COMPILER_ASTRETURNSTATEMENTNODE_H
