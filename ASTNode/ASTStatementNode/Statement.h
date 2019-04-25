//
// Created by bennet.vella on 25/03/2019.
//

#ifndef COMPILER_STATEMENT_H
#define COMPILER_STATEMENT_H

#include "../ASTNode.h"

namespace AST {
    class Statement : public ASTNode {
    public:
        Statement() {}
        virtual ~Statement() {}

        virtual void Accept(Visitor& v) = 0;
    };
}

#endif //COMPILER_STATEMENT_H
