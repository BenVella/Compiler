//
// Created by bennet.vella on 10/04/2019.
//

#ifndef COMPILER_ASTFACTOREXPRNODE_H
#define COMPILER_ASTFACTOREXPRNODE_H


#include <string>
#include "ASTTermExprNode.h"

class ASTFactorExprNode : public ASTTermExprNode {
public:
    ASTFactorExprNode();
    virtual ~ASTFactorExprNode();

    std::string m_value;         // Optional

    void PrintInfo (int p_level);
    void Accept (Visitor * v);
};


#endif //COMPILER_ASTFACTOREXPRNODE_H
