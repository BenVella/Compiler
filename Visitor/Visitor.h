//
// Created by bennet.vella on 25/03/2019.
//

#ifndef COMPILER_VISITOR_H
#define COMPILER_VISITOR_H

namespace AST {
    class Expr;
    class ExprBinOpAdd;
    class ExprBinOpSub;
}

class Visitor {
public:
    virtual void Visit (AST::Expr& e) = 0;
    virtual void Visit (AST::ExprBinOpAdd& e) = 0;
    virtual void Visit (AST::ExprBinOpSub& e) = 0;
};

#endif //COMPILER_VISITOR_H
