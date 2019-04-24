//
// Created by bennet.vella on 27/03/2019.
//

#ifndef COMPILER_ASTFUNCTIONNODE_H
#define COMPILER_ASTFUNCTIONNODE_H


#include "../ASTNode.h"
#include "Statement.h"
#include "Block.h"
#include <string>
namespace AST {
    class Function : public Statement {
    public:
        Function();
        virtual ~Function();

        std::string m_identifier;
        // std::vector< TODO Use a hashmap object to store parameters?
        std::string m_type;
        Block *block;

        void Accept(Visitor& v) override {};
    };
}

#endif //COMPILER_ASTFUNCTIONNODE_H
