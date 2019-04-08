//
// Created by bennet.vella on 25/03/2019.
//

#ifndef COMPILER_VISITOR_H
#define COMPILER_VISITOR_H


#include "ASTNode/ASTNode.h"

class Visitor {
public:
    virtual void Visit(ASTNode * e) = 0;
    virtual void Visit(ASTStatementNode * e) = 0;
    virtual void Visit(ASTExprNode * e) = 0;
    virtual void Visit(ASTIfNode * e) = 0;
    virtual void Visit(ASTReturnNode * e) = 0;
    virtual void Visit(ASTVariableNode * e) = 0;
    virtual void Visit(ASTFunctionNode * e) = 0;

};


#endif //COMPILER_VISITOR_H
