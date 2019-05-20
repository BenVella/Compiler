//
// Created by bennv on 5/19/2019.
//

#ifndef COMPILER_INTERPRETERVISITOR_H
#define COMPILER_INTERPRETERVISITOR_H

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

class InterpreterVisitor : public Visitor {
    struct SymbolTable {
        // Stack defining scopes holding identifier / type details
        std::vector<std::map<std::string,std::string>*> _scopeVector;

        // Tracks current working stack
        std::map<std::string,std::string> *_currentMap{};

        SymbolTable() = default;

        void Push() {
            std::map<std::string,std::string> *_tempMap;
            _tempMap = new std::map<std::string,std::string>();
            _scopeVector.push_back(_tempMap);
            _currentMap = _scopeVector.back();
        }

        bool Create(const std::string& p_name, const std::string& p_value) {
            if (_currentMap->find(p_name) == _currentMap->end()) {
                _currentMap->insert(std::make_pair(p_name, p_value));
                return true;
            }
            else {
                std::string errorText = "Element '" + p_name + "' already declared in Symbol Table!";
                Error(errorText);
                return false;
            }
        }

        void Update (const std::string& p_name, const std::string& p_value) {
            for (int i = 0; i < _scopeVector.size(); i++) {
                if (_scopeVector[i]->find(p_name) == _scopeVector[i]->end()) {
                    // No match yet
                } else {
                    _scopeVector[i]->find(p_name)->second = p_value;
                    return;
                }
            }
            // If we failed to find variable on any map
            std::string errorText = "Element '" + p_name + "' not found in Symbol Table!";
            Error(errorText);
        }

        void Pop () {
            _scopeVector.pop_back();
            _currentMap = _scopeVector.back();
        }

        void Error(const std::string& str) {
            std::cerr << "[ERROR]: " << str << std::endl;
        }

        // Returns value if found, empty if not
        std::string Lookup (const std::string& p_name) {
            for (int i = 0; i < _scopeVector.size(); i++) {
                if (_scopeVector[i]->find(p_name) == _scopeVector[i]->end()) {
                    // No match yet
                } else {
                    return _scopeVector[i]->find(p_name)->second; // return value
                }
            }
            //std::cerr << "Type name " << p_name << " not found in all of stack" << std::endl;
            return "";
        }
    };

    SymbolTable *ST;
    std::stack<std::string> boolStack;
    std::stack<float> valueStack;
    bool boolOrVal; // True if bool stack last used, false if value stack last used
    std::vector<AST::FunctionDeclare *> * functionList;
public:
    bool hasErrored;
    InterpreterVisitor() {
        ST = new SymbolTable();
        ST->Push();
        hasErrored = false;
        boolOrVal=true;
        functionList = new std::vector<AST::FunctionDeclare *> ();
    }

    ////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////// Expression //////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////

    void Visit(AST::ExprConstInt& p_node) override {
        valueStack.push(p_node.get_value());
        boolOrVal = false; // Value
    }

    void Visit(AST::ExprConstFloat& p_node) override {
        valueStack.push(p_node.get_value());
    }

    void Visit(AST::ExprVar& p_node) override {
        std::string varResult = ST->Lookup(p_node.getName());
        if (!varResult.empty()) {
            if (varResult == "true" || varResult == "false") {
                boolOrVal = true;
                boolStack.push(varResult);
            } else {
                boolOrVal = false;
                valueStack.push(std::stof(varResult));
            }
        } else {
            if (p_node.getVar().get() != nullptr) {
                p_node.getVar().get()->Accept(*this); // Set var type
            }
        }
    }

    void Visit(AST::ExprBoolOpTrue& p_node) override {
        boolStack.push("true");
        boolOrVal = true;
    }

    void Visit(AST::ExprBoolOpFalse& p_node) override {
        boolStack.push("false");
        boolOrVal = true;
    }

    void Visit(AST::ExprBinOpAdd& p_node) override {
        p_node.get_pArg1()->Accept(*this);
        p_node.get_pArg2()->Accept(*this);

        if (hasErrored)
            return;

        float val2 = valueStack.top(); valueStack.pop();
        float val1 = valueStack.top(); valueStack.pop();

        valueStack.push(val1+val2);
        boolOrVal = false;
    }

    void Visit(AST::ExprBinOpSub& p_node) override {
        p_node.get_pArg1()->Accept(*this);
        p_node.get_pArg2()->Accept(*this);

        if (hasErrored)
            return;

        float val2 = valueStack.top(); valueStack.pop();
        float val1 = valueStack.top(); valueStack.pop();

        valueStack.push(val1-val2);
        boolOrVal = false;
    }

