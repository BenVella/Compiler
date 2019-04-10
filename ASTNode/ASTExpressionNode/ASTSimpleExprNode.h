//
// Created by bennet.vella on 10/04/2019.
//

#ifndef COMPILER_ASTSIMPLEEXPRNODE_H
#define COMPILER_ASTSIMPLEEXPRNODE_H

#include "ASTExprNode.h"

class ASTSimpleExprNode : public ASTExprNode {
public:
    ASTSimpleExprNode();
    virtual ~ASTSimpleExprNode();



    void PrintInfo (int p_level) override;
    void Accept (Visitor * v) override;
};
#endif //COMPILER_ASTSIMPLEEXPRNODE_H
