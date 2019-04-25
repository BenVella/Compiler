//
// Created by bennet.vella on 25/03/2019.
//

#ifndef COMPILER_ASTNODE_H
#define COMPILER_ASTNODE_H

#include "../Visitor/Visitor.h"

namespace AST {
    class ASTNode {
    public:
        ASTNode() = default;
        virtual ~ASTNode() = default;

        virtual void Accept(Visitor& v) = 0;
    };
}

#endif //COMPILER_ASTNODE_H
