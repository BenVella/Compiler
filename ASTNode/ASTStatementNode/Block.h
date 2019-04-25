//
// Created by bennet.vella on 10/04/2019.
//

#ifndef COMPILER_BLOCK_H
#define COMPILER_BLOCK_H

#include "../ASTNode.h"
#include "Statement.h"
#include <vector>

namespace AST {
    class Block : public ASTNode {
    public:
        Block();
        virtual ~Block();

        std::vector<Statement *> *m_statements;

        void Accept(Visitor& v) override {};
    };
}
#endif //COMPILER_BLOCK_H
