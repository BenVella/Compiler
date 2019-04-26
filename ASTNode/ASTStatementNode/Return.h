//
// Created by bennet.vella on 27/03/2019.
//

#ifndef COMPILER_RETURN_H
#define COMPILER_RETURN_H


#include "../ASTExpressionNode/Expr.h"
#include "Statement.h"

namespace AST {
    class Return : public Statement {
    private:
        AST::Expr *_expr;
    public:
        explicit Return(Expr *p_node) : _expr(p_node) {}
        ~Return() override = default;

        void Accept(Visitor& v) override { v.Visit(*this); };

        Expr *getExpr() const {
            return _expr;
        }
    };
}

#endif //COMPILER_RETURN_H
