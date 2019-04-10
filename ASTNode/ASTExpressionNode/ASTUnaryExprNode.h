//
// Created by bennet.vella on 10/04/2019.
//

#ifndef COMPILER_ASTUNARYEXPRNODE_H
#define COMPILER_ASTUNARYEXPRNODE_H

#include <string>
#include "ASTExprNode.h"

class ASTUnaryExprNode : public ASTExprNode {
public:
    ASTUnaryExprNode();
    virtual ~ASTUnaryExprNode();

    std::string m_val;
    ASTExprNode * LHS;

    void PrintInfo (int p_level) override;
    void Accept (Visitor * v) override;
};
#endif //COMPILER_ASTUNARYEXPRNODE_H