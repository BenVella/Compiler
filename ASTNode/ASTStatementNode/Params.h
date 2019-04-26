//
// Created by bennet.vella on 26/04/2019.
//

#ifndef COMPILER_PARAMS_H
#define COMPILER_PARAMS_H

#include <vector>
#include "Statement.h"

namespace AST {
    class Params : public Statement {
    private:
        std::vector<Statement *> *_params;
    public:
        Params(std::vector<Statement *> *_params) : _params(_params) {}
        Params() {
            _params = new std::vector<Statement *>();
        }
        ~Params() override = default;

        void Accept(Visitor& v) override { v.Visit(*this); };

        std::vector<Statement *> *getParams() const { return _params; }

        void addParam(Statement *p_statement) {
            _params->push_back(p_statement);
        }
    };
}

#endif //COMPILER_PARAMS_H
