//
// Created by Ethan L. Kerr on 1/24/22.
//

#ifndef UNTITLED_STRINGAUTOMATON_H
#define UNTITLED_STRINGAUTOMATON_H
#include <string>
using namespace std;

class StringAutomaton {

public:
    StringAutomaton () {} // Constructor

    bool IsDefined() { return isDefined; }
    int GetLinesRead() {return newLines; }
    int GetNumRead() {return numRead; }
    string GetInputRead() {return inputRead; }

    void ReadInput(string input){
        newLines = 0;

        for (unsigned int i = 1; i < input.length(); i++) {

            if (input.at(i) == '\n') {newLines += 1;}
            if (input.at(i) != '\'') {
                numRead = (int)(i+1);
                isDefined = true;
                inputRead = input.substr(0, numRead);
            } else if (input.at(i) == '\'') {

                // Read in the last quote
                numRead = (int)(i+1);

                // Include last quote in output
                inputRead = input.substr(0, numRead);

                return;
            }
        }
        newLines -= 1;
        numRead = (int)input.length()-1;
        inputRead = input.substr(0, numRead);
        isDefined = false;
    };

private:
    int numRead;
    int newLines;
    string inputRead;
    bool isDefined;

};


#endif //UNTITLED_STRINGAUTOMATON_H
