//
// Created by bennet.vella on 25/03/2019.
//

#ifndef COMPILER_IF_H
#define COMPILER_IF_H

#include "../ASTNode.h"
#include "Statement.h"
#include "../../Visitor/Visitor.h"
#include "../ASTExpressionNode/Expr.h"
namespace AST {
    class If : public Statement {
    private:
        AST::Expr *_expr;
        ASTNode *_block1;
        ASTNode *_block2;
    public:
        If(AST::Expr * p_expr, ASTNode *pBlock) : _expr(p_expr), _block1(pBlock) {}
        If(AST::Expr * p_expr, ASTNode *pBlock1, ASTNode *pBlock2) : _expr(p_expr), _block1(pBlock1), _block2(pBlock2) {}
        ~If() override = default;

        void Accept(Visitor& v) override { v.Visit(*this); };

        Expr *getExpr() const {return _expr;}
        ASTNode *getBlock1() const {return _block1;}
        ASTNode *getBlock2() const {return _block2;}
    };
}
#endif //COMPILER_IF_H