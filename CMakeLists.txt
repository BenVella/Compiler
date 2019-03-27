# cmake_minimum_required(VERSION <specify CMake version here>)
project(Compiler)

set(CMAKE_CXX_STANDARD 14)

add_executable(Compiler main.cpp Lexer.h Lexer.cpp ASTNode/ASTNode.h ASTNode/ASTStatementNode.h ASTNode/ASTIfStatementNode.h ASTNode/Visitor.cpp ASTNode/Visitor.h ASTNode/ASTExprNode.cpp ASTNode/ASTExprNode.h ASTNode/ASTVariableExprNode.h ASTNode/ASTProgramNode.h ASTNode/Parser.h ASTNode/Parser.cpp Util.cpp Util.h ASTNode/ASTReturnStatementNode.h ASTNode/ASTFunctionNode.h ASTNode/ASTFuncPrototypeNode.h)