//
// Created by bennet.vella on 12/04/2019.
//

#include "ASTNumberExprNode.h"

ASTNumberExprNode::ASTNumberExprNode(ASTExprNode *p_node) {
    literalVal = p_node;
}

ASTNumberExprNode::~ASTNumberExprNode() {

}

void ASTNumberExprNode::PrintInfo(int p_level) {
    ASTExprNode::PrintInfo(p_level);
}

void ASTNumberExprNode::Accept(Visitor *v) {
    ASTExprNode::Accept(v);
}
