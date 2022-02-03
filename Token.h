//
// Created by Ethan L. Kerr on 1/24/22.
//
//#pragma //once?

#ifndef UNTITLED_TOKEN_H
#define UNTITLED_TOKEN_H

#include <string>
#include <sstream>

using namespace std;

enum TokenType { COMMA, ID, PERIOD, Q_MARK,
    LEFT_PAREN, RIGHT_PAREN, COLON,
    COLON_DASH, MULTIPLY, ADD,
    SCHEMES, FACTS, RULES, QUERIES,
    STRING, COMMENT, UNDEFINED, EOF_TYPE };

class Token {

private:
    TokenType type;
    string value;
    int line;

public:
    Token(TokenType type, string value, int line)
            : type(type), value(value), line(line)
    {}

    string toString() const {

        stringstream out; // Display strings
        out << "(" << typeName(type) << "," << "\"" <<  value << "\"," << line << ")";
        return out.str();
    }

    TokenType getType() const{
        return type; // TODO: this returns the index of the enum. Should it return the name?

    }

    string getValue() const {
        return value;
    }

string typeName(TokenType type) const {

    switch (type) {
        case COMMA:
            return "COMMA";
        case ID:
            return "ID";
        case STRING:
            return "STRING";
        case PERIOD:
            return "PERIOD";
        case Q_MARK:
            return "Q_MARK";
        case LEFT_PAREN:
            return "LEFT_PAREN";
        case RIGHT_PAREN:
            return "RIGHT_PAREN";
        case COLON:
            return "COLON";
        case COLON_DASH:
            return "COLON_DASH";
        case MULTIPLY:
            return "MULTIPLY";
        case ADD:
            return "ADD";
        case SCHEMES:
            return "SCHEMES";
        case FACTS:
            return "FACTS";
        case RULES:
            return "RULES";
        case QUERIES:
            return "QUERIES";
        case COMMENT:
            return "COMMENT";
        case UNDEFINED:
            return "UNDEFINED";
        case EOF_TYPE:
            return "EOF";
        default:
            return "UNDEFINED";
    }

}

};
#endif

