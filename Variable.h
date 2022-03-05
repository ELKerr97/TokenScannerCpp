//
// Created by Ethan L. Kerr on 3/3/22.
//

#ifndef UNTITLED_VARIABLE_H
#define UNTITLED_VARIABLE_H

#include <string>
#include <vector>

using namespace std;

class Variable {

private:



public:

    string name;
    vector<int> indices;

    Variable(const string& name, const vector<int>& indices) : name(name), indices(indices) {}

    string getVariableName() {

        return name;
    }

    vector<int> getIndices() {

        return indices;
    }
};


#endif //UNTITLED_VARIABLE_H
