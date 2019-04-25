# cmake_minimum_required(VERSION <specify CMake version here>)
project(Compiler)

set(CMAKE_CXX_STANDARD 14)

add_executable(Compiler main.cpp Lexer.h Lexer.cpp ASTNode/ASTNode.h ASTNode/ASTStatementNode/Statement.h ASTNode/ASTStatementNode/If.h Visitor/Visitor.h ASTNode/ASTExpressionNode/Expr.h ASTNode/Program.h Parser.h Parser.cpp Util.cpp Util.h ASTNode/ASTStatementNode/Return.h ASTNode/ASTStatementNode/Function.h ASTNode/ASTStatementNode/Block.h ASTNode/ASTStatementNode/AssignmentStatement.h Visitor/PrintInfoVisitor.h ASTNode/ASTExpressionNode/ExprConst.h ASTNode/ASTExpressionNode/ExprVar.h ASTNode/ASTExpressionNode/Var.h ASTNode/ASTExpressionNode/Unary/ExprUnOp.h ASTNode/ASTExpressionNode/Unary/ExprUnOpNeg.h ASTNode/ASTExpressionNode/Binary/ExprBinOp.h ASTNode/ASTExpressionNode/Binary/ExprBinOpAdd.h ASTNode/ASTExpressionNode/Binary/ExprBinOpSub.h ASTNode/ASTExpressionNode/Binary/ExprBinOppMul.h ASTNode/ASTExpressionNode/Binary/ExprBinOppDiv.h)