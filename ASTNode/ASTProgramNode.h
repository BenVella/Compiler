//
// Created by bennet.vella on 25/03/2019.
//

#ifndef COMPILER_ASTPROGRAMNODE_H
#define COMPILER_ASTPROGRAMNODE_H

#include "ASTStatementNode.h"
#include "ASTNode.h"

class ASTProgramNode : public ASTNode {
public:
    ASTProgramNode();
    virtual ~ASTProgramNode();

    std::vector<ASTFunctionNode *> * functions;
    std::vector<ASTStatementNode *> * main_impl;
};

#endif //COMPILER_ASTPROGRAMNODE_H
