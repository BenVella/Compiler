#include <utility>

#include <utility>

//
// Created by bennet.vella on 08/03/2019.
//

#ifndef COMPILER_LEXER_H
#define COMPILER_LEXER_H

#include <string>
#include <iostream>
#include <set>
#include <stack>

class Lexer {
public :
    explicit Lexer(std::string p_fileName);

    Lexer();

    virtual ~Lexer();

    enum TOK_TYPE {
        TOK_EOF, TOK_DEF, TOK_EXTERN, TOK_ID,
        TOK_INT_NUMBER, TOK_FLOAT_NUMBER, TOK_NUM_ERROR, TOK_PUNC, TOK_SRCLANG_TYPE,
        TOK_SYNTAX_ERR, TOK_BOOLOP, TOK_ASSIGNOP, TOK_ARITHMETIC_PLUS,
        TOK_ARITHMETIC_MINUS, TOK_ARITHMETIC_DIV, TOK_ARITHMETIC_MULT,
        TOK_STMT_DELIMITER, TOK_OPEN_SCOPE, TOK_CLOSE_SCOPE,
        TOK_COMMENT, TOK_KEY_FLOAT, TOK_KEY_INT, TOK_KEY_BOOL,
        TOK_KEY_VAR, TOK_KEY_PRINT, TOK_KEY_RETURN, TOK_KEY_IF, TOK_KEY_ELSE,
        TOK_KEY_FOR, TOK_KEY_FN, TOK_KEY_TRUE, TOK_KEY_FALSE, TOK_KEY_NOT
    };

    struct Token {
        TOK_TYPE token_type;
        std::string id_name;
        float number_value;

        Token() {
            token_type = TOK_EOF;
            id_name = "";
            number_value = 0;
        }

        Token(TOK_TYPE p_token_type, std::string p_id_name, float p_number_value) {
            token_type = p_token_type;
            id_name = std::move(p_id_name);
            number_value = p_number_value;
        }

        explicit Token(TOK_TYPE p_token_type) {
            token_type = p_token_type;
            id_name = "";
            number_value = 0;
        }

        Token(TOK_TYPE p_token_type, std::string p_id_name) {
            token_type = p_token_type;
            id_name = std::move(p_id_name);
            number_value = 0;
        }

        Token(TOK_TYPE p_token_type, float p_number_value) {
            token_type = p_token_type;
            id_name = "";
            number_value = p_number_value;
        }

        std::string ToString() {
            switch (token_type) {
                case TOK_EOF :                      return "[TOK_EOF]";
                case TOK_DEF :                      return "[TOK_DEF]";
                case TOK_EXTERN :                   return "[TOK_EXTERN]";
                case TOK_ID :                       return "[TOK_ID]";
                case TOK_INT_NUMBER :               return "[TOK_INT_NUMBER]";
                case TOK_FLOAT_NUMBER :             return "[TOK_FLOAT_NUMBER]";
                case TOK_NUM_ERROR :                return "[TOK_NUM_ERROR]";
                case TOK_PUNC :                     return "[TOK_PUNC]";
                case TOK_SRCLANG_TYPE :             return "[TOK_SRCLANG_TYPE]";
                case TOK_SYNTAX_ERR :               return "[TOK_SYNTAX_ERR]";
                case TOK_BOOLOP :                   return "[TOK_BOOLOP]";
                case TOK_ASSIGNOP :                 return "[TOK_ASSIGNOP]";
                case TOK_ARITHMETIC_PLUS :          return "[TOK_ARITHMETIC_PLUS]";
                case TOK_ARITHMETIC_MINUS :         return "[TOK_ARITHMETIC_MINUS]";
                case TOK_ARITHMETIC_MULT :          return "[TOK_ARITHMETIC_MULT]";
                case TOK_ARITHMETIC_DIV :           return "[TOK_ARITHMETIC_DIV]";
                case TOK_STMT_DELIMITER :           return "[TOK_STMT_DELIMITER]";
                case TOK_OPEN_SCOPE :               return "[TOK_OPEN_SCOPE]";
                case TOK_CLOSE_SCOPE :              return "[TOK_CLOSE_SCOPE]";
                case TOK_COMMENT :                  return "[TOK_COMMENT]";
                case TOK_KEY_FLOAT :                return "[TOK_KEY_FLOAT]";
                case TOK_KEY_INT :                  return "[TOK_KEY_INT]";
                case TOK_KEY_BOOL :                 return "[TOK_KEY_BOOL]";
                case TOK_KEY_VAR :                  return "[TOK_KEY_VAR]";
                case TOK_KEY_PRINT :                return "[TOK_KEY_PRINT]";
                case TOK_KEY_RETURN :               return "[TOK_KEY_RETURN]";
                case TOK_KEY_IF :                   return "[TOK_KEY_IF]";
                case TOK_KEY_ELSE :                 return "[TOK_KEY_ELSE]";
                case TOK_KEY_FOR :                  return "[TOK_KEY_FOR]";
                case TOK_KEY_FN :                   return "[TOK_KEY_FN]";
                case TOK_KEY_TRUE :                 return "[TOK_KEY_TRUE]";
                case TOK_KEY_FALSE :                return "[TOK_KEY_FALSE]";
                case TOK_KEY_NOT :                  return "[TOK_KEY_NOT]";
                default:                            return nullptr;
            }
        };
    };
    Token GetNextToken();
    void NextWord();
    void NextChar(char * p_lastChar);

private:
    std::string m_inputProgram;
    int m_charIndex;
    int m_lineNumber;

