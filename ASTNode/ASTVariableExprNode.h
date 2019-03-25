//
// Created by bennet.vella on 25/03/2019.
//

#ifndef COMPILER_ASTVARIABLEEXPRNODE_H
#define COMPILER_ASTVARIABLEEXPRNODE_H

#include <string>
#include "ASTExprNode.h"

class ASTVariableExprNode: public ASTExprNode {
public:
    ASTVariableExprNode (const std::string &Name);
    virtual ~ASTVariableExprNode();

    std::string Name;

    virtual void Accept (class Visitor * v);
};

#endif //COMPILER_ASTVARIABLEEXPRNODE_H
