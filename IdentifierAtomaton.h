//
// Created by Ethan L. Kerr on 1/26/22.
//

#ifndef UNTITLED_IDENTIFIERATOMATON_H
#define UNTITLED_IDENTIFIERATOMATON_H
#include <string>
using namespace std;

class IdentifierAtomaton {

public:
    IdentifierAtomaton() {}

    bool GetIsIdentifier() {return isId; }
    string GetInputRead() {return inputRead;}
    int GetNumRead() {return numRead;}

    void ReadInput(string input){
        for (unsigned int i = 0; i < input.length(); i++) {

            if (input.at(i) != '\n') {

                // Check if first character is a digit. If so, it is not an identifier.
                if (isdigit(input.at(0)) || !isalpha(input.at(0))) {
                    isId = false;
                    numRead = 1;
                    inputRead = input.substr(0, numRead);
                    return;
                }
                    // Check if next character is a number or letter
                else if (isalnum(input.at(i+1))) { // if next is letter or number, continue
                    isId = true;
                    numRead = (int)(i+1);
                    inputRead = input.substr(0, numRead);
                } else {
                    isId = true;
                    numRead = (int)(i+1);
                    inputRead = input.substr(0, numRead);
                    return;
                }

            } else if (input.at(i) == '\n') {return;}

        }
        isId = false;
        numRead = (int)input.length()-1;
        inputRead = input.substr(0, numRead);
    };

private:
    bool isId;
    string inputRead;
    int numRead;

};


#endif //UNTITLED_IDENTIFIERATOMATON_H
