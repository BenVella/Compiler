//
// Created by bennet.vella on 10/04/2019.
//

#ifndef COMPILER_ASTFACTOREXPRNODE_H
#define COMPILER_ASTFACTOREXPRNODE_H


#include <string>
#include "ASTExprNode.h"

class ASTFactorExprNode : public ASTExprNode {
public:
    ASTFactorExprNode();
    virtual ~ASTFactorExprNode();

    ASTExprNode * node;         // Accepts a (bool/int/float) / Identifier

    void PrintInfo (int p_level);
    void Accept (Visitor * v);
};


#endif //COMPILER_ASTFACTOREXPRNODE_H
