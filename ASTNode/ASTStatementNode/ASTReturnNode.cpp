//
// Created by bennet.vella on 12/04/2019.
//

#include "ASTReturnNode.h"

ASTReturnNode::ASTReturnNode(ASTExprNode* p_node) {
    LHS = p_node;
}

void ASTReturnNode::Accept(Visitor *v) {

}

void ASTReturnNode::PrintInfo(int p_level) {

}