    int m_currentState;
    std::string m_lexeme;
    std::stack<int> m_stack;

    std::set<std::string> m_keywords = {
            "float", "int", "bool", "var",
            "print","return", "if", "else",
            "for", "fn", "true", "false", "not"};

    enum STATE_TYPE {
        ST_START, ST_ER, ST_TEXT,
        ST_ID, ST_DIGIT, ST_OPERATOR,
        ST_PUNCTUATION, ST_SLASH,
        ST_BACKSLASH, ST_LINE_COMMENT,
        ST_BLOCK_COMMENT, ST_BLOCK_TRY_END,
        ST_BLOCK_END, ST_FLOAT_START, ST_FLOAT_END
    };

    inline const char* ToString(STATE_TYPE v)
    {
        switch (v)
        {
            case ST_START:                  return "ST_START";
            case ST_ER:                     return "ST_ER";
            case ST_TEXT:                   return "ST_TEXT";
            case ST_ID:                     return "ST_ID";
            case ST_DIGIT:                  return "ST_DIGIT";
            case ST_OPERATOR:               return "ST_OPERATOR";
            case ST_PUNCTUATION:            return "ST_PUNCTUATION";
            case ST_SLASH:                  return "ST_SLASH";
            case ST_BACKSLASH:              return "ST_BACKSLASH";
            case ST_LINE_COMMENT:           return "ST_LINE_COMMENT";
            case ST_BLOCK_COMMENT:          return "ST_BLOCK_COMMENT";
            case ST_BLOCK_TRY_END:          return "ST_BLOCK_TRY_END";
            case ST_BLOCK_END:              return "ST_BLOCK_END";
            case ST_FLOAT_START:            return "ST_FLOAT_START";
            case ST_FLOAT_END:              return "ST_FLOAT_END";
            default:                        return "[Unknown STATE_TYPE]";
        }
    }
    enum CATEGORY {
        CAT_ERROR, CAT_SPACE, CAT_NEWLINE,
        CAT_TEXT, CAT_DIGIT, CAT_OP, CAT_PUNC,
        CAT_PERIOD, CAT_STAR, CAT_SLASH, CAT_BACKSLASH
    };

    inline const char* ToString(CATEGORY v)
    {
        switch (v)
        {
            case CAT_ERROR:                 return "CAT_ERROR";
            case CAT_SPACE:                 return "CAT_SPACE";
            case CAT_NEWLINE:               return "CAT_NEWLINE";
            case CAT_TEXT:                  return "CAT_TEXT";
            case CAT_DIGIT:                 return "CAT_DIGIT";
            case CAT_OP:                    return "CAT_OP";
            case CAT_PUNC:                  return "CAT_PUNC";
            case CAT_PERIOD:                return "CAT_PERIOD";
            case CAT_STAR:                  return "CAT_STAR";
            case CAT_SLASH:                 return "CAT_SLASH";
            case CAT_BACKSLASH:             return "CAT_BACKSLASH";
            default:                        return "[Unknown CATEGORY]";
        }
    }

