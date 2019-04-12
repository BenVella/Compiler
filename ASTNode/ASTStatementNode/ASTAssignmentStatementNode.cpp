//
// Created by bennet.vella on 12/04/2019.
//

#include "ASTAssignmentStatementNode.h"

ASTAssignmentStatementNode::ASTAssignmentStatementNode(std::string p_name, ASTExprNode *p_node) {
    LHS = new ASTIdentifierExprNode(p_name);
    RHS = p_node;
}

ASTAssignmentStatementNode::~ASTAssignmentStatementNode() {

}

void ASTAssignmentStatementNode::PrintInfo(int p_level) {

}

void ASTAssignmentStatementNode::Accept(Visitor *v) {

}
