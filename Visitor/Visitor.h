//
// Created by bennet.vella on 25/03/2019.
//

#ifndef COMPILER_VISITOR_H
#define COMPILER_VISITOR_H

namespace AST {
    class ExprConstInt;
    class ExprConstFloat;
    class ExprVar;
    class ExprBinOpAdd;
    class ExprBinOpSub;
    class ExprBinOpMul;
    class ExprBinOpDiv;
    class ExprUnOpNeg;

    class Assignment;
    class VarDeclare;
    class Print;
}

class Visitor {
public:
    virtual void Visit (AST::ExprConstInt& e) = 0;
    virtual void Visit (AST::ExprConstFloat& e) = 0;
    virtual void Visit (AST::ExprVar& e) = 0;
    virtual void Visit (AST::ExprBinOpAdd& e) = 0;
    virtual void Visit (AST::ExprBinOpSub& e) = 0;
    virtual void Visit (AST::ExprBinOpMul& e) = 0;
    virtual void Visit (AST::ExprBinOpDiv& e) = 0;
    virtual void Visit (AST::ExprUnOpNeg& e) = 0;

    virtual void Visit (AST::Assignment& e) = 0;
    virtual void Visit (AST::VarDeclare& e) = 0;
    virtual void Visit (AST::Print& e) = 0;
};

#endif //COMPILER_VISITOR_H
