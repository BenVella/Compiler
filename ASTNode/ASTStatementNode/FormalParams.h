//
// Created by bennet.vella on 26/04/2019.
//

#ifndef COMPILER_FORMALPARAMS_H
#define COMPILER_FORMALPARAMS_H

#include <vector>
#include "Statement.h"

namespace AST {
    class FormalParams : public Statement {
    private:
        std::vector<Statement *> *_params;
    public:
        FormalParams(std::vector<Statement *> *_params) : _params(_params) {}
        FormalParams() {
            _params = new std::vector<Statement *>();
        }
        ~FormalParams() override = default;

        void Accept(Visitor& v) override { v.Visit(*this); };

        std::vector<Statement *> *getParams() const { return _params; }

        void addParam(Statement *p_statement) {
            _params->push_back(p_statement);
        }
    };
}

#endif //COMPILER_FORMALPARAMS_H
