//
// Created by Ethan L. Kerr on 1/24/22.
//

#ifndef UNTITLED_KEYWORDAUTOMATON_H
#define UNTITLED_KEYWORDAUTOMATON_H

#include <string>
using namespace std;

class KeyWordAutomaton {

public:
    KeyWordAutomaton() {}

    bool IsDefined() { return isDefined; }
    int GetNumRead() {return numRead; }
    string GetInputRead() {return inputRead; }
    bool isIdentifier() {return isID;}

    void ReadInput(string input) {

        if (input.at(0) == 'S') {
            if (input.at(1) == 'c' &&
                input.at(2) == 'h' &&
                input.at(3) == 'e' &&
                input.at(4) == 'm' &&
                input.at(5) == 'e' &&
                input.at(6) == 's' && !isalnum(input.at(7))) {
                isID = false;
                isDefined = true;
                inputRead = "Schemes";
                numRead = 7;

            } else {

                isID = true;
                isDefined = false;
            }

        } else if (input.at(0) == 'F') {
            if (input.at(1) == 'a' &&
                input.at(2) == 'c' &&
                input.at(3) == 't' &&
                input.at(4) == 's' && !isalnum(input.at(5))) {
                isDefined = true;
                inputRead = "Facts";
                numRead = 5;
            } else {

                isID = true;
                isDefined = false; }

        } else if (input.at(0) == 'R') {
            if (input.at(1) == 'u' &&
                input.at(2) == 'l' &&
                input.at(3) == 'e' &&
                input.at(4) == 's' && !isalnum(input.at(5))) {
                isDefined = true;
                inputRead = "Rules";
                numRead = 5;
            } else {

                isID = true;
                isDefined = false;
            }

        } else if (input.at(0) == 'Q') {
            if (input.at(1) == 'u' &&
                input.at(2) == 'e' &&
                input.at(3) == 'r' &&
                input.at(4) == 'i' &&
                input.at(5) == 'e' &&
                input.at(6) == 's' && !isalnum(input.at(7))) {
                isDefined = true;
                inputRead = "Queries";
                numRead = 7;
            } else {
                isDefined = false; }
        } else {
            isDefined = false;
        }};


private:
    int numRead;
    string inputRead;
    bool isDefined;
    bool isID;

};


#endif //UNTITLED_KEYWORDAUTOMATON_H
