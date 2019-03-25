//
// Created by bennet.vella on 08/03/2019.
//
#include <fstream>
#include <stack>
#include "Lexer.h"

Lexer::Lexer (std::string p_fileName) {
    //Read file
    std::cout << "[Lexer] Loading program form " << p_fileName << std::endl;
    std::ifstream programFile;
    programFile.open(p_fileName.c_str());
    m_inputProgram = "";

    if (programFile.is_open()) {
        std::cout << "[Lexer] Reading program text ... ";
        std::string line;
        while (std::getline(programFile, line)) {
            m_inputProgram.append(line + '\n');
        }
        std::cout << "done." << std::endl;
    }
    else {
        std::cout << "[Lexer] File does not exist!!" << std::endl;
    }
    programFile.close();
}

Lexer::~Lexer () = default;

Lexer::Token Lexer::GetNextToken() {
    std::cout << m_charIndex << ".." << m_inputProgram.length() << std::endl;

    if ((unsigned int) m_charIndex == m_inputProgram.length() - 1) return Lexer::Token(TOK_EOF);

    char lastChar = m_inputProgram[m_charIndex];

    // Consume all whitespaces and newlines, update index and line number
    while (lastChar == ' ' || lastChar == '\n') {
        if (lastChar == '\n') m_lineNumber++;
        m_charIndex++;
        lastChar = m_inputProgram[m_charIndex];
    }

    // Initialize Process
    int currentState = ST_BAD;
    std::string lexeme = "";
    std::stack<int> m_stack;
    m_stack.empty();
    m_stack.push(ST_BAD);

    while (currentState != ST_ER) {
        NextChar(&lastChar);
        lexeme += lastChar;
        if (currentState in m_acceptedStates)

        int currentChar;
        if (lastChar == '_') currentChar = CHAR_USCORE;
        else if (isalpha(lastChar)) currentChar = CHAR_LETTER;
        else if (isdigit(lastChar)) currentChar = CHAR_DIGIT;

        currentState = m_transitionTable[currentState][currentChar];

        std::cout << "Printing currentChar: " << CHAR_TYPE (currentChar);
        std::cout << "Printing currentState: " << STATE_TYPE (currentState);

        m_charIndex++;
        lastChar = m_inputProgram[m_charIndex];
    }

    // Are these comments?
    if (lastChar == '/') {
        m_charIndex++;
        lastChar = m_inputProgram[m_charIndex];
        if (lastChar == '/') {
            // Acquire comment and advance line number
            std::string commentLine = "";
            while (lastChar != '\n') {
                m_charIndex++;
                lastChar = m_inputProgram[m_charIndex];
                commentLine += lastChar;
            }
            if (lastChar == '\n') m_lineNumber++;
            m_charIndex++;
            return Lexer::Token(TOK_ID,"Comment: " + commentLine); // ToDo : Review the return type for a comment
        } else { // Not two consecutive slashes - could be division
            return Lexer::Token(TOK_ARITHMETICOP,"/");   // ToDo: Review the return type for different operands
        }
    }
    return Lexer::Token(TOK_NUM_ERROR);
}