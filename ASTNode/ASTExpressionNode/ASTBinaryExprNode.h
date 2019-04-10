//
// Created by bennet.vella on 10/04/2019.
//

#ifndef COMPILER_ASTBINARYEXPRNODE_H
#define COMPILER_ASTBINARYEXPRNODE_H

#include <string>
#include "ASTExprNode.h"

class ASTBinaryExprNode : public ASTExprNode {
public:
    ASTBinaryExprNode();
    virtual ~ASTBinaryExprNode();

    std::string m_val;
    ASTExprNode * LHS;
    ASTExprNode * RHS;

    void PrintInfo (int p_level) override;
    void Accept (Visitor * v) override;
};
#endif //COMPILER_ASTBINARYEXPRNODE_H
