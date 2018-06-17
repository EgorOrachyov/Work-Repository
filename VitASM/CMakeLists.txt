cmake_minimum_required(VERSION 3.9)
project(VitASM C)

set(CMAKE_C_STANDARD 99)

add_executable(VitASM main.c Stack.h Stack.c Parser.h Parser.c ASMformat.h Interpreter.h CommandStructure.h Interpreter.c)