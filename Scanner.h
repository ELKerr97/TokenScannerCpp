//
// Created by Ethan L. Kerr on 1/24/22.
//

#include <string>
#include <cctype>
#include <iostream>
#include <sstream>
#include <istream>
#include "StringAutomaton.h"
//#include "StringAutomaton.cpp"
#include "CommentAutomaton.h"
//#include "CommentAutomaton.cpp"
#include "KeyWordAutomaton.h"
//#include "KeyWordAutomaton.cpp"
#include "IdentifierAtomaton.h"
//#include "IdentifierAtomaton.cpp"
#include <vector>
#include <fstream>
#include <string>
using namespace std;

class Scanner {

private:
    string input;

public:
    Scanner(const string& input) : input(input) { }

    vector<Token> Run() { // TODO: turn into .run() and put it in a while loop until it reaches the end of the file.

        TokenType type;
        int size = 0;
        int line = 1;
        string value;
        vector<Token> tokens;
        StringAutomaton stringAutomaton;
        CommentAutomaton commentAutomaton;
        KeyWordAutomaton keyWordAutomaton;
        IdentifierAtomaton idAutomaton;

        // Check to see if file is empty
        if (input.empty()) {
            tokens.push_back(Token(type = EOF_TYPE, value = "", line = 1 ));
            return tokens;
        } else {
            while (input.at(0) != EOF) {
                if (input.at(0) == '\n') {
                    input = input.substr(1); // skip over the new line
                    line++; }

                // increment the token
                input = input.substr(size);

                while (isspace(input.at(0))){
                    if (input.at(0) == '\n' && input.size() != 1) {
                        line ++;
                        input = input.substr(1);
                    } else if (input.at(0) == '\t') {
                        input = input.substr(1);
                    } else if (input.at(0) == ' ') {
                        input = input.substr(1);
                    } else if (input.size() == 1) { // Check for end of file with content
                        line ++;
                        tokens.push_back(Token(type = EOF_TYPE, value = "", line = line));
                        return tokens;
                    }
                }
                // determine which token is being read, set the type, size and value, then add Token object to vector
                switch (input.at(0)) {
                    // TODO: Fix crazy numbers in output
                    case ',':
                        type = COMMA;
                        size = 1;
                        value = input.substr(0, size);
                        tokens.push_back(Token(type, value, line));
                        break;
                    case '.':
                        type = PERIOD;
                        size = 1;
                        value = input.substr(0, size);
                        tokens.push_back(Token(type, value, line));
                        break;
                    case '?':
                        type = Q_MARK;
                        size = 1;
                        value = input.substr(0, size);
                        tokens.push_back(Token(type, value, line));
                        break;
                    case '(':
                        type = LEFT_PAREN;
                        size = 1;
                        value = input.substr(0, size);
                        tokens.push_back(Token(type, value, line));
                        break;
                    case ')':
                        type = RIGHT_PAREN;
                        size = 1;
                        value = input.substr(0, size);
                        tokens.push_back(Token(type, value, line));
                        break;
                    case ':':
                        if (input.at(1) == '-'){
                            type = COLON_DASH;
                            size = 2;
                            value = input.substr(0,size);
                        } else {
                            type = COLON;
                            size = 1;
                            value = input.substr(0, size);
                        }
                        tokens.push_back(Token(type, value, line));
                        break;
                    case '*':
                        type = MULTIPLY;
                        size = 1;
                        value = input.substr(0, size);
                        tokens.push_back(Token(type, value, line));
                        break;
                    case '+':
                        type = ADD;
                        size = 1;
                        value = input.substr(0, size);
                        tokens.push_back(Token(type, value, line));
                        break;
                    case '$':
                        type = UNDEFINED;
                        size = 1;
                        value = input.substr(0, size);
                        tokens.push_back(Token(type, value, line));
                        break;
                    case '&':
                        type = UNDEFINED;
                        size = 1;
                        value = input.substr(0, size);
                        tokens.push_back(Token(type, value, line));
                        break;
                    case '^':
                        type = UNDEFINED;
                        size = 1;
                        value = input.substr(0, size);
                        tokens.push_back(Token(type, value, line));
                        break;
                    case '\'':
                        stringAutomaton.ReadInput(input);
                        if (stringAutomaton.IsDefined()) { type = STRING; }
                        else if (!stringAutomaton.IsDefined()) { type = UNDEFINED; }
                        size = stringAutomaton.GetNumRead();
                        value = stringAutomaton.GetInputRead();
                        tokens.push_back(Token(type, value, line));
                        line += stringAutomaton.GetLinesRead();
                        break;
                    case '#':
                        commentAutomaton.ReadInput(input);
                        if (commentAutomaton.IsDefined()) { type = COMMENT; }
                        else if (!commentAutomaton.IsDefined()) { type = UNDEFINED; }
                        size = commentAutomaton.GetNumRead();
                        value = commentAutomaton.GetInputRead();
                        // Ignore comments in Datalog Parser
                        // tokens.push_back(Token(type, value, line));
                        break;
                    case 'S':
                        keyWordAutomaton.ReadInput(input);
                        if (keyWordAutomaton.IsDefined()) {
                            type = SCHEMES;
                            value = keyWordAutomaton.GetInputRead();
                            size = keyWordAutomaton.GetNumRead();
                            tokens.push_back(Token(type, value, line));
                        } else {
                            type = ID;
                            idAutomaton.ReadInput(input);
                            value = idAutomaton.GetInputRead();
                            size = idAutomaton.GetNumRead();
                            tokens.push_back(Token(type, value, line));
                        }
                        break;
                    case 'F':
                        keyWordAutomaton.ReadInput(input);
                        if (keyWordAutomaton.IsDefined()) {
                            type = FACTS;
                            value = keyWordAutomaton.GetInputRead();
                            size = keyWordAutomaton.GetNumRead();
                            tokens.push_back(Token(type, value, line));
                        } else {
                            type = ID;
                            idAutomaton.ReadInput(input);
                            value = idAutomaton.GetInputRead();
                            size = idAutomaton.GetNumRead();
                            tokens.push_back(Token(type, value, line));
                        }
                        break;
                    case 'R':
                        keyWordAutomaton.ReadInput(input);
                        if (keyWordAutomaton.IsDefined()) {
                                type = RULES;
                                value = keyWordAutomaton.GetInputRead();
                                size = keyWordAutomaton.GetNumRead();
                                tokens.push_back(Token(type, value, line));

                        } else {
                            type = ID;
                            idAutomaton.ReadInput(input);
                            value = idAutomaton.GetInputRead();
                            size = idAutomaton.GetNumRead();
                            tokens.push_back(Token(type, value, line));
                        }
                        break;
                    case 'Q':
                        keyWordAutomaton.ReadInput(input);
                        if (keyWordAutomaton.IsDefined()) {
                            type = QUERIES;
                            value = keyWordAutomaton.GetInputRead();
                            size = keyWordAutomaton.GetNumRead();
                            tokens.push_back(Token(type, value, line));
                        } else {
                            type = ID;
                            idAutomaton.ReadInput(input);
                            value = idAutomaton.GetInputRead();
                            size = idAutomaton.GetNumRead();
                            tokens.push_back(Token(type, value, line));
                        }
                        break;
                    default:
                        // TODO: check for other cases like X,Y. Supposed to be 3 tokens.
                        idAutomaton.ReadInput(input);
                        if (idAutomaton.GetIsIdentifier()) {type = ID;}
                        else if (!idAutomaton.GetIsIdentifier()) {type = UNDEFINED;}
                        size = idAutomaton.GetNumRead();
                        value = idAutomaton.GetInputRead();
                        tokens.push_back(Token(type, value, line));
                        break;
                }
            }
        }
        return tokens;
    }
};


