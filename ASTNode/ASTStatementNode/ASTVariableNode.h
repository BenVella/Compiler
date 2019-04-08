//
// Created by bennet.vella on 25/03/2019.
//

#ifndef COMPILER_ASTVARIABLEEXPRNODE_H
#define COMPILER_ASTVARIABLEEXPRNODE_H

#include <string>
#include "../ASTExprNode.h"

class ASTVariableNode: public ASTExprNode {
public:
    ASTVariableNode (const std::string &Name);
    virtual ~ASTVariableNode();

    std::string Name;

    virtual void Accept (class Visitor * v);
};

#endif //COMPILER_ASTVARIABLEEXPRNODE_H
