//
// Created by bennet.vella on 12/04/2019.
//
#include "ASTProgramNode.h"

ASTProgramNode::ASTProgramNode () {
        functions = new std::vector<ASTFunctionNode *>();
        main_impl = new std::vector<ASTStatementNode *>();
}

ASTProgramNode::~ASTProgramNode() {}

void ASTProgramNode::Accept(Visitor *v) {
}

void ASTProgramNode::PrintInfo(int p_level) {
}


