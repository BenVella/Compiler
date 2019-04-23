//
// Created by bennet.vella on 12/04/2019.
//

#ifndef COMPILER_ASTFLOATLITERALEXPRNODE_H
#define COMPILER_ASTFLOATLITERALEXPRNODE_H

#include "../ASTFactorExprNode.h"

class ASTFloatLiteralExprNode : public ASTFactorExprNode {
public:
    ASTFloatLiteralExprNode(float p_val);
    virtual ~ASTFloatLiteralExprNode();

    float val;

    void PrintInfo (int p_level);
    void Accept (Visitor * v);
};
#endif //COMPILER_ASTFLOATLITERALEXPRNODE_H
