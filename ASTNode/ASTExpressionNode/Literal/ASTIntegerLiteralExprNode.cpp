//
// Created by bennet.vella on 12/04/2019.
//

#include "ASTIntegerLiteralExprNode.h"

ASTIntegerLiteralExprNode::ASTIntegerLiteralExprNode(float p_val) {
    val = static_cast<int>(p_val);
}

ASTIntegerLiteralExprNode::~ASTIntegerLiteralExprNode() {

}

void ASTIntegerLiteralExprNode::PrintInfo(int p_level) {
    ASTExprNode::PrintInfo(p_level);
}

void ASTIntegerLiteralExprNode::Accept(Visitor *v) {
    ASTExprNode::Accept(v);
}
