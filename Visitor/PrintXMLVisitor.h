//
// Created by bennet.vella on 10/04/2019.
//

#ifndef COMPILER_PRINTINFOVISITOR_H
#define COMPILER_PRINTINFOVISITOR_H

#include <iostream>
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

class PrintXMLVisitor : public Visitor {
private:
    int m_indent = 0;

    std::string indentTabs() {
        std::string tabs = "";
        for (int t=0; t<m_indent; t++) tabs.append("   ");
        return tabs;
    }
public:
    void Visit(AST::ExprConstInt& p_node) override {
        std::cout << indentTabs() << "<ExprConstInt>" << p_node.get_value() << "</ExprConstInt>" << std::endl;
    }

    void Visit(AST::ExprConstFloat& p_node) override {
        std::cout << indentTabs() << "<ExprConstFloat>" << p_node.get_value() << "</ExprConstFloat>" << std::endl;
    }

    void Visit(AST::ExprVar& p_node) override {
        std::cout << indentTabs() <<  "<ExprVar>" << p_node.getName() << "</ExprVar>" << std::endl;
    }

    void Visit(AST::ExprBoolOpTrue& p_node) override {
        std::cout << indentTabs() <<  "<ExprBoolOp>true</ExprBoolOp>" << std::endl;
    }

    void Visit(AST::ExprBoolOpFalse& p_node) override {
        std::cout << indentTabs() <<  "<ExprBoolOp>false</ExprBoolOp>" << std::endl;
    }

    void Visit(AST::ExprBinOpAdd& p_node) override {
        std::cout << indentTabs() << "<ExprBinOpAdd>" << std::endl;
        m_indent++;
        p_node.get_pArg1()->Accept(*this);
        p_node.get_pArg2()->Accept(*this);
        m_indent--;
        std::cout << indentTabs() << "</ExprBinOpAdd>" << std::endl;
    }

    void Visit(AST::ExprBinOpSub& p_node) override {
        std::cout << indentTabs() << "<ExprBinOpSub>" << std::endl;
        m_indent++;
        p_node.get_pArg1()->Accept(*this);
        p_node.get_pArg2()->Accept(*this);
        m_indent--;
        std::cout << indentTabs() << "</ExprBinOpSub>" << std::endl;
    }

    void Visit(AST::ExprBinOpMul& p_node) override {
        std::cout << indentTabs() << "<ExprBinOpMul>" << std::endl;
        m_indent++;
        p_node.get_pArg1()->Accept(*this);
        p_node.get_pArg2()->Accept(*this);
        m_indent--;
        std::cout << indentTabs() << "</ExprBinOpMul>" << std::endl;
    }

    void Visit(AST::ExprBinOpDiv& p_node) override {
        std::cout << indentTabs() << "<ExprBinOpDiv>" << std::endl;
        m_indent++;
        p_node.get_pArg1()->Accept(*this);
        p_node.get_pArg2()->Accept(*this);
        m_indent--;
        std::cout << indentTabs() << "</ExprBinOpDiv>" << std::endl;
    }
    
    void Visit(AST::ExprBinOpSmaller& p_node) override {
        std::cout << indentTabs() << "<ExprBinOpSmaller>" << std::endl;
        m_indent++;
        p_node.get_pArg1()->Accept(*this);
        p_node.get_pArg2()->Accept(*this);
        m_indent--;
        std::cout << indentTabs() << "</ExprBinOpSmaller>" << std::endl;
    }
    
    void Visit(AST::ExprBinOpGreater& p_node) override {
        std::cout << indentTabs() << "<ExprBinOpGreater>" << std::endl;
        m_indent++;
        p_node.get_pArg1()->Accept(*this);
        p_node.get_pArg2()->Accept(*this);
        m_indent--;
        std::cout << indentTabs() << "</ExprBinOpGreater>" << std::endl;
    }

    void Visit(AST::ExprUnOpNeg& p_node) override {
        std::cout << indentTabs() << "<ExprUnOpNeg>" << std::endl;
        m_indent++;
        p_node.get_pArg1()->Accept(*this);
        m_indent--;
        std::cout << indentTabs() << "</ExprUnOpNeg>" << std::endl;
    }

    ////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////// Statements //////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////

    void Visit(AST::Assignment& p_node) override {
        std::cout << indentTabs() << "<Assignment>" << std::endl;
        m_indent++;
        std::cout << indentTabs() << "<Identifier>" << p_node.getName() << "</Identifier>" << std::endl;
        std::cout << indentTabs() << "<Expression>" << std::endl;
        m_indent++;
        p_node.getExpr()->Accept(*this);
        m_indent--;
        std::cout<< indentTabs() << "</Expression>" << std::endl;
        m_indent--;
        std::cout << indentTabs() << "</Assignment>" << std::endl;
    }

    void Visit(AST::VarDeclare& p_node) override {
        std::cout << indentTabs() << "<VarDeclare>" << std::endl;
        m_indent++;
        std::cout << indentTabs() << "<Identifier>" << p_node.getName() << "</Identifier>" << std::endl;
        std::cout << indentTabs() << "<Type>" << p_node.getType() << "</Type>" << std::endl;
        std::cout << indentTabs() << "<Expression>" << std::endl;
        m_indent++;
        p_node.getExpr()->Accept(*this);
        m_indent--;
        std::cout<< indentTabs() << "</Expression>" << std::endl;
        m_indent--;
        std::cout << indentTabs() << "</VarDeclare>" << std::endl;
    }

