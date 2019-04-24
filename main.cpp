#include <iostream>
#include <fstream>
#include "Lexer.h"
#include "Parser.h"
#include "Visitor/PrintInfoVisitor.h"

void AppendLexerDetails(Lexer::Token *pToken);
void PrintTokenDetails();
void OffloadLexerDetails();

std::string m_lexOutput;

int main() {
    m_lexOutput = "";

    std::string fileName = R"(C:\Users\bennet.vella\Desktop\Compilers\SampleCode.txt)";
    Lexer* newLexer = new Lexer (fileName);

    //std::cout << "Starting Main Program" << std::endl;

    // Standard Parser Evaluation TODO Uncomment if you want Parser operation
    AST::Program* progResult = Parser::Parse(newLexer);

    //std::cout << "Finished Main Program" << std::endl;
    PrintInfoVisitor visitor;

    for (auto* expr : *progResult->tempExprs) {
        expr->Accept(visitor);
    }


    // Direct Lexer Evaluation  TODO Uncomment if you want direct Lexer operation
/*    auto valTest = newLexer->GetNextToken();
    while (valTest.token_type != Lexer::TOK_EOF && valTest.token_type != Lexer::TOK_SYNTAX_ERR) {
        AppendLexerDetails(&valTest);
        valTest = newLexer->GetNextToken();
    }

    PrintTokenDetails();
    OffloadLexerDetails();*/
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