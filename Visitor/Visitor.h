//
// Created by bennet.vella on 25/03/2019.
//

#ifndef COMPILER_VISITOR_H
#define COMPILER_VISITOR_H

namespace AST {
    class ExprConstInt;
    class ExprConstFloat;
    class ExprVar;
    class ExprBoolOpTrue;
    class ExprBoolOpFalse;
    class ExprBinOpAdd;
    class ExprBinOpSub;
    class ExprBinOpMul;
    class ExprBinOpSmaller;
    class ExprBinOpGreater;
    class ExprBinOpDiv;
    class ExprUnOpNeg;

    class Assignment;
    class VarDeclare;
    class Print;
    class Return;
    class If;
    class Block;
    class For;
    class FunctionCall;
    class FunctionDeclare;
    class Param;
    class Params;
}

class Visitor {
public:
    virtual void Visit (AST::ExprConstInt& e) = 0;
    virtual void Visit (AST::ExprConstFloat& e) = 0;
    virtual void Visit (AST::ExprVar& e) = 0;
    virtual void Visit (AST::ExprBoolOpTrue& e) = 0;
    virtual void Visit (AST::ExprBoolOpFalse& e) = 0;
    virtual void Visit (AST::ExprBinOpAdd& e) = 0;
    virtual void Visit (AST::ExprBinOpSub& e) = 0;
    virtual void Visit (AST::ExprBinOpMul& e) = 0;
    virtual void Visit (AST::ExprBinOpDiv& e) = 0;
    virtual void Visit (AST::ExprBinOpSmaller& e) = 0;
    virtual void Visit (AST::ExprBinOpGreater& e) = 0;
    virtual void Visit (AST::ExprUnOpNeg& e) = 0;

    virtual void Visit (AST::Assignment& e) = 0;
    virtual void Visit (AST::VarDeclare& e) = 0;
    virtual void Visit (AST::Print& e) = 0;
    virtual void Visit (AST::Return& e) = 0;
    virtual void Visit (AST::If& e) = 0;
    virtual void Visit (AST::Block& e) = 0;
    virtual void Visit (AST::For& e) = 0;
    virtual void Visit (AST::FunctionCall& e) = 0;
    virtual void Visit (AST::FunctionDeclare& e) = 0;
    virtual void Visit (AST::Param& e) = 0;
    virtual void Visit (AST::Params& e) = 0;
};

#endif //COMPILER_VISITOR_H