    void Visit(AST::ExprBinOpMul& p_node) override {
        p_node.get_pArg1()->Accept(*this);
        p_node.get_pArg2()->Accept(*this);

        if (hasErrored)
            return;

        float val2 = valueStack.top(); valueStack.pop();
        float val1 = valueStack.top(); valueStack.pop();

        valueStack.push(val1*val2);
        boolOrVal = false;
    }

    void Visit(AST::ExprBinOpDiv& p_node) override {
        p_node.get_pArg1()->Accept(*this);
        p_node.get_pArg2()->Accept(*this);

        if (hasErrored)
            return;

        float val2 = valueStack.top(); valueStack.pop();
        float val1 = valueStack.top(); valueStack.pop();

        if (val2 == 0) {
            std::string errorText = "Dividing by 0 is not allowed.  Runtime Error!";
            Error (errorText);
        } else {
            valueStack.push(val1 / val2);
            boolOrVal = false;
        }
    }

    void Visit(AST::ExprBinOpSmaller& p_node) override {
        p_node.get_pArg1()->Accept(*this);
        p_node.get_pArg2()->Accept(*this);

        if (hasErrored)
            return;

        float val2 = valueStack.top(); valueStack.pop();
        float val1 = valueStack.top(); valueStack.pop();

        boolStack.push(val1 < val2 ? "true" : "false");
        boolOrVal = true;
    }

    void Visit(AST::ExprBinOpGreater& p_node) override {
        p_node.get_pArg1()->Accept(*this);
        p_node.get_pArg2()->Accept(*this);

        if (hasErrored)
            return;

        float val2 = valueStack.top(); valueStack.pop();
        float val1 = valueStack.top(); valueStack.pop();

        boolStack.push(val1 > val2 ? "true" : "false");
        boolOrVal = true;
    }

    void Visit(AST::ExprUnOpNeg& p_node) override {
        p_node.get_pArg1()->Accept(*this);
        if (boolOrVal) {
             if (boolStack.top() == "true") {
                 boolStack.pop();
                 boolStack.push("false");
             } else {
                 boolStack.pop();
                 boolStack.push("true");
             }
        } else {
            float tempVal = valueStack.top();
            valueStack.pop();
            valueStack.push(-tempVal);
        }
    }

    ////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////// Statements //////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////

    void Visit(AST::Assignment& p_node) override {
        // Interpret expression
        p_node.getExpr()->Accept(*this);

        // Assign result to node name
        if (boolOrVal) {
            ST->Update(p_node.getName(), boolStack.top());
            boolStack.pop();
        } else {
            ST->Update(p_node.getName(), std::to_string(valueStack.top()));
            valueStack.pop();
        }
    }

    void Visit(AST::VarDeclare& p_node) override {
        p_node.getExpr()->Accept(*this);

        // Assign result to node name
        if (boolOrVal) {
            ST->Create(p_node.getName(), boolStack.top());
            boolStack.pop();
        } else {
            ST->Create(p_node.getName(), std::to_string(valueStack.top()));
            valueStack.pop();
        }
    }

    void Visit(AST::Print& p_node) override {
        p_node.getExpr()->Accept(*this);
        std::cout << "Printing Expr: ";
        if (boolOrVal) {
            std::cout << boolStack.top() << std::endl;
            boolStack.pop();
        } else {
            std::cout << valueStack.top() << std::endl;
            valueStack.pop();
        }
    }

    void Visit(AST::Return& p_node) override {
        // Compute expression and leave it for something else to handle
        p_node.getExpr()->Accept(*this);
    }

    void Visit(AST::If& p_node) override {
        // Compute expression first before checking
        p_node.getExpr()->Accept(*this);

        if (boolOrVal) { // It's a boolean
            if (boolStack.top() == "true") { // If true execute first block
                p_node.getBlock1()->Accept(*this);
            } else if (p_node.getBlock2() != nullptr) { // If not true but second block exists execute it instead
                p_node.getBlock2()->Accept(*this);
            }

            boolStack.pop();
        } else { // It's a float (or int) value
            if (valueStack.top() != 0) { // If not zero execute first block
                p_node.getBlock1()->Accept(*this);
            } else if (p_node.getBlock2() != nullptr) { // If zero and second block exists execute it instead
                p_node.getBlock2()->Accept(*this);
            }

            valueStack.pop();
        }
    }

