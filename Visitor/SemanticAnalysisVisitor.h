//
// Created by bennv on 5/8/2019.
//

#ifndef COMPILER_SEMANTICANALYSISVISITOR_H
#define COMPILER_SEMANTICANALYSISVISITOR_H

#include <vector>
#include <stack>
#include <map>
#include <iostream>
#include <queue>
#include "Visitor.h"
#include "../ASTNode/ASTExpressionNode/Data/ExprConstInt.h"
#include "../ASTNode/ASTExpressionNode/Data/ExprConstFloat.h"
#include "../ASTNode/ASTExpressionNode/Data/ExprVar.h"
#include "../ASTNode/ASTExpressionNode/Boolean/ExprBoolOpTrue.h"
#include "../ASTNode/ASTExpressionNode/Boolean/ExprBoolOpFalse.h"
#include "../ASTNode/ASTExpressionNode/Binary/ExprBinOpAdd.h"
#include "../ASTNode/ASTExpressionNode/Binary/ExprBinOpSub.h"
#include "../ASTNode/ASTExpressionNode/Binary/ExprBinOpMul.h"
#include "../ASTNode/ASTExpressionNode/Binary/ExprBinOpDiv.h"
#include "../ASTNode/ASTExpressionNode/Binary/ExprBinOpSmaller.h"
#include "../ASTNode/ASTExpressionNode/Binary/ExprBinOpGreater.h"
#include "../ASTNode/ASTExpressionNode/Unary/ExprUnOpNeg.h"
#include "../ASTNode/ASTStatementNode/Assignment.h"
#include "../ASTNode/ASTStatementNode/VarDeclare.h"
#include "../ASTNode/ASTStatementNode/Print.h"
#include "../ASTNode/ASTStatementNode/Return.h"
#include "../ASTNode/ASTStatementNode/If.h"
#include "../ASTNode/ASTStatementNode/For.h"
#include "../ASTNode/ASTExpressionNode/FunctionCall.h"
#include "../ASTNode/ASTStatementNode/FunctionDeclare.h"
#include "../ASTNode/ASTStatementNode/FormalParam.h"
#include "../ASTNode/ASTStatementNode/FormalParams.h"
#include "../ASTNode/ASTStatementNode/SimpleParam.h"
#include "../ASTNode/ASTStatementNode/SimpleParams.h"

class SemanticAnalysisVisitor : public Visitor {
    struct SymbolTable {
        // Stack defining scopes holding identifier / type details
        std::vector<std::map<std::string,std::string>*> _scopeVector;

        // Tracks current working stack
        std::map<std::string,std::string> *_currentMap;

        SymbolTable() = default;

        void Push() {
            std::map<std::string,std::string> *_tempMap;
            _tempMap = new std::map<std::string,std::string>();
            _scopeVector.push_back(_tempMap);
            _currentMap = _scopeVector.back();
        }

        bool Insert(std::string p_name, std::string p_type) {
            if (_currentMap->find(p_name) == _currentMap->end()) {
                _currentMap->insert(std::make_pair(p_name, p_type));
                return true;
            }
            else {
                std::cerr << "Element already declared in Symbol Table!" << std::endl;
                return false;
            }
        }

        // Returns type if found, empty if not
        std::string Lookup (std::string p_name) {
            for (int i = _scopeVector.size()-1; i >= 0; i--) {
                if (_scopeVector[i]->find(p_name) == _scopeVector[i]->end()) {
                    // No match yet
                } else {
                    return _scopeVector[i]->find(p_name)->second; // return var type
                }
            }
            std::cerr << "Type name " << p_name << " not found in all of stack" << std::endl;
            return "";
        }

        void Pop () {
            _scopeVector.pop_back();
            delete _currentMap;
            _currentMap = _scopeVector.back();
        }
    };

    SymbolTable *ST;
    std::stack<std::string> typeStack;
    std::vector<AST::FunctionDeclare *> * functionList;
public:
    bool hasErrored;
    SemanticAnalysisVisitor() {
        ST = new SymbolTable();
        ST->Push();
        hasErrored = false;
        functionList = new std::vector<AST::FunctionDeclare *> ();
    }

