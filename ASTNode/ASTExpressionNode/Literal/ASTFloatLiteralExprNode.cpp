//
// Created by bennet.vella on 12/04/2019.
//

#include "ASTFloatLiteralExprNode.h"

ASTFloatLiteralExprNode::ASTFloatLiteralExprNode(float p_val) {
    val = p_val;
}

ASTFloatLiteralExprNode::~ASTFloatLiteralExprNode() {

}

void ASTFloatLiteralExprNode::PrintInfo(int p_level) {
    ASTExprNode::PrintInfo(p_level);
}

void ASTFloatLiteralExprNode::Accept(Visitor *v) {
    ASTExprNode::Accept(v);
}
