//
// Created by bennet.vella on 27/03/2019.
//

#ifndef COMPILER_ASTRETURNSTATEMENTNODE_H
#define COMPILER_ASTRETURNSTATEMENTNODE_H


#include "../ASTExpressionNode/Expr.h"
#include "ASTStatementNode.h"

namespace AST {
    class ASTReturnNode : public ASTStatementNode {
    public:
        ASTReturnNode(Expr *p_node);
        virtual ~ASTReturnNode() {}

        AST::Expr *LHS;

        void Accept(Visitor *v) override;
        void PrintInfo(int p_level) override;
    };
}

#endif //COMPILER_ASTRETURNSTATEMENTNODE_H
