//
// Created by Ethan L. Kerr on 1/31/22.
//

#ifndef UNTITLED_PREDICATE_H
#define UNTITLED_PREDICATE_H

#include <string>
#include <vector>
#include "Parameter.h"

using namespace std;

class Predicate {

private:


public:
    string name;
    vector<Parameter> parameters;

    Predicate(const string &name) :name(name) {}

    void addParam(const Parameter& p){
        parameters.push_back(p);
    }

    string paramToString(int index) {
            return parameters[index].printName();
        }

    string predToString() {
        string predString;
        predString += (name + "(");
        for (long unsigned int i = 0; i < parameters.size(); i++) {
            if (i != parameters.size() - 1) {
                predString += paramToString(i) + ",";
            } else {
                predString += paramToString(i) + ")";
            }
        }
        return predString;
    }

    string getName() {
        return name;
    }

    vector<int> repeatParameters(string& parameter) {
        vector<int> indicesOfRepeat;
        for (long unsigned int i = 0; i < parameters.size(); i++) {
            if(parameter == parameters[i].name) {
                indicesOfRepeat.push_back(i);
            }
        }
        return indicesOfRepeat;
    }

};


#endif //UNTITLED_PREDICATE_H
