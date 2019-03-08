//
// Created by bennet.vella on 08/03/2019.
//

Lexer::Lexer(std::string p_fileName) {
    //Read file
    std::cout << "[Lexer] Loading program form " << p_fileName << std::endl;
    std::ifstream programFile;
    programFile.open(p_fileName.c_str());
    m_inputProgram = "";

    if (programFile.isOpen()) {
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

Lexer::Token Lexer::GetToken() {
    std::cout << m_charIndex << ".." << m_inputProgram.length() << std::endl;
    if ((unsigned int) m_charIndex == m_inputProgram.length() - 1) return Lexer::Token(TOK_EOF)

    char lastChar = m_inputProgram[m_charIndex];

    while (lastChar == ' ' || lastChar == '\n') {
        if (lastChar == '\n') m_lineNumber++;
        m_charIndex++;
        lastChar = m_inputProgram[m_charIndex];
    }

    // Are these comments?
    if (lastChar == '/') {
        //m_charIndex
    }
}