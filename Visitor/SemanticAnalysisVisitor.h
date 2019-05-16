//
// Created by bennv on 5/8/2019.
//

#ifndef COMPILER_SEMANTICANALYSISVISITOR_H
#define COMPILER_SEMANTICANALYSISVISITOR_H

#include <vector>
#include <map>
#include <iostream>
#include "Visitor.h"
#include "../ASTNode/ASTExpressionNode/Data/ExprConstInt.h"
#include "../ASTNode/ASTExpressionNode/Data/ExprConstFloat.h"
#include "../ASTNode/ASTExpressionNode/Data/ExprVar.h"
#include "../ASTNode/ASTExpressionNode/Boolean/ExprBoolOpTrue.h"
#include "../ASTNode/ASTExpressionNode/Boolean/ExprBoolOpFalse.h"
#include "../ASTNode/ASTExpressionNode/Binary/ExprBinOpAdd.h"
#include "../ASTNode/ASTExpressionNode/Binary/ExprBinOpSub.h"
#include "../ASTNode/ASTExpressionNode/Binary/ExprBinOppMul.h"
#include "../ASTNode/ASTExpressionNode/Binary/ExprBinOppDiv.h"
#include "../ASTNode/ASTExpressionNode/Unary/ExprUnOpNeg.h"
#include "../ASTNode/ASTStatementNode/Assignment.h"
#include "../ASTNode/ASTStatementNode/VarDeclare.h"
#include "../ASTNode/ASTStatementNode/Print.h"
#include "../ASTNode/ASTStatementNode/Return.h"
#include "../ASTNode/ASTStatementNode/If.h"
#include "../ASTNode/ASTStatementNode/For.h"
#include "../ASTNode/ASTStatementNode/FunctionCall.h"
#include "../ASTNode/ASTStatementNode/FunctionDeclare.h"
#include "../ASTNode/ASTStatementNode/Param.h"
#include "../ASTNode/ASTStatementNode/Params.h"

class SemanticAnalysisVisitor : public Visitor {
    struct SymbolTable {
        // Stack defining scopes holding identifier / type details
        std::vector<std::map<std::string,std::string>> _scopeVector;

        // Tracks current working stack
        std::map<std::string,std::string> _currentMap;

        SymbolTable() = default;

        void Push() {
            std::map<std::string,std::string> *_tempMap;
            _tempMap = new std::map<std::string,std::string>();
            _scopeVector.push_back(*_tempMap);
            _currentMap = _scopeVector.back();
        }

        void Insert(std::string p_name, std::string p_type) {
            _currentMap.insert(std::make_pair(p_name,p_type));
        }

        // Returns type if found, empty if not
        std::string Lookup (std::string p_name) {
            for (int i = 0; i < _scopeVector.size(); i++) {
                if (_scopeVector[i].find(p_name) == _scopeVector[i].end()) {
                    // No match yet
                } else {
                    return _scopeVector[i].find(p_name)->second;
                }
            }
            std::cerr << "Type name " << p_name << " not found in all of stack" << std::endl;
            return "";
        }

        void Pop () {
            _scopeVector.pop_back();
            _currentMap = _scopeVector.back();
        }
    };
    SymbolTable *ST;
public:
    SemanticAnalysisVisitor() {
        ST = new SymbolTable();
        ST->Push();
    }

    ////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////// Expression //////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////

    virtual void Visit(AST::ExprConstInt& p_node) override {
        // p_node.get_value();
    }

    virtual void Visit(AST::ExprConstFloat& p_node) override {
        // p_node.get_value();
    }

    virtual void Visit(AST::ExprVar& p_node) override {
        if (ST->Lookup(p_node.getName()) == "") {
            std::cout << "Variable NOT FOUND" << std::endl;
        } else {
            std::cout << "Var OK" << std::endl;
        }
    }

    virtual void Visit(AST::ExprBoolOpTrue& p_node) override {
        // true
    }

    virtual void Visit(AST::ExprBoolOpFalse& p_node) override {
        // false
    }

    virtual void Visit(AST::ExprBinOpAdd& p_node) override {
        p_node.get_pArg1()->Accept(*this);
        p_node.get_pArg2()->Accept(*this);
    }

    virtual void Visit(AST::ExprBinOpSub& p_node) override {
        p_node.get_pArg1()->Accept(*this);
        p_node.get_pArg2()->Accept(*this);
    }

    virtual void Visit(AST::ExprBinOpMul& p_node) override {
        p_node.get_pArg1()->Accept(*this);
        p_node.get_pArg2()->Accept(*this);
    }

    virtual void Visit(AST::ExprBinOpDiv& p_node) override {
        p_node.get_pArg1()->Accept(*this);
        p_node.get_pArg2()->Accept(*this);
    }

    virtual void Visit(AST::ExprUnOpNeg& p_node) override {
        p_node.get_pArg1()->Accept(*this);
    }

    ////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////// Statements //////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////

    virtual void Visit(AST::Assignment& p_node) override {
        // p_node.getName();
        p_node.getExpr()->Accept(*this);
    }

    virtual void Visit(AST::VarDeclare& p_node) override {
        // p_node.getName();
        // p_node.getType();
        ST->Insert(p_node.getName(),p_node.getType());

        p_node.getExpr()->Accept(*this);
    }

    virtual void Visit(AST::Print& p_node) override {
        p_node.getExpr()->Accept(*this);
    }

    virtual void Visit(AST::Return& p_node) override {
        p_node.getExpr()->Accept(*this);
    }

    virtual void Visit(AST::If& p_node) override {
        p_node.getExpr()->Accept(*this);
        p_node.getBlock1()->Accept(*this);
        if (p_node.getBlock2() != NULL)
            p_node.getBlock2()->Accept(*this);
    }

    virtual void Visit(AST::Block& p_node) override {
        for (auto *stmt : *p_node.getStatements()) {
            stmt->Accept(*this);
        }
    }

    virtual void Visit(AST::For& p_node) override {
        if (p_node.getVar() != NULL)
            p_node.getVar()->Accept(*this);

        p_node.getExpr()->Accept(*this);

        if (p_node.getAssign() != NULL)
            p_node.getAssign()->Accept(*this);
    }

    virtual void Visit(AST::FunctionCall& p_node) override {
        p_node.getParams()->Accept(*this);
    }

    virtual void Visit(AST::FunctionDeclare& p_node) override {
        ST->Insert(p_node.getName(), p_node.getType());
        p_node.getParams()->Accept(*this);
        p_node.getBlock()->Accept(*this);
    }

    virtual void Visit(AST::Params& p_node) override {
        for (auto *param : *p_node.getParams()) {
            param->Accept(*this);
        }
    }

    virtual void Visit(AST::Param& p_node) override {
        ST->Insert(p_node.getName(),p_node.getType());
    }
};

#endif //COMPILER_SEMANTICANALYSISVISITOR_H