//
// Created by bennet.vella on 25/04/2019.
//

#ifndef COMPILER_IDENTIFIER_H
#define COMPILER_IDENTIFIER_H

#include "../Expr.h"
//ToDo implement this to store string data or just carry direct value storage
namespace AST {
    class Identifier {
    private:
        std::string _name;
    public :
        Identifier (std::string p_name) : _name(p_name) { }
        ~Identifier ( ) = default;

        const std::string &get_name() const { return _name; }
    };
}
#endif //COMPILER_IDENTIFIER_H
