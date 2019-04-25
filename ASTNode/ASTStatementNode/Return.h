//
// Created by bennet.vella on 27/03/2019.
//

#ifndef COMPILER_RETURN_H
#define COMPILER_RETURN_H


#include "../ASTExpressionNode/Expr.h"
#include "Statement.h"

namespace AST {
    class Return : public Statement {
    public:
        explicit Return(Expr *p_node) : LHS(p_node) {}
        ~Return() override = default;

        AST::Expr *LHS;

        void Accept(Visitor& v) override {};
    };
}

#endif //COMPILER_RETURN_H
