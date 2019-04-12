//
// Created by bennet.vella on 12/04/2019.
//

#ifndef COMPILER_ASTINTEGERLITERALEXPRNODE_H
#define COMPILER_ASTINTEGERLITERALEXPRNODE_H

#include "../ASTExprNode.h"

class ASTIntegerLiteralExprNode : public ASTExprNode {
public:
    ASTIntegerLiteralExprNode();
    virtual ~ASTIntegerLiteralExprNode();

    int val;

    void PrintInfo (int p_level) override;
    void Accept (Visitor * v) override;
};
#endif //COMPILER_ASTINTEGERLITERALEXPRNODE_H
