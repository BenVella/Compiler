//
// Created by bennet.vella on 10/04/2019.
//

#ifndef COMPILER_ASTSIMPLEEXPRNODE_H
#define COMPILER_ASTSIMPLEEXPRNODE_H

#include "ASTTermExprNode.h"

class ASTSimpleExprNode : public ASTExprNode {
public:
    ASTSimpleExprNode();
    virtual ~ASTSimpleExprNode();

    ASTTermExprNode * LHS_term;
    ASTTermExprNode * RHS_term;         // Optional
    std::string m_additiveOper;         // Optional

    void PrintInfo (int p_level) override;
    void Accept (Visitor * v) override;
};
#endif //COMPILER_ASTSIMPLEEXPRNODE_H
