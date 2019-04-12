//
// Created by bennet.vella on 10/04/2019.
//

#ifndef COMPILER_ASTASSIGNMENTSTATEMENTNODE_H
#define COMPILER_ASTASSIGNMENTSTATEMENTNODE_H

#include "ASTStatementNode.h"

class ASTAssignmentStatementNode : public ASTStatementNode {
public:
    std::string identifier;

};
#endif //COMPILER_ASTASSIGNMENTSTATEMENTNODE_H
