//
// Created by bennet.vella on 25/03/2019.
//

#ifndef COMPILER_ASTEXPRNODE_H
#define COMPILER_ASTEXPRNODE_H

#include <string>
#include "../ASTNode.h"

namespace AST {
    class Expr : public ASTNode {
    protected:
        Expr() = default;
    public:
        virtual ~Expr() = default;
        virtual double solve() const = 0;

        virtual void Accept(Visitor& v) = 0;
    };
}

#endif //COMPILER_ASTEXPRNODE_H
