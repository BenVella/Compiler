//
// Created by bennet.vella on 08/03/2019.
//

#ifndef COMPILER_LEXER_H
#define COMPILER_LEXER_H


class Lexer {
public :
    Lexer(std::string p_fileName);

    virtual ~Lexer();

    enum TOK_TYPE {
        TOK_EOF = 1 , TOK_DEF = 2 , TOK_RETURN = 3 , TOK_EXTERN = 4 ,
        TOK_ID = 5 , TOK_NUMBER = 6 , TOK_NUM_ERROR = 7 , TOK_IF = 8 ,
        TOK_PUNC = 9 , TOK_SRCLANG_TYPE = 10 , TOK_SYNTAX_ERR = 11 ,
        TOK_BOOLOP = 12 , TOK_ASSIGNOP = 13 , TOK_ARITHMETICOP = 14 ,
        TOK_STMT_DELIMITER = 15 , TOK_OPEN_SCOPE = 16 , TOK_CLOSE_SCOPE = 17
    };

    struct Token {
        TOK_TYPE token_type;
        std::string id_name;
        float number_value;

        Token()
        {
            token_type = TOK_EOF;
            id_name = "";
            number_value = 0;
        }

        Token(TOK_TYPE p_token_type, std:string p_id_name, float p_number_value)
        {
            token_type = p_token_type;
            id_name = p_id_name;
            number_value = p_number_value;
        }

        Token(TOK_TYPE p_token_type)
        {
            token_type = p_token_type;
            id_name = "";
            number_value = 0;
        }

        Token(TOK_TYPE p_token_type, std:string p_id_name)
        {
            token_type = p_token_type;
            id_name = p_id_name;
            number_value = 0;
        }

        Token(TOK_TYPE p_token_type, float p_number_value) {
            token_type = p_token_type;
            id_name = "";
            number_value = 0;
        }

        std:string ToString() {
            switch (token_type) {
                case TOK_EOF :
                    return "[TOK_EOF]";
                case TOK_DEF :
                    return "[TOK_DEF]";
                case TOK_RETURN :
                    return "[TOK_RETURN]";
                case TOK_EXTERN :
                    return "[TOK_EXTERN]";
                case TOK_ID :
                    return "[TOK_ID]";
                case TOK_NUMBER :
                    return "[TOK_NUMBER]";
                case TOK_NUM_ERROR :
                    return "[TOK_NUM_ERROR]";
                case TOK_IF :
                    return "[TOK_IF]";
                case TOK_PUNC :
                    return "[TOK_PUNC]";
                case TOK_SRCLANG_TYPE :
                    return "[TOK_SRCLANG_TYPE]";
                case TOK_SYNTAX_ERR :
                    return "[TOK_SYNTAX_ERR]";
                case TOK_BOOLOP :
                    return "[TOK_BOOLOP]";
                case TOK_ASSIGNOP :
                    return "[TOK_ASSIGNOP]";
                case TOK_ARITHMETICOP :
                    return "[TOK_ARITHMETICOP]";
                case TOK_STMT_DELIMITER :
                    return "[TOK_STMT_DELIMITER]";
                case TOK_OPEN_SCOPE :
                    return "[TOK_OPEN_SCOPE]";
                case TOK_CLOSE_SCOPE :
                    return "[TOK_CLOSE_SCOPE]";
            }
        }


        Token getToken();

        std:string ToString();

    private:
        std::string m_inputProgram;
        int m_charIndex;
        int m_lineNumber;
    };
}

#endif //COMPILER_LEXER_H