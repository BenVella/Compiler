//
// Created by bennet.vella on 25/03/2019.
//

#ifndef COMPILER_ASTPROGRAMNODE_H
#define COMPILER_ASTPROGRAMNODE_H

#include "ASTNode.h"
#include "ASTStatementNode/ASTFunctionNode.h"
#include "ASTStatementNode/ASTStatementNode.h"
#include <vector>

namespace AST {
    class ASTProgramNode : public ASTNode {
    public:
        ASTProgramNode();
        virtual ~ASTProgramNode();

        std::vector<ASTFunctionNode *> *functions;
        std::vector<ASTStatementNode *> *main_impl;

        void Accept(Visitor *v) override;
        void PrintInfo(int p_level) override;
    };
}

#endif //COMPILER_ASTPROGRAMNODE_H
