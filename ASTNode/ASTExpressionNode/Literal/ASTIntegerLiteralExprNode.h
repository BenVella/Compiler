//
// Created by bennet.vella on 12/04/2019.
//

#ifndef COMPILER_ASTINTEGERLITERALEXPRNODE_H
#define COMPILER_ASTINTEGERLITERALEXPRNODE_H

#include "../ASTFactorExprNode.h"

class ASTIntegerLiteralExprNode : public ASTFactorExprNode {
public:
    ASTIntegerLiteralExprNode(float p_val);
    virtual ~ASTIntegerLiteralExprNode();

    int val;

    void PrintInfo (int p_level);
    void Accept (Visitor * v);
};
#endif //COMPILER_ASTINTEGERLITERALEXPRNODE_H
