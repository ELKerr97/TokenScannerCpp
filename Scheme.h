//
// Created by Ethan L. Kerr on 2/22/22.
//

#ifndef UNTITLED_SCHEME_H
#define UNTITLED_SCHEME_H
#include <string>
#include <vector>

using namespace std;


class Scheme : public vector<string> {

public:
    Scheme(vector<string> names) : vector<string>(names) { }

};


#endif //UNTITLED_SCHEME_H
