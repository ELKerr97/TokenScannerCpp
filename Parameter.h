//
// Created by Ethan L. Kerr on 1/31/22.
//

#ifndef UNTITLED_PARAMETER_H
#define UNTITLED_PARAMETER_H

#include <string>
#include "Token.h"

using namespace std;

class Parameter {

private:

public:
    string name;

    Parameter(const string &name) : name(name){}

    string printName() {
        return name;
    }

    bool isConstant() {
        if(!isalpha(name.at(0))){
            return true;
        } else
        return false;
    }



};


#endif //UNTITLED_PARAMETER_H