    ////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////// Expression //////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////

    void Visit(AST::ExprConstInt& p_node) override {
        typeStack.push("int");
    }

    void Visit(AST::ExprConstFloat& p_node) override {
        typeStack.push("float");
    }

    void Visit(AST::ExprVar& p_node) override {
        if (ST->Lookup(p_node.getName()) == "") {
            std::string errorText = "Var '" + p_node.getName() + "' not found in SymbolTable!";
            Error(errorText);
        } else {
            if (ST->Lookup(p_node.getName()) != "") {
                typeStack.push(ST->Lookup(p_node.getName()));
            } else {
                std::string errorText = "Var '" + p_node.getName() + "' not found in SymbolTable!";
                Error(errorText);
            }
        }
    }

    void Visit(AST::ExprBoolOpTrue& p_node) override {
        typeStack.push("bool");
    }

    void Visit(AST::ExprBoolOpFalse& p_node) override {
        typeStack.push("bool");
    }

    void Visit(AST::ExprBinOpAdd& p_node) override {
        p_node.get_pArg1()->Accept(*this);
        p_node.get_pArg2()->Accept(*this);

        CompareBinTopStackTypes();
    }

    void Visit(AST::ExprBinOpSub& p_node) override {
        p_node.get_pArg1()->Accept(*this);
        p_node.get_pArg2()->Accept(*this);

        CompareBinTopStackTypes();
    }

    void Visit(AST::ExprBinOpMul& p_node) override {
        p_node.get_pArg1()->Accept(*this);
        p_node.get_pArg2()->Accept(*this);

        CompareBinTopStackTypes();
    }

    void Visit(AST::ExprBinOpDiv& p_node) override {
        p_node.get_pArg1()->Accept(*this);
        p_node.get_pArg2()->Accept(*this);

        CompareBinTopStackTypes();
    }

    void Visit(AST::ExprBinOpSmaller& p_node) override {
        p_node.get_pArg1()->Accept(*this);
        p_node.get_pArg2()->Accept(*this);

        CompareBinTopStackTypes();
    }

    void Visit(AST::ExprBinOpGreater& p_node) override {
        p_node.get_pArg1()->Accept(*this);
        p_node.get_pArg2()->Accept(*this);

        CompareBinTopStackTypes();
    }

    void Visit(AST::ExprUnOpNeg& p_node) override {
        p_node.get_pArg1()->Accept(*this);
    }

    ////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////// Statements //////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////

    void Visit(AST::Assignment& p_node) override {
        p_node.getExpr()->Accept(*this);
    }

    void Visit(AST::VarDeclare& p_node) override {
        if (ST->Insert(p_node.getName(),p_node.getType())) {
            p_node.getExpr()->Accept(*this);
            ValidateVarDeclareType(); // Ensure float or int and pop it
        } else {
            hasErrored = true;
        }
    }

    void Visit(AST::Print& p_node) override {
        p_node.getExpr()->Accept(*this);
        typeStack.pop();
    }

    void Visit(AST::Return& p_node) override {
        p_node.getExpr()->Accept(*this);
    }

    void Visit(AST::If& p_node) override {
        p_node.getExpr()->Accept(*this);
        typeStack.pop();
        p_node.getBlock1()->Accept(*this);
        if (p_node.getBlock2() != nullptr)
            p_node.getBlock2()->Accept(*this);
    }

    void Visit(AST::Block& p_node) override {
        ST->Push();
        for (auto *stmt : *p_node.getStatements()) {
            stmt->Accept(*this);
        }
        ST->Pop();
    }

    void Visit(AST::For& p_node) override {
        if (p_node.getVar() != nullptr)
            p_node.getVar()->Accept(*this);

        p_node.getExpr()->Accept(*this);

        if (p_node.getAssign() != nullptr)
            p_node.getAssign()->Accept(*this);
    }

    bool functionActive = false;
    std::queue<std::string> paramQueue;
    void Visit(AST::FunctionCall& p_node) override {
        // Verify function exists
        if (ST->Lookup(p_node.getName()) == "") {
            std::string errorText = "No function with name '" + p_node.getName() + "' was found.";
            Error (errorText);
            return;
        }

        // Locate and setup required function
        AST::FunctionDeclare *pFunc = nullptr;
        // Find required function declaration
        for (auto tempFunc : *functionList) {
            if (tempFunc->getName() == p_node.getName()) {// got it!
                pFunc = tempFunc;
                break;
            }
        }

        if (!pFunc) {
            std::string errorText = "Error locating declared function with name " + p_node.getName();
            Error(errorText);
            return;
        }


        // Register and update the params in a new scope
        ST->Push();

        // Let the interpreter know we're calling a function to run its formal params
        functionActive = true;
        paramQueue.empty(); // Empty before use
        pFunc->getParams()->Accept(*this); // Populate paramQueue with type:name of variables

        p_node.getParams()->Accept(*this); // Run function call params and exhaust paramQueue, filling SymbolTable

        // Function scope created, parameters populated, run block code
        pFunc->getBlock()->Accept(*this);

        functionActive = false;
        // Terminate Function Call Scope
        ST->Pop();
    }

    void Visit(AST::FunctionDeclare& p_node) override {
        if (ST->Insert(p_node.getName(), p_node.getType())) {
            p_node.getParams()->Accept(*this);
            p_node.getBlock()->Accept(*this);

            if (p_node.getType() != typeStack.top()) {
                Error("Function return type is incorrect!");
                return;
            } else {
                typeStack.pop();
            }

            // Keep track of this declared function to run it when called.
            functionList->push_back(&p_node);
        } else {
            hasErrored = true;
        }
    }

    void Visit(AST::FormalParams& p_node) override {
        for (auto *param : *p_node.getParams()) {
            if (hasErrored) return;
            param->Accept(*this);
        }
    }

    void Visit(AST::FormalParam& p_node) override {
        // Insert a type : name of variable to track it, provided we're running a function, not just declaring it
        if (functionActive)
            paramQueue.push(p_node.getType());
        else // Just run through semantic analysis of a normal declaration
            if (!ST->Insert(p_node.getName(),p_node.getType()))
                hasErrored = true;
    }

    void Visit(AST::SimpleParams& p_node) override {
        for (auto *param : *p_node.getParams()) {
            if (hasErrored) return;
            param->Accept(*this);
        }
    }

    void Visit(AST::SimpleParam& p_node) override {
        // Run the expression contained to generate type on stack
        p_node.getExpr()->Accept(*this);

        if (paramQueue.size() == 0) {
            Error("PARAM QUEUE IS EMPTY!!!");
            return;
        }
        // Determine what variable type and name we need
        std::string paramType = paramQueue.front(); paramQueue.pop();

        // Match the type
        if (paramType == typeStack.top()) {
            typeStack.pop();
        } else {
            Error ("Incorrect Function Call Parameter Type!");
            return;
        }
    }

    ////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////// HELPER METHODS ////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////

    void Error(std::string str) {
        hasErrored=true;
        std::cout << "[ERROR]: " << str << std::endl;
        std::cerr << "[ERROR]: " << str << std::endl;
    }

    void CompareBinTopStackTypes() {
        if (hasErrored)
            return;
        std::string pType2 = typeStack.top(); typeStack.pop();
        std::string pType1 = typeStack.top(); typeStack.pop();

        if (pType1 != pType2) {
            std::string errorText = "Type mismatch! Expected: " + pType1 + "; Found: " + pType2;
            Error(errorText);
        } else {
            typeStack.push(pType1); // Push back matching type result as overall type
        }
    }

    void ValidateVarDeclareType() {
        if (typeStack.top() == "int" || typeStack.top() == "float" || typeStack.top() == "bool") {
            typeStack.pop(); // Valid type, pop it!
        } else {
            std::string errorText = "Type mismatch! Expected 'float' or 'int' but instead got " + typeStack.top();
            Error(errorText);
        }


    }
};

#endif //COMPILER_SEMANTICANALYSISVISITOR_H
