//
// Created by bennet.vella on 11/04/2019.
//

#ifndef COMPILER_ASTNUMBEREXPRNODE_H
#define COMPILER_ASTNUMBEREXPRNODE_H

#include "ASTExprNode.h"

class ASTNumberExprNode : public ASTExprNode {
public:
    ASTNumberExprNode(ASTExprNode * p_node);
    virtual ~ASTNumberExprNode();

    ASTExprNode * literalVal;

    void PrintInfo (int p_level) override;
    void Accept (Visitor * v) override;
};

#endif //COMPILER_ASTNUMBEREXPRNODE_H
