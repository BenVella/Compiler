#include <iostream>
#include <fstream>
#include <io.h>
#include "Lexer.h"
#include "Parser.h"
#include "Visitor/PrintXMLVisitor.h"
#include "Visitor/SemanticAnalysisVisitor.h"
#include "Visitor/InterpreterVisitor.h"

typedef std::map<std::string, AST::Var> VarTable;

void AppendLexerDetails(Lexer::Token *pToken);
void PrintTokenDetails();
void OffloadLexerDetails();

std::string m_lexOutput;

int main() {
    m_lexOutput = "";

    std::string fileName = R"(SampleCode.txt)";
    Lexer* newLexer = new Lexer (fileName);
    VarTable varTable;

    // Standard Parser Evaluation
    AST::Program* progResult = Parser::Parse(newLexer, varTable);

    // Uncomment for Printing XML
    // VISITOR - PrintXMLVisitor
    PrintXMLVisitor xmlVisitor;
    for (auto* stmt : *progResult->main_impl) {
        stmt->Accept(xmlVisitor);
    }

    // Uncomment for Semantic Analysis
    // VISITOR - SemanticAnalysisVisitor
    std::cout << "Semantic Analysis Start" << std::endl;
    auto *semanticVisitor = new SemanticAnalysisVisitor();
    for (auto* stmt : *progResult->main_impl) {
        if (!semanticVisitor->hasErrored)
            stmt->Accept(*semanticVisitor);
    }
    if (semanticVisitor->hasErrored) {
        std::cerr << "SEMANTIC ANALYSIS FAILED!" << std::endl;
        std::cout << "SEMANTIC ANALYSIS FAILED!" << std::endl;
    } else {
        std::cout << "Semantic Analysis Successful" << std::endl;
        std::cout << "============================" << std::endl << std::endl;
        std::cout << "Beginning Interpretation" << std::endl;
        std::cout << "------------------------" << std::endl;

        // Uncomment for Interpretation
        // Carry out Interpretation since Analysis was successful
        auto *interpreterVisitor = new InterpreterVisitor();

        for (auto *stmt : *progResult->main_impl) {
            if (!interpreterVisitor->hasErrored)
                stmt->Accept(*interpreterVisitor);
        }
        if (interpreterVisitor->hasErrored) {
            std::cerr << "INTERPRETATION FAILED!" << std::endl;
            std::cout << "INTERPRETATION FAILED!" << std::endl;
        } else {
            std::cout << "Interpretation Complete" << std::endl;
            std::cout << "=======================" << std::endl;
        }
    }
    return 0;
}

void AppendLexerDetails(Lexer::Token *pToken) {
    m_lexOutput.append(pToken->ToString());
    m_lexOutput.append(" ");
    m_lexOutput.append(pToken->token_type==Lexer::TOK_INT_NUMBER ? std::to_string(pToken->number_value) : pToken->id_name);
    m_lexOutput.append("\n");
}

void PrintTokenDetails() {
    std::cout << m_lexOutput;
}

void OffloadLexerDetails () {
    std::ofstream file (R"(C:\Users\bennet.vella\Desktop\Compilers\LogOutput.txt)");
    file << m_lexOutput;
}