//
// Created by bennet.vella on 08/03/2019.
//
#include <fstream>
#include <stack>
#include "Lexer.h"
#include "Util.h"

Lexer::Lexer (std::string p_fileName) {
    // Initialize Vars
    m_charIndex = 0;
    m_lineNumber = 0;

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
    m_currentState = ST_START;
    m_lexeme = "";
    m_stack.empty();
    m_stack.push(ST_START);
}

void Lexer::NextChar(char * p_lastChar) {
    *p_lastChar = m_inputProgram[m_charIndex++];
}

Lexer::Token Lexer::GetNextToken() {
    std::cout << m_charIndex << ".." << m_inputProgram.length() << std::endl;

    if ((unsigned int) m_charIndex == m_inputProgram.length() - 1) return Lexer::Token(TOK_EOF);

    NextWord();
    char lastChar = m_inputProgram[m_charIndex];

    // Consume all whitespaces and newlines, update index and line number
    while (lastChar == ' ' || lastChar == '\n') {
        if (lastChar == '\n') m_lineNumber++;
        lastChar = m_inputProgram[m_charIndex++];
    }

    // Initialize Process
    NextWord();

    while (m_currentState != ST_ER) {
        NextChar(&lastChar);
        m_lexeme += lastChar;

        if (Util::setContains(m_acceptedStates, m_currentState)) m_stack.empty();
        m_stack.push(m_currentState);

        int charCat = categorizeChar(lastChar);


        m_currentState = m_transitionTable[m_currentState][charCat];

        std::cout << "Printing charCategory: " << CATEGORY (charCat) << std::endl;
        std::cout << "Printing m_currentState: " << STATE_TYPE (m_currentState) << std::endl;

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

Lexer::CATEGORY Lexer::categorizeChar(char val) {
    if (val == ' ') return CAT_CUT;
    else if (std::isalpha(val) || val == '_') return CAT_TEXT;
    else if (std::isdigit(val)) return CAT_DIGIT;
    else if ( val == '/' ) return CAT_SLASH;
    else if (val == '*' || val == '+' || val == '-' || val == '<' || val == '>') return CAT_OP;
    else if (val == ';' || val == '(' || val == ')' || val == '{' || val == '}') return CAT_PUNC;
    return CAT_UNDEFINED;
}
