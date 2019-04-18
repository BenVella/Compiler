//
// Created by bennet.vella on 12/04/2019.
//

#include "ASTUnaryExprNode.h"

ASTUnaryExprNode::ASTUnaryExprNode() {

}

ASTUnaryExprNode::~ASTUnaryExprNode() {

}

void ASTUnaryExprNode::PrintInfo(int p_level) {
    ASTExprNode::PrintInfo(p_level);
}

void ASTUnaryExprNode::Accept(Visitor *v) {
    ASTExprNode::Accept(v);
}
