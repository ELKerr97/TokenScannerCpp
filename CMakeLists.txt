cmake_minimum_required(VERSION 3.16.3)
project(untitled)

set(CMAKE_CXX_STANDARD 17)

add_executable(untitled main.cpp Token.h Scanner.h StringAutomaton.h CommentAutomaton.cpp CommentAutomaton.h KeyWordAutomaton.cpp KeyWordAutomaton.h IdentifierAtomaton.cpp IdentifierAtomaton.h Parser.cpp Parser.h)
