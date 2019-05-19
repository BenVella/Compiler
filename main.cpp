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

    // Standard Parser Evaluation TODO Uncomment if you want Parser operation
    AST::Program* progResult = Parser::Parse(newLexer, varTable);

    // Uncomment for Printing XML
    // VISITOR - PrintXMLVisitor
    /*PrintXMLVisitor visitor;
    for (auto* stmt : *progResult->main_impl) {
        stmt->Accept(visitor);
    }*/


    // VISITOR - SemanticAnalysisVisitor
    std::cout << "Semantic Analysis Start" << std::endl;
    auto *visitor1 = new SemanticAnalysisVisitor();
    for (auto* stmt : *progResult->main_impl) {
        if (!visitor1->hasErrored)
            stmt->Accept(*visitor1);
    }
    if (visitor1->hasErrored)
        std::cerr << "SEMANTIC ANALYSIS FAILED!" << std::endl;
    else {
        std::cout << "Semantic Analysis Successful." << std::endl;

        // Carry out interpretation since Analysis was successful
        auto *visitor2 = new InterpreterVisitor();

        for (auto *stmt : *progResult->main_impl) {
            stmt->Accept(*visitor2);
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