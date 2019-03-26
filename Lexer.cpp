//
// Created by bennet.vella on 08/03/2019.
//
#include <fstream>
#include <stack>
#include "Lexer.h"
#include "Util.h"

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

void Lexer::NextWord() {
    m_currentState = ST_BAD;
    m_lexeme = "";
    m_stack.empty();
    m_stack.push(ST_BAD);
}

void Lexer::NextChar(char * p_lastChar) {
    m_charIndex++;
    *p_lastChar = m_inputProgram[m_charIndex];
}

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
    NextWord();

    while (m_currentState != ST_ER) {
        NextChar(&lastChar);
        m_lexeme += lastChar;

        if (Util::setContains(m_acceptedStates, m_currentState)) m_stack.empty();

        m_stack.push(m_currentState);



        int currentChar;
        if (lastChar == '_') currentChar = CHAR_USCORE;
        else if (isalpha(lastChar)) currentChar = CHAR_LETTER;
        else if (isdigit(lastChar)) currentChar = CHAR_DIGIT;

        m_currentState = m_transitionTable[m_currentState][currentChar];

        std::cout << "Printing currentChar: " << CHAR_TYPE (currentChar);
        std::cout << "Printing m_currentState: " << STATE_TYPE (m_currentState);

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

Lexer::CLASSIFIER Lexer::classifyChar(char val) {
    if (val == '_') return CAT_UNDERSCORE;
    else if ((val <= 'z' && val >= 'a') && (val <= 'Z' || val >= 'A')) return CAT_LETTER;
    else if (val >= '0' && val <= '9') return CAT_DIGIT;
    else if (val == '*' || val == '/' || val == 'and') return CAT_MULTIPLICATIVE;
    else if (val == '+' || val == '-' || val == 'or') return CAT_ADDITIVE;
    else if (val == '<' || val == '>' || val == )
    return CAT_ADDITIVE;
}