    void Visit(AST::Block& p_node) override {
        ST->Push();
        for (auto *stmt : *p_node.getStatements()) {
            stmt->Accept(*this);
        }
        ST->Pop();
    }

    void Visit(AST::For& p_node) override {
        bool keepLooping = true;
        // Execute a var declaration if one exists
        if (p_node.getVar() != nullptr)
            p_node.getVar()->Accept(*this);

        while (keepLooping) {
            // Run the expression
            p_node.getExpr()->Accept(*this);

            if (boolOrVal) { // It's a boolean
                keepLooping = boolStack.top() == "true";
                boolStack.pop();
            } else {
                keepLooping = valueStack.top() != 0;
                valueStack.pop();
            }

            if (keepLooping) { // If code still active after check, trigger block statements
                p_node.getBlock()->Accept(*this);
            }

            if (p_node.getAssign() != nullptr) // User entered their own condition
                p_node.getAssign()->Accept(*this);
            else {                            // No user condition specified, we keep looping
                boolStack.push("true");
            }
        }
    }

    bool functionActive = false;
    std::queue<std::string> paramQueue;
    void Visit(AST::FunctionCall& p_node) override {
        // Locate and setup required function
        AST::FunctionDeclare *pFunc = nullptr;
        // Find required function declaration
        for (auto tempFunc : *functionList) {
            if (tempFunc->getName() == p_node.getName()) { // got it!
                pFunc = tempFunc;
                break;
            }
        }

        if (!pFunc) {
            std::string errorText = "Error locating declared function with name " + p_node.getName();
            Error(errorText);
        }

        // Register and update the params in a new scope
        ST->Push();

        // Let the interpreter know we're calling a function to run its formal params
        functionActive = true;

        pFunc->getParams()->Accept(*this); // Populate paramQueue with type:name of variables

        p_node.getParams()->Accept(*this); // Run function call params and exhaust paramQueue, filling SymbolTable

        // Function scope created, parameters populated, run block code
        pFunc->getBlock()->Accept(*this);

        functionActive = false;
        // Terminate Function Call Scope
        ST->Pop();
    }

    void Visit(AST::FunctionDeclare& p_node) override {
        // Keep track of this declared function to run it when called.
        functionList->push_back(&p_node);
    }

    // This only gets called if we're calling a function to get name and types
    void Visit(AST::FormalParams& p_node) override {
        // Populate paramQueue
        for (auto *param : *p_node.getParams()) {
            param->Accept(*this);
        }
    }

    // This only gets called if we're running a function to get name and types
    void Visit(AST::FormalParam& p_node) override {
        // Create a type : name of variable to track it, provided we're running a function, not just declaring it
        if (functionActive)
            paramQueue.push(p_node.getType() + ":" + p_node.getName());
    }

    void Visit(AST::SimpleParams& p_node) override {
        // Populate SymbolTable with matching parameter values
        for (auto *param : *p_node.getParams()) {
            param->Accept(*this);
        }
    }

    void Visit(AST::SimpleParam& p_node) override {
        // Run the expression contained to generate value on stacks
        p_node.getExpr()->Accept(*this);

        if (paramQueue.empty()) {
            Error("PARAM QUEUE IS EMPTY!!!");
        }
        // Determine what variable type and name we need
        std::string param = paramQueue.front(); paramQueue.pop();
        auto paramParts = split(param,":");
        if (paramParts[0] == "int" || paramParts[0] == "float") {
            ST->Create(paramParts[1], std::to_string(valueStack.top()));
            valueStack.pop();
        } else if (paramParts[0] == "bool") {
            ST->Create(paramParts[1], boolStack.top());
            boolStack.pop();
        }
    }

    ////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////// HELPER METHODS ////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////

    void Error(const std::string& str) {
        hasErrored=true;
        std::cerr << "[ERROR]: " << str << std::endl;
    }

    std::vector<std::string> split(const std::string& str, const std::string& delim)
    {
        std::vector<std::string> tokens;
        size_t prev = 0, pos = 0;
        do
        {
            pos = str.find(delim, prev);
            if (pos == std::string::npos) pos = str.length();
            std::string token = str.substr(prev, pos-prev);
            tokens.push_back(token);
            prev = pos + delim.length();
        }
        while (pos < str.length() && prev < str.length());
        return tokens;
    }
};
#endif //COMPILER_INTERPRETERVISITOR_H
