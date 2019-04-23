//
// Created by bennet.vella on 27/03/2019.
//

#ifndef COMPILER_ASTFUNCTIONNODE_H
#define COMPILER_ASTFUNCTIONNODE_H


#include "../ASTNode.h"
#include "ASTStatementNode.h"
#include "ASTBlockNode.h"
#include <string>
namespace AST {
    class ASTFunctionNode : public ASTStatementNode {
    public:
        ASTFunctionNode();
        virtual ~ASTFunctionNode();

        std::string m_identifier;
        // std::vector< TODO Use a hashmap object to store parameters?
        std::string m_type;
        ASTBlockNode *block;

        void PrintInfo(int p_level) override;
        void Accept(Visitor *v) override;
    };
}

#endif //COMPILER_ASTFUNCTIONNODE_H
