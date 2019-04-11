//
// Created by bennet.vella on 11/04/2019.
//

#ifndef COMPILER_ASTVARIABLEEXPRNODE_H
#define COMPILER_ASTVARIABLEEXPRNODE_H

#include "ASTExprNode.h"

class ASTVariableExprNode : public ASTExprNode {
public:
    ASTVariableExprNode();
    virtual ~ASTVariableExprNode();

    std::string name;

    void PrintInfo (int p_level) override;
    void Accept (Visitor * v) override;
};

#endif //COMPILER_ASTVARIABLEEXPRNODE_H
