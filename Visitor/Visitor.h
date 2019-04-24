//
// Created by bennet.vella on 25/03/2019.
//

#ifndef COMPILER_VISITOR_H
#define COMPILER_VISITOR_H

/*#include "../ASTNode/ASTNode.h"
#include "../ASTNode/Program.h"
#include "../ASTNode/Statement/Statement.h"
#include "../ASTNode/Statement/If.h"
#include "../ASTNode/Statement/Return.h"
#include "../ASTNode/ASTExpressionNode/ASTFactorExprNode.h"
#include "../ASTNode/ASTExpressionNode/ASTTermExprNode.h"
#include "../ASTNode/ASTExpressionNode/ASTUnaryExprNode.h"
#include "../ASTNode/ASTExpressionNode/ASTBinaryExprNode.h"*/

class Visitor {
/*public:
    virtual void Visit(ASTNode * e) = 0;
    virtual void Visit(Program * e) = 0;
    virtual void Visit(Statement * e) = 0;
    virtual void Visit(Block * e) = 0;
    virtual void Visit(Function * e) = 0;
    virtual void Visit(If * e) = 0;
    virtual void Visit(Return * e) = 0;
    virtual void Visit(ASTVariableNode * e) = 0;
    virtual void Visit(Expr * e) = 0;
    virtual void Visit(ASTFactorExprNode * e) = 0;
    virtual void Visit(ASTSimpleExprNode * e) = 0;
    virtual void Visit(ASTTermExprNode * e) = 0;
    virtual void Visit(ASTUnaryExprNode * e) = 0;
    virtual void Visit(ASTBinaryExprNode * e) = 0;

    ASTNode::Accept(Visitor &v) { v.Visit(this); }
    Program::Accept(Visitor &v) { v.Visit(this); }

    ASTSStatementNode::Accept(Visitor &v) { v.Visit(this); }
    ASTVariableNode::Accept(Visitor &v) { v.Visit(this); }
    Return::Accept(Visitor &v) { v.Visit(this); }
    If::Accept(Visitor &v) { v.Visit(this); }
    Function::Accept(Visitor &v) { v.Visit(this); }
    Block::Accept(Visitor &v) { v.Visit(this); }

    Expr::Accept(Visitor &v) { v.Visit(this); }
    ASTBinaryExprNode::Accept(Visitor &v) { v.Visit(this); }
    ASTUnaryExprNode::Accept(Visitor &v) { v.Visit(this); }
    ASTFactorExprNode::Accept(Visitor &v) { v.Visit(this); }
    ASTTermExprNode::Accept(Visitor &v) { v.Visit(this); }
    ASTSimpleExprNode::Accept(Visitor &v) { v.Visit(this); }*/
};

#endif //COMPILER_VISITOR_H
