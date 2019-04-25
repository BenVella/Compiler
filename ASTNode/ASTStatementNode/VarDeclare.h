//
// Created by bennet.vella on 10/04/2019.
//

#ifndef COMPILER_VARDECLARE_H
#define COMPILER_VARDECLARE_H

#include <string>
#include "Statement.h"

namespace AST {
    class VarDeclare : public Statement {
    private:
        std::string _name;
        std::string _type;
        AST::Expr *_expr;
    public:
        VarDeclare(std::string p_name, std::string p_type, AST::Expr *p_node) : _name(p_name), _type(p_type), _expr (p_node) {}
        ~VarDeclare() = default;

        void Accept(Visitor& v) override { v.Visit(*this); }

        const std::string &getName() const { return _name; }
        const std::string &getType() const { return _type; }
        Expr *getExpr() const { return _expr; }
    };
}

#endif //COMPILER_VARDECLARE_H
