//
// Created by bennet.vella on 25/03/2019.
//

#ifndef COMPILER_ASTEXPRNODE_H
#define COMPILER_ASTEXPRNODE_H


#include "../ASTNode.h"
#include "../../Visitor/Visitor.h"
#include "ASTSimpleExprNode.h"

class ASTExprNode : public ASTNode {
public:
    ASTExprNode();
    virtual ~ASTExprNode();

    ASTSimpleExprNode * LHS;
    ASTSimpleExprNode * RHS;    // Optional
    std::string m_oper;         // Optional

    void PrintInfo (int p_level) override;
    void Accept (Visitor * v) override;
};

#endif //COMPILER_ASTEXPRNODE_H