    void Visit(AST::Print& p_node) override {
        std::cout << indentTabs() << "<Print>" << std::endl;
        m_indent++;
        std::cout << indentTabs() << "<Expression>" << std::endl;
        m_indent++;
        p_node.getExpr()->Accept(*this);
        m_indent--;
        std::cout<< indentTabs() << "</Expression>" << std::endl;
        m_indent--;
        std::cout << indentTabs() << "</Print>" << std::endl;
    }

    void Visit(AST::Return& p_node) override {
        std::cout << indentTabs() << "<Return>" << std::endl;
        m_indent++;
        std::cout << indentTabs() << "<Expression>" << std::endl;
        m_indent++;
        p_node.getExpr()->Accept(*this);
        m_indent--;
        std::cout<< indentTabs() << "</Expression>" << std::endl;
        m_indent--;
        std::cout << indentTabs() << "</Return>" << std::endl;
    }

    void Visit(AST::If& p_node) override {
        std::cout << indentTabs() << "<If>" << std::endl;
        m_indent++;
        std::cout << indentTabs() << "<Expression>" << std::endl;
        m_indent++;
        p_node.getExpr()->Accept(*this);
        m_indent--;
        std::cout<< indentTabs() << "</Expression>" << std::endl;
        p_node.getBlock1()->Accept(*this);
        if (p_node.getBlock2() != NULL)
            p_node.getBlock2()->Accept(*this);
        m_indent--;
        std::cout << indentTabs() << "</If>" << std::endl;
    }

    void Visit(AST::Block& p_node) override {
        std::cout << indentTabs() << "<Block>" << std::endl;
        m_indent++;
        for (auto *stmt : *p_node.getStatements()) {
            stmt->Accept(*this);
        }
        m_indent--;
        std::cout << indentTabs() << "</Block>" << std::endl;
    }

    void Visit(AST::For& p_node) override {
        std::cout << indentTabs() << "<For>" << std::endl;
        m_indent++;
        if (p_node.getVar() != NULL)
            p_node.getVar()->Accept(*this);
        std::cout << indentTabs() << "<Expression>" << std::endl;
        m_indent++;
        p_node.getExpr()->Accept(*this);
        m_indent--;
        std::cout<< indentTabs() << "</Expression>" << std::endl;
        if (p_node.getAssign() != NULL)
            p_node.getAssign()->Accept(*this);
        m_indent--;
        std::cout << indentTabs() << "</For>" << std::endl;
    }

    void Visit(AST::FunctionCall& p_node) override {
        std::cout << indentTabs() << "<FunctionCall>" << std::endl;
        m_indent++;
        std::cout << indentTabs() << "<Identifier>" << p_node.getName() << "</Identifier>" << std::endl;
        p_node.getParams()->Accept(*this);
        m_indent--;
        std::cout << indentTabs() << "</FunctionCall>" << std::endl;
    }

    void Visit(AST::FunctionDeclare& p_node) override {
        std::cout << indentTabs() << "<FunctionDeclare>" << std::endl;
        m_indent++;
        std::cout << indentTabs() << "<Identifier>" << p_node.getName() << "</Identifier>" << std::endl;
        p_node.getParams()->Accept(*this);
        std::cout << indentTabs() << "<Type>" << p_node.getType() << "</Type>" << std::endl;
        p_node.getBlock()->Accept(*this);
        m_indent--;
        std::cout << indentTabs() << "</FunctionDeclare>" << std::endl;
    }

    void Visit(AST::FormalParams& p_node) override {
        std::cout << indentTabs() << "<FormalParams>" << std::endl;
        m_indent++;
        for (auto *param : *p_node.getParams()) {
            param->Accept(*this);
        }
        m_indent--;
        std::cout << indentTabs() << "</FormalParams>" << std::endl;
    }

    void Visit(AST::FormalParam& p_node) override {
        std::cout << indentTabs() << "<FormalParam>" << std::endl;
        m_indent++;
        std::cout << indentTabs() << "<Identifier>" << p_node.getName() << "</Identifier>" << std::endl;
        std::cout << indentTabs() << "<Type>" << p_node.getType() << "</Type>" << std::endl;
        m_indent--;
        std::cout << indentTabs() << "</FormalParam>" << std::endl;
    }

    void Visit(AST::SimpleParams& p_node) override {
        std::cout << indentTabs() << "<SimpleParams>" << std::endl;
        m_indent++;
        for (auto *param : *p_node.getParams()) {
            param->Accept(*this);
        }
        m_indent--;
        std::cout << indentTabs() << "</SimpleParams>" << std::endl;
    }

    void Visit(AST::SimpleParam& p_node) override {
        std::cout << indentTabs() << "<SimpleParam>" << std::endl;
        m_indent++;
        std::cout << indentTabs() << "<Expression>" << std::endl;
        m_indent++;
        p_node.getExpr()->Accept(*this);
        m_indent--;
        std::cout<< indentTabs() << "</Expression>" << std::endl;
        m_indent--;
        std::cout << indentTabs() << "</SimpleParam>" << std::endl;
    }
};
#endif //COMPILER_PRINTINFOVISITOR_H
