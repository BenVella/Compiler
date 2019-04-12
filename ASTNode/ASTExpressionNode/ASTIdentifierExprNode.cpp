//
// Created by bennet.vella on 12/04/2019.
//

#include "ASTIdentifierExprNode.h"

ASTIdentifierExprNode::ASTIdentifierExprNode(std::string p_name) {
    name = p_name;
}

ASTIdentifierExprNode::~ASTIdentifierExprNode() {

}

void ASTIdentifierExprNode::PrintInfo(int p_level) {
    ASTExprNode::PrintInfo(p_level);
}

void ASTIdentifierExprNode::Accept(Visitor *v) {
    ASTExprNode::Accept(v);
}
