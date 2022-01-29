//
// Created by Ethan L. Kerr on 1/28/22.
//

#ifndef UNTITLED_PARSER_H
#define UNTITLED_PARSER_H

#include <iostream>
#include <vector>
#include "Token.h"

class Parser {
private:
    vector<Token> tokens;

public:
    Parser(const vector<Token>& tokens) : tokens(tokens) { }


    TokenType tokenType() const{
        return tokens.at(0).getType();
    }

    void advanceToken() {
            tokens.erase(tokens.begin());
        }

    void throwError() {
        cout << "error" << endl;
    }

};



#endif //UNTITLED_PARSER_H
