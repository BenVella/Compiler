//
// Created by bennet.vella on 27/03/2019.
//

#ifndef COMPILER_ASTRETURNSTATEMENTNODE_H
#define COMPILER_ASTRETURNSTATEMENTNODE_H


#include "../ASTExpressionNode/Expr.h"
#include "Statement.h"

namespace AST {
    class Return : public Statement {
    public:
        explicit Return(Expr *p_node) : LHS(p_node) {}
        ~Return() override = default;

        AST::Expr *LHS;

        void Accept(Visitor *v) override {};
        void PrintInfo(int p_level) override {};
    };
}

#endif //COMPILER_ASTRETURNSTATEMENTNODE_H
