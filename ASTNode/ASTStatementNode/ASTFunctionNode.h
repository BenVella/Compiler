//
// Created by bennet.vella on 27/03/2019.
//

#ifndef COMPILER_ASTFUNCTIONNODE_H
#define COMPILER_ASTFUNCTIONNODE_H


#include "../ASTNode.h"
#include "ASTStatementNode.h"

class ASTFunctionNode: public ASTStatementNode {
public:
    ASTFunctionNode();
    virtual ~ASTFunctionNode();



    void PrintInfo (int p_level) override;
    void Accept (Visitor * v) override;
};


#endif //COMPILER_ASTFUNCTIONNODE_H