    std::set<int> m_acceptedStates = {ST_TEXT, ST_ID, ST_DIGIT, ST_OPERATOR, ST_PUNCTUATION,ST_SLASH,
                                      ST_BACKSLASH, ST_LINE_COMMENT, ST_BLOCK_END, ST_FLOAT_END};

    int m_transitionTable[11][15] = {
            {ST_ER,ST_ER,ST_ER,ST_ER,ST_ER,ST_ER,ST_ER,ST_ER,ST_ER,ST_ER,ST_ER,ST_ER,ST_ER,ST_ER,ST_ER},
            {ST_ER,ST_ER,ST_ER,ST_ER,ST_ER,ST_ER,ST_ER,ST_ER,ST_ER,ST_LINE_COMMENT,ST_BLOCK_COMMENT,ST_BLOCK_COMMENT,ST_ER,ST_ER,ST_ER},
            {ST_ER,ST_ER,ST_ER,ST_ER,ST_ER,ST_ER,ST_ER,ST_ER,ST_ER,ST_ER,ST_BLOCK_COMMENT,ST_BLOCK_COMMENT,ST_ER,ST_ER,ST_ER},
            {ST_TEXT,ST_ER,ST_TEXT,ST_ID,ST_ER,ST_ER,ST_ER,ST_ER,ST_ER,ST_LINE_COMMENT,ST_BLOCK_COMMENT,ST_BLOCK_COMMENT,ST_ER,ST_ER,ST_ER},
            {ST_DIGIT,ST_ER,ST_ID,ST_ID,ST_DIGIT,ST_ER,ST_ER,ST_ER,ST_ER,ST_LINE_COMMENT,ST_BLOCK_COMMENT,ST_BLOCK_COMMENT,ST_ER,ST_FLOAT_END,ST_FLOAT_END},
            {ST_OPERATOR,ST_ER,ST_ER,ST_ER,ST_ER,ST_ER,ST_ER,ST_ER,ST_ER,ST_LINE_COMMENT,ST_BLOCK_COMMENT,ST_BLOCK_COMMENT,ST_ER,ST_ER,ST_ER},
            {ST_PUNCTUATION,ST_ER,ST_ER,ST_ER,ST_ER,ST_ER,ST_ER,ST_ER,ST_ER,ST_LINE_COMMENT,ST_BLOCK_COMMENT,ST_BLOCK_COMMENT,ST_ER,ST_ER,ST_ER},
            {ST_PUNCTUATION,ST_ER,ST_ER,ST_ER,ST_FLOAT_START,ST_ER,ST_ER,ST_ER,ST_ER,ST_LINE_COMMENT,ST_BLOCK_COMMENT,ST_BLOCK_COMMENT,ST_ER,ST_ER,ST_ER},    //TODO - Complete actual
            {ST_OPERATOR,ST_ER,ST_ER,ST_ER,ST_ER,ST_ER,ST_ER,ST_ER,ST_BLOCK_COMMENT,ST_LINE_COMMENT,ST_BLOCK_TRY_END,ST_BLOCK_COMMENT,ST_ER,ST_ER,ST_ER},
            {ST_SLASH,ST_ER,ST_ER,ST_ER,ST_ER,ST_ER,ST_ER,ST_LINE_COMMENT,ST_ER,ST_LINE_COMMENT,ST_BLOCK_COMMENT,ST_BLOCK_END,ST_ER,ST_ER,ST_ER},
            {ST_BACKSLASH,ST_ER,ST_ER,ST_ER,ST_ER,ST_ER,ST_ER,ST_ER,ST_ER,ST_LINE_COMMENT,ST_BLOCK_COMMENT,ST_BLOCK_COMMENT,ST_ER,ST_ER,ST_ER}};

    CATEGORY categorizeChar(char val);
    Lexer::Token StateToToken (STATE_TYPE st);
};

#endif //COMPILER_LEXER_H