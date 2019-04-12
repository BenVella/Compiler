//
// Created by bennet.vella on 12/04/2019.
//

#ifndef COMPILER_ASTBOOLEANLITERALEXPRNODE_H
#define COMPILER_ASTBOOLEANLITERALEXPRNODE_H

#include "../ASTExprNode.h"

class ASTBooleanLiteralExprNode : public ASTExprNode {
public:
    ASTBooleanLiteralExprNode();
    virtual ~ASTBooleanLiteralExprNode();

    bool val;

    void PrintInfo (int p_level) override;
    void Accept (Visitor * v) override;
};
#endif //COMPILER_ASTBOOLEANLITERALEXPRNODE_H
