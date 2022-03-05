//
// Created by Ethan L. Kerr on 2/22/22.
//

#ifndef UNTITLED_TUPLE_H
#define UNTITLED_TUPLE_H

#include <string>
#include <vector>
#include <sstream>
#include "Scheme.h"

using namespace std;

/**
 * Tuple class stores Tuples of String type.
 *
 * Note: Use a <set> of Tuples in database. This will eliminate duplicates and give the right order to the output.
 */
class Tuple : public vector<string> {

public:

    Tuple(vector<string> values) : vector<string>(values) { }

    string schemeTupleToString(const Scheme& scheme) const {
        stringstream out;
        for (unsigned i = 0; i < size() ;i++ ) {
            if (i > 0)
                out << ", ";
            const string& name = scheme.at(i);
            const string& value = at(i);
            out << name << "=" << value;
        }
        return out.str();

    }



};


#endif //UNTITLED_TUPLE_H
