//
// Created by bennet.vella on 10/04/2019.
//

#ifndef COMPILER_BLOCK_H
#define COMPILER_BLOCK_H

#include "../ASTNode.h"
#include "Statement.h"
#include <vector>

namespace AST {
    class Block : public Statement {
    private:
        std::vector<Statement *> *_statements;
    public:
        Block(std::vector<Statement *> *p_statements) : _statements(p_statements) {}
        Block() {
            _statements = new std::vector<Statement *> ();
        }
        ~Block() override = default;

        void Accept(Visitor& v) override { v.Visit(*this); };

        std::vector<Statement *> *getStatements() const { return _statements; }

        void addStatement(Statement *p_statement) {
            _statements->push_back(p_statement);
        }
    };
}
#endif //COMPILER_BLOCK_H
