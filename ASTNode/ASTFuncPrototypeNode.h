//
// Created by bennet.vella on 27/03/2019.
//

#ifndef COMPILER_ASTFUNCPROTOTYPENODE_H
#define COMPILER_ASTFUNCPROTOTYPENODE_H


#include "ASTNode.h"

class ASTFuncPrototypeNode: public ASTNode {
    ASTFuncPrototypeNode();
    virtual ~ASTFuncPrototypeNode();

    virtual void PrintInfo (int p_level) = 0;
    virtual void Accept (Visitor * v) = 0;
};


#endif //COMPILER_ASTFUNCPROTOTYPENODE_H
