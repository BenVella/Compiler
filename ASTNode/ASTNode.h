//
// Created by bennet.vella on 25/03/2019.
//

#ifndef COMPILER_ASTNODE_H
#define COMPILER_ASTNODE_H

#include "../Visitor.h"

class ASTNode {
public:
    ASTNode();
    virtual ~ASTNode();

    void Initialise();

    virtual void Accept(Visitor* v) = 0;
    virtual void PrintInfo (int p_level);
};
#endif //COMPILER_ASTNODE_H
