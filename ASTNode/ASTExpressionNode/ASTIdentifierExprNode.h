//
// Created by bennet.vella on 12/04/2019.
//

#ifndef COMPILER_ASTIDENTIFIEREXPRNODE_H
#define COMPILER_ASTIDENTIFIEREXPRNODE_H

#include "ASTExprNode.h"

class ASTIdentifierExprNode : public ASTExprNode {
public:
    ASTIdentifierExprNode(std::string p_name);

    virtual ~ASTIdentifierExprNode();

    std::string name;         // Holds identifier name

    void PrintInfo (int p_level) override;
    void Accept (Visitor * v) override;
};
#endif //COMPILER_ASTIDENTIFIEREXPRNODE_H
