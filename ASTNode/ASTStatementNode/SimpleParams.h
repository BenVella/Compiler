//
// Created by bennet.vella on 26/04/2019.
//

#ifndef COMPILER_SIMPLEPARAMS_H
#define COMPILER_SIMPLEPARAMS_H

#include <vector>
#include "Statement.h"

namespace AST {
    class SimpleParams : public Statement {
    private:
        std::vector<Statement *> *_params;
    public:
        SimpleParams(std::vector<Statement *> *_params) : _params(_params) {}
        SimpleParams() {
            _params = new std::vector<Statement *>();
        }
        ~SimpleParams() override = default;

        void Accept(Visitor& v) override { v.Visit(*this); };

        std::vector<Statement *> *getParams() const { return _params; }

        void addParam(Statement *p_statement) {
            _params->push_back(p_statement);
        }
    };
}

#endif //COMPILER_SIMPLEPARAMS_H
