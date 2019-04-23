//
// Created by bennet.vella on 25/03/2019.
//

#ifndef COMPILER_ASTNODE_H
#define COMPILER_ASTNODE_H

#include "../Visitor/Visitor.h"

namespace AST {
    class ASTNode {
    public:
        ASTNode() {}
        virtual ~ASTNode() {}
        virtual void Accept(Visitor *v) = 0;
        virtual void PrintInfo(int p_level) = 0;
    };
}

#endif //COMPILER_ASTNODE_H
