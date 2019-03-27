//
// Created by bennet.vella on 25/03/2019.
//

#ifndef COMPILER_ASTSTATEMENTNODE_H
#define COMPILER_ASTSTATEMENTNODE_H

#include "ASTNode.h"

class ASTStatementNode: public ASTNode  {
public:
    ASTStatementNode();
    virtual ~ASTStatementNode();

    virtual void PrintInfo (int p_level) = 0;
    virtual void Accept (Visitor * v) = 0;
};

#endif //COMPILER_ASTSTATEMENTNODE_H
