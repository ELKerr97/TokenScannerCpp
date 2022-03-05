//
// Created by Ethan L. Kerr on 2/22/22.
//

#ifndef UNTITLED_RELATION_H
#define UNTITLED_RELATION_H

#include <string>
#include "Scheme.h"
#include "Tuple.h"
#include <set>

using namespace std;

/**
 * Represents a table in a database.
 * A Relation has a name, a Scheme, and a set of Tuples.
 *
 * name -> used to uniquely identify the Relation
 * Scheme -> gives the names of the columns of the Relation
 * Tuples -> gives the values of the rows of the Relation
 *
 * Scheme and Tuples of relation must be same size
 */
class Relation {

private:

    string name;
    Scheme scheme;
    set<Tuple> tuples;

public:

    Relation(const string& name, const Scheme& scheme) : name(name), scheme(scheme) { }

    void rename(vector<string> newNames) {
        Scheme newScheme = Scheme(newNames);
        scheme = newScheme;
    }

    void addTuple(const Tuple& tuple) {
        tuples.insert(tuple);
    }

    int getTupleNum() {
        return tuples.size();
    }

    string relationNameToString() const {

        return name;
    }

    string relationToString() const {
        stringstream out;
        for (auto& tuple : tuples)

            out << tuple.schemeTupleToString(scheme) << endl;

        return out.str();
    }

    /**
     * Returns a new Relation that contains a subset of Tuples
     * from an existing Relation that meet a select condition.
     *
     * In this case, the select condition is that a given position
     * in the Tuple must have a given value.
    */
    Relation selectSingleIndex(int index, const string& value) const {
        Relation result(name, scheme);
        for (auto& tuple : tuples)
            if (tuple.at(index) == value)
                result.addTuple(tuple);
        return result;
    }

    /**
     * Returns a new Relation that contains a subset of Tuples
     * from an existing Relation that meet a certain condition.
     *
     * In this case, the select condition is that multiple positions
     * in the Tuple must have the same given value
     */

    // TODO: Handle more than two indexes in case variable shows up more than twice in the same query
    Relation selectMultipleIndexes(vector<int> indices) const {
        Relation result(name, scheme);
        vector<string> tupleElements;
        for (auto& tuple : tuples) {

            // add each element at those indices to compare
            for (auto &index: indices) {
                tupleElements.push_back(tuple.at(index));
            }

            // If all elements are equal, add tuple to result
            if(std::equal(tupleElements.begin() + 1, tupleElements.end(), tupleElements.begin())){
                result.addTuple(tuple);
            }

            // Clear tuple elements list for next tuple
            tupleElements.clear();
        }
        return result;
    }

    Relation project(vector<int> indices) const {

        Relation result(name, scheme);
        for (auto& tuple : tuples) {
            vector<string> newTupleVals;
            for (auto & index : indices) {
                newTupleVals.push_back(tuple.at(index));
            }
            Tuple newTuple(newTupleVals);
            result.addTuple(newTuple);
        }

        return result;
    }

};


#endif //UNTITLED_RELATION_H
