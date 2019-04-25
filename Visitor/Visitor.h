//
// Created by bennet.vella on 25/03/2019.
//

#ifndef COMPILER_VISITOR_H
#define COMPILER_VISITOR_H

namespace AST {
    class ExprConst;
    class ExprVar;
    class ExprBinOpAdd;
    class ExprBinOpSub;
    class ExprBinOpMul;
    class ExprBinOpDiv;
    class ExprUnOp;
    class ExprUnOpNeg;
}

class Visitor {
public:
    virtual void Visit (AST::ExprConst& e) = 0;
    virtual void Visit (AST::ExprVar& e) = 0;
    virtual void Visit (AST::ExprBinOpAdd& e) = 0;
    virtual void Visit (AST::ExprBinOpSub& e) = 0;
    virtual void Visit (AST::ExprBinOpMul& e) = 0;
    virtual void Visit (AST::ExprBinOpDiv& e) = 0;
    virtual void Visit (AST::ExprUnOp& e) = 0;
    virtual void Visit (AST::ExprUnOpNeg& e) = 0;
};

#endif //COMPILER_VISITOR_H
