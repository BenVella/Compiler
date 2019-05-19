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
    m_lineNumber = 1;

    //Read file
    std::cout << "[Lexer] Loading program from " << p_fileName << std::endl;
    std::ifstream programFile;
    programFile.open(p_fileName.c_str());
    m_inputProgram = "";

    if (programFile.is_open()) {
        std::cout << "[Lexer] Reading program text ... ";
        std::string line;
        while (std::getline(programFile, line)) {
            m_inputProgram.append(line + '\n');
        }
        std::cout << "Program Read.  Source Code: " << std::endl << m_inputProgram << std::endl;
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
    // ToDo : Uncommemnt the below value for debugging purposes only
    //std::cout << "Char Index: " << m_charIndex << "/" << m_inputProgram.length() << "(total)" << std::endl;

    if ((unsigned int) m_charIndex >= m_inputProgram.length() - 1) return Lexer::Token(TOK_EOF);

    NextWord();
    char lastChar = m_inputProgram[m_charIndex];

    // Consume all whitespaces newlines and tabs, update index and line number
    while (lastChar == ' ' || lastChar == '\n' || lastChar == '\t') {
        if (lastChar == '\n') m_lineNumber++;
        lastChar = m_inputProgram[++m_charIndex];
    }

    // Initialize Process
    NextWord();

    while (m_currentState != ST_ER) {
        NextChar(&lastChar);
        m_lexeme += lastChar;

        if (Util::setContains(m_acceptedStates, m_currentState)) m_stack.empty();
        m_stack.push(m_currentState);

        int charCat = categorizeChar(lastChar);


        m_currentState = m_transitionTable[charCat][m_currentState];

        //ToDo : Uncomment the below value, for debugging purposes
        /*std::cout << "Character: " << lastChar << " ; Categ: " << Lexer::ToString(CATEGORY (charCat))
            << " ; State: " << Lexer::ToString(STATE_TYPE (m_currentState)) << std::endl;*/
    }

    // We hit an ST_ER, rollback to last accepted state
    while (!Util::setContains(m_acceptedStates, m_currentState) && m_currentState != ST_START) {
        m_currentState = m_stack.top();
        m_stack.pop();
        m_lexeme.pop_back();
        m_charIndex--;
    }

    if (Util::setContains(m_acceptedStates, m_currentState)) {
        return StateToToken(STATE_TYPE (m_currentState));
    }

    return Lexer::Token(TOK_SYNTAX_ERR);
}

Lexer::CATEGORY Lexer::categorizeChar(char val) {
    if (val == ' ' || val == '\t' || val == '\r') return CAT_SPACE;
    else if (val == '\n') return CAT_NEWLINE;
    else if (std::isalpha(val) || val == '_') return CAT_TEXT;
    else if (std::isdigit(val)) return CAT_DIGIT;
    else if (val == ';' || val == ':' || val == ',' || val == '\'' || val == '(' || val == ')' || val == '{' || val == '}') return CAT_PUNC;
    else if (val == '.') return CAT_PERIOD;
    else if ( val == '/' ) return CAT_SLASH;
    else if (val == '*' || val == '+' || val == '-' || val == '<' || val == '>' || val == '=') return CAT_OP;
    else { std::cout << "Missing category for value: '" << std::endl << val << std::endl; return CAT_ERROR; }
}

Lexer::Token Lexer::StateToToken(STATE_TYPE st) {
    switch (st) {
        case ST_TEXT:
            if (Util::setContains(m_keywords,m_lexeme)) {
                if (m_lexeme == "float") return Lexer::Token(TOK_KEY_FLOAT);
                else if (m_lexeme == "int") return Lexer::Token(TOK_KEY_INT);
                else if (m_lexeme == "bool") return Lexer::Token(TOK_KEY_BOOL);
                else if (m_lexeme == "var") return Lexer::Token(TOK_KEY_VAR);
                else if (m_lexeme == "print") return Lexer::Token(TOK_KEY_PRINT);
                else if (m_lexeme == "return") return Lexer::Token(TOK_KEY_RETURN);
                else if (m_lexeme == "if") return Lexer::Token(TOK_KEY_IF);
                else if (m_lexeme == "else") return Lexer::Token(TOK_KEY_ELSE);
                else if (m_lexeme == "for") return Lexer::Token(TOK_KEY_FOR);
                else if (m_lexeme == "fn") return Lexer::Token(TOK_KEY_FN);
                else if (m_lexeme == "true") return Lexer::Token(TOK_KEY_TRUE);
                else if (m_lexeme == "false") return Lexer::Token(TOK_KEY_FALSE);
                else if (m_lexeme == "not") return Lexer::Token(TOK_KEY_NOT);
            } else
                return Lexer::Token(TOK_ID,m_lexeme);
        case ST_ID:                             return Lexer::Token(TOK_ID,m_lexeme);
        case ST_DIGIT:                          return Lexer::Token(TOK_INT_NUMBER,std::stof(m_lexeme, nullptr));
        case ST_FLOAT_END:                      return Lexer::Token(TOK_FLOAT_NUMBER,std::stof(m_lexeme, nullptr));
        case ST_SLASH:
        case ST_OPERATOR:
            if (m_lexeme == "=") return Lexer::Token(TOK_ASSIGNOP);
            else if (m_lexeme == "*") return Lexer::Token(TOK_ARITHMETIC_MULT);
            else if (m_lexeme == "/") return Lexer::Token(TOK_ARITHMETIC_DIV);
            else if (m_lexeme == "+") return Lexer::Token(TOK_ARITHMETIC_PLUS);
            else if (m_lexeme == "-") return Lexer::Token(TOK_ARITHMETIC_MINUS);
            else if (m_lexeme == ">") return Lexer::Token(TOK_ARITHMETIC_GREATER);
            else if (m_lexeme == "<") return Lexer::Token(TOK_ARITHMETIC_SMALLER);
            else return Lexer::Token(TOK_SYNTAX_ERR,m_lexeme);
        case ST_PUNCTUATION:
            if (m_lexeme == ";") return Lexer::Token(TOK_STMT_DELIMITER);
            else if (m_lexeme == "{") return Lexer::Token(TOK_OPEN_SCOPE);
            else if (m_lexeme == "}") return Lexer::Token(TOK_CLOSE_SCOPE);
            else return Lexer::Token(TOK_PUNC,m_lexeme);
        case ST_LINE_COMMENT:                   return GetNextToken(); // Retry
        case ST_BLOCK_END:                      return GetNextToken(); // Retry
    }
    return Lexer::Token();
}

int Lexer::getLine() const {
    return m_lineNumber;
}

