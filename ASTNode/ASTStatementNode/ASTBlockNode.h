//
// Created by bennet.vella on 10/04/2019.
//

#ifndef COMPILER_ASTBLOCKNODE_H
#define COMPILER_ASTBLOCKNODE_H

#include "../ASTNode.h"
#include "ASTStatementNode.h"
#include <vector>

namespace AST {
    class ASTBlockNode : public ASTNode {
    public:
        ASTBlockNode();
        virtual ~ASTBlockNode();

        std::vector<ASTStatementNode *> *m_statements;

        void PrintInfo(int p_level) override;
        void Accept(Visitor *v) override;
    };
}
#endif //COMPILER_ASTBLOCKNODE_H
