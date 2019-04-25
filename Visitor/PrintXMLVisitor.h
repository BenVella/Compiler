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
#include "../ASTNode/ASTExpressionNode/Binary/ExprBinOpAdd.h"
#include "../ASTNode/ASTExpressionNode/Binary/ExprBinOpSub.h"
#include "../ASTNode/ASTExpressionNode/Binary/ExprBinOppMul.h"
#include "../ASTNode/ASTExpressionNode/Binary/ExprBinOppDiv.h"
#include "../ASTNode/ASTExpressionNode/Unary/ExprUnOpNeg.h"
#include "../ASTNode/ASTStatementNode/AssignmentStatement.h"


class PrintXMLVisitor : public Visitor {
private:
    int m_indent = 0;

    std::string indentTabs() {
        std::string tabs = "";
        for (int t=0; t<m_indent; t++) tabs.append("   ");
        return tabs;
    }
public:
    // Expressions

    virtual void Visit(AST::ExprConstInt& p_node) override {
        std::cout << indentTabs() << "<ExprConstInt>" << p_node.get_value() << "</ExprConstInt>" << std::endl;
    }

    virtual void Visit(AST::ExprConstFloat& p_node) override {
        std::cout << indentTabs() << "<ExprConstFloat>" << p_node.get_value() << "</ExprConstFloat>" << std::endl;
    }

    virtual void Visit(AST::ExprVar& p_node) override {
        std::cout << indentTabs() <<  "<ExprVar>" << p_node.get_pVar()->get() << "</ExprVar>" << std::endl;
    }

    virtual void Visit(AST::ExprBinOpAdd& p_node) override {
        std::cout << indentTabs() << "<ExprBinOpAdd>" << std::endl;
        m_indent++;
        p_node.get_pArg1()->Accept(*this);
        p_node.get_pArg2()->Accept(*this);
        m_indent--;
        std::cout << indentTabs() << "</ExprBinOpAdd>" << std::endl;
    }

    virtual void Visit(AST::ExprBinOpSub& p_node) override {
        std::cout << indentTabs() << "<ExprBinOpSub>" << std::endl;
        m_indent++;
        p_node.get_pArg1()->Accept(*this);
        p_node.get_pArg2()->Accept(*this);
        m_indent--;
        std::cout << indentTabs() << "</ExprBinOpSub>" << std::endl;
    }

    virtual void Visit(AST::ExprBinOpMul& p_node) override {
        std::cout << indentTabs() << "<ExprBinOpMul>" << std::endl;
        m_indent++;
        p_node.get_pArg1()->Accept(*this);
        p_node.get_pArg2()->Accept(*this);
        m_indent--;
        std::cout << indentTabs() << "</ExprBinOpMul>" << std::endl;
    }

    virtual void Visit(AST::ExprBinOpDiv& p_node) override {
        std::cout << indentTabs() << "<ExprBinOpDiv>" << std::endl;
        m_indent++;
        p_node.get_pArg1()->Accept(*this);
        p_node.get_pArg2()->Accept(*this);
        m_indent--;
        std::cout << indentTabs() << "</ExprBinOpDiv>" << std::endl;
    }

    virtual void Visit(AST::ExprUnOpNeg& p_node) override {
        std::cout << indentTabs() << "<ExprUnOpNeg>" << std::endl;
        m_indent++;
        p_node.get_pArg1()->Accept(*this);
        m_indent--;
        std::cout << indentTabs() << "</ExprUnOpNeg>" << std::endl;
    }

    // Statements
    virtual void Visit(AST::AssignmentStatement& p_node) override {
        std::cout << indentTabs() << "<AssignmentStatement>" << std::endl;
        m_indent++;
        std::cout << p_node.get_name() << std::endl;
        p_node.getRHS()->Accept(*this);
        m_indent--;
        std::cout << indentTabs() << "</AssignmentStatement>" << std::endl;
    }
};
#endif //COMPILER_PRINTINFOVISITOR_H
