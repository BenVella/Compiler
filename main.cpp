#include <iostream>
#include "Lexer.h"

int main() {
    std::cout << "Hello, World!" << std::endl;

    std::string fileName = R"(C:\Users\bennet.vella\Desktop\Compilers\SampleCode.txt)";
    Lexer* newLexer = new Lexer (fileName);

    auto valTest = newLexer->GetNextToken();
    while ( valTest.token_type != Lexer::TOK_TYPE::TOK_EOF) {
        std::cout << valTest.ToString() << std::endl;
        valTest = newLexer->GetNextToken();
    }

    return 0;
}