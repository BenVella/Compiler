//
// Created by bennet.vella on 12/04/2019.
//

#ifndef COMPILER_ASTFLOATLITERALEXPRNODE_H
#define COMPILER_ASTFLOATLITERALEXPRNODE_H

#include "../ASTExprNode.h"

class ASTFloatLiteralExprNode : public ASTExprNode {
public:
    ASTFloatLiteralExprNode();
    virtual ~ASTFloatLiteralExprNode();

    float val;

    void PrintInfo (int p_level) override;
    void Accept (Visitor * v) override;
};
#endif //COMPILER_ASTFLOATLITERALEXPRNODE_H
