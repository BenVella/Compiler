//
// Created by bennet.vella on 25/03/2019.
//

#ifndef COMPILER_ASTPROGRAMNODE_H
#define COMPILER_ASTPROGRAMNODE_H

#include "ASTNode.h"
#include "ASTStatementNode/Function.h"
#include "ASTStatementNode/Statement.h"
#include <vector>

namespace AST {
    class Program : public ASTNode {
    public:
        Program() {
            functions = new std::vector<Function*>();
            main_impl = new std::vector<Statement*>();
            tempExprs = new std::vector<AST::Expr*>();
        };
        ~Program() override = default;

        std::vector<Function *> *functions;
        std::vector<Statement *> *main_impl;
        std::vector<AST::Expr*> *tempExprs;

        void Accept(Visitor *v) override {};
        void PrintInfo(int p_level) override {};
    };
}

#endif //COMPILER_ASTPROGRAMNODE_H
