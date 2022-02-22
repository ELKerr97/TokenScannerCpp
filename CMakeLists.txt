cmake_minimum_required(VERSION 3.16.3)
project(untitled)

set(CMAKE_CXX_STANDARD 17)

add_executable(untitled main.cpp Token.h Scanner.h StringAutomaton.h  CommentAutomaton.h  KeyWordAutomaton.h  IdentifierAtomaton.h  Parser.h Predicate.h DatalogProgram.h Rule.h Parameter.h Scheme.h Tuple.h Relation.h)
