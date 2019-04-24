//
// Created by bennet.vella on 25/03/2019.
//

#ifndef COMPILER_ASTIFSTATEMENTNODE_H
#define COMPILER_ASTIFSTATEMENTNODE_H

#include "../ASTNode.h"
#include "Statement.h"
#include "../../Visitor/Visitor.h"
#include "../ASTExpressionNode/Expr.h"
namespace AST {
    class If : public Statement {
    public:
        If();
        virtual ~If();

        AST::Expr *condition = nullptr;
        ASTNode *LHS = nullptr;
        ASTNode *RHS = nullptr;

        void Accept(Visitor *v) override {};
        void PrintInfo(int p_level) override {};
    };
}
#endif //COMPILER_ASTIFSTATEMENTNODE_H