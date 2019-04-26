#include <utility>

#include <utility>

//
// Created by bennet.vella on 27/03/2019.
//

#ifndef COMPILER_FUNCTION_H
#define COMPILER_FUNCTION_H


#include "../ASTNode.h"
#include "Statement.h"
#include "Block.h"
#include <string>
namespace AST {
    class Function : public Statement {
    private:
        std::string _name;
        Statement* _params;
        std::string _type;
        Statement* _block;
    public:
        Function(std::string _name, Statement *_params, std::string _type, Statement *_block) :
            _name(std::move(_name)), _params(_params), _type(std::move(_type)), _block(_block) {}

        ~Function() override = default;
        void Accept(Visitor& v) override { v.Visit(*this); };

        const std::string &getName() const { return _name; }
        Statement *getParams() const { return _params; }
        const std::string &getType() const { return _type; }
        Statement *getBlock() const { return _block; }
    };
}

#endif //COMPILER_FUNCTION_H
