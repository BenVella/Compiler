//
// Created by bennet.vella on 25/03/2019.
//

#ifndef COMPILER_ASTVARIABLEEXPRNODE_H
#define COMPILER_ASTVARIABLEEXPRNODE_H

#include <string>
#include "../ASTExpressionNode/ASTExprNode.h"

class ASTVariableNode: public ASTExprNode {
public:
    explicit ASTVariableNode (const std::string &Name);
    virtual ~ASTVariableNode();

    std::string Name;

    void PrintInfo (int p_level) override;
    void Accept (class Visitor * v) override;
};

#endif //COMPILER_ASTVARIABLEEXPRNODE_H
