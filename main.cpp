#include <iostream>
#include "Lexer.h"

int main() {
    std::cout << "Hello, World!" << std::endl;

    std::string fileName = R"(C:\Users\bennet.vella\Desktop\Compilers\SampleCode.txt)";
    Lexer* newLexer = new Lexer (fileName);

    auto * newToken = new Lexer::Token(Lexer::TOK_TYPE::TOK_EOF);
    std::cout << newToken->ToString() << std::endl;
    return 0;
}