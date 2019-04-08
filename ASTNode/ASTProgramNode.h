//
// Created by bennet.vella on 25/03/2019.
//

#ifndef COMPILER_ASTPROGRAMNODE_H
#define COMPILER_ASTPROGRAMNODE_H

#include "ASTStatementNode/ASTStatementNode.h"
#include "ASTNode.h"
#include "ASTStatementNode/ASTFunctionNode.h"
#include <iostream>
#include <vector>

class ASTProgramNode : public ASTNode {
public:
    ASTProgramNode();
    virtual ~ASTProgramNode();

    std::vector<ASTFunctionNode *> * functions;
    std::vector<ASTStatementNode *> * main_impl;
};

#endif //COMPILER_ASTPROGRAMNODE_H
