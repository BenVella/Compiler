//
// Created by bennet.vella on 10/04/2019.
//

#ifndef COMPILER_PRINTINFOVISITOR_H
#define COMPILER_PRINTINFOVISITOR_H

#include "Visitor.h"
#include "../ASTNode/ASTExpressionNode/ASTBinaryExprNode.h"

class PrintInfoVisitor : public Visitor {
    PrintInfoVisitor ();
    void Visit(ASTNumberExprNode * p_node);
    void Visit(ASTVariableExprNode * p_node);
    void Visit(ASTBinaryExprNode * p_node);
};
#endif //COMPILER_PRINTINFOVISITOR_H
