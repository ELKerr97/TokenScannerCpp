//
// Created by Ethan L. Kerr on 1/24/22.
//

#ifndef UNTITLED_COMMENTAUTOMATON_H
#define UNTITLED_COMMENTAUTOMATON_H
#include <string>
using namespace std;


class CommentAutomaton {

public:
    CommentAutomaton () {} // Constructor

    bool IsDefined() { return isDefined; }
    int GetNumRead() {return numRead; }
    string GetInputRead() {return inputRead; }

    void ReadInput(string input){
        for (unsigned int i = 1; i < input.length(); i++) {

            if (input.at(i) != '\n') {
                numRead = (int)(i+1);
                isDefined = true;
                inputRead = input.substr(0, numRead);
            } else if (input.at(i) == '\n') {return;}
        }

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


#endif //UNTITLED_COMMENTAUTOMATON_H
