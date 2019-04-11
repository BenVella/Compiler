//
// Created by bennet.vella on 10/04/2019.
//

#ifndef COMPILER_ASTTERMEXPRNODE_H
#define COMPILER_ASTTERMEXPRNODE_H

#include "ASTSimpleExprNode.h"
#include "ASTFactorExprNode.h"

class ASTTermExprNode : public ASTSimpleExprNode {
public:
    ASTTermExprNode();
    virtual ~ASTTermExprNode();

    ASTFactorExprNode * LHS_factor;
    ASTFactorExprNode * RHS_factor;     // Optional
    std::string m_additiveOper;         // Optional

    void PrintInfo (int p_level);
    void Accept (Visitor * v);
};
#endif //COMPILER_ASTTERMEXPRNODE_H
