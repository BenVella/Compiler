# cmake_minimum_required(VERSION <specify CMake version here>)
project(Compiler)

set(CMAKE_CXX_STANDARD 14)

add_executable(Compiler main.cpp Lexer.h Lexer.cpp ASTNode/ASTNode.h ASTNode/ASTStatementNode/ASTStatementNode.h ASTNode/ASTStatementNode/ASTIfNode.h Visitor.cpp Visitor.h ASTNode/ASTExpressionNode/ASTExprNode.h ASTNode/ASTStatementNode/ASTVariableNode.h ASTNode/ASTProgramNode.h Parser.h Parser.cpp Util.cpp Util.h ASTNode/ASTStatementNode/ASTReturnNode.h ASTNode/ASTStatementNode/ASTFunctionNode.h ASTNode/ASTExpressionNode/ASTSimpleExprNode.h ASTNode/ASTExpressionNode/ASTBinaryExprNode.h ASTNode/ASTExpressionNode/ASTUnaryExprNode.h)