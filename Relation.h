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

    Tuple joinTuples(const Tuple& leftTuple, const Tuple& rightTuple){
        // Join two tuples

        vector<string> values;

        // Add all the values from the left tuple first
        for(auto & leftValue : leftTuple) {
            //cout << leftValue << endl;
            values.push_back(leftValue);
        }

        // Add all the values in the right tuple that aren't in the left tuple (no repeats allowed in this case)
        for(auto & rightValue : rightTuple){

            bool repeat = false;

            for(auto & value : values){
                if(value == rightValue){
                    //cout << "false" << endl;
                    repeat = true;
                }
            }

            if(!repeat){
                values.push_back(rightValue);
            }

        }

        Tuple joinedTuple = Tuple(values);

        return joinedTuple;
    }

    Scheme joinSchemes(const Scheme& leftScheme, const Scheme& rightScheme){
        // Join two schemes
        vector<string> newSchemeNames;

        for(auto & name : leftScheme) {
            newSchemeNames.push_back(name);
        }


        for(auto & name : rightScheme){
            // Check for repeat names

            bool repeat = false;

            for(auto & schemeName : newSchemeNames) {
                if(name == schemeName) {
                    repeat = true;
                }
            }

            if(!repeat){
                newSchemeNames.push_back(name);
            }

        }

        // Return new scheme with joined scheme names
        return Scheme(newSchemeNames);
    }

    Relation join(Relation r) {

        const Scheme& leftScheme = scheme;
        const Scheme& rightScheme = r.scheme;
        Scheme newScheme = joinSchemes(leftScheme, rightScheme);
        for(auto & name : newScheme){
            //cout << name << endl;
        }
        Relation newRelation = Relation("intermediateRelation", newScheme); // What should the name be?

        for (const Tuple& leftTuple : tuples) {

            for (const Tuple& rightTuple : r.tuples) {

                // If tuples in scheme are joinable, make the tuples
                if(joinable(leftScheme, rightScheme, leftTuple, rightTuple)){

                    Tuple joinedTuple = joinTuples(leftTuple, rightTuple);

                    newRelation.addTuple(joinedTuple);

                }



            }

        }
        //cout << newRelation.relationNameToString() << endl;
        cout << newRelation.relationToString() << endl;
        return newRelation;
    }

    static bool joinable(const Scheme& leftScheme, const Scheme& rightScheme,
                         const Tuple& leftTuple, const Tuple& rightTuple) {

        bool foundSameName = false;

        // Loop over left scheme and tuple, print names and values of left scheme and tuple
        for (unsigned leftIndex = 0; leftIndex < leftScheme.size(); leftIndex++) {
            const string &leftName = leftScheme.at(leftIndex);
            const string &leftValue = leftTuple.at(leftIndex);
            //cout << "left name: " << leftName << " value: " << leftValue << endl;

            // Loop over right scheme and tuple, print names and values of right scheme and tuple
            for (unsigned rightIndex = 0; rightIndex < rightScheme.size(); rightIndex++) {
                const string &rightName = rightScheme.at(rightIndex);
                const string &rightValue = rightTuple.at(rightIndex);
                //cout << "right name: " << rightName << " value: " << rightValue << endl;

                // Check to see if the tuples are not a match (names are the same, but values are not equal).
                if (leftName == rightName){
                    foundSameName = true;

                    if(leftValue != rightValue) {
                        return false;
                    }
                }

            }
        }

        // If none of the scheme names match, they are not joinable
        if(!foundSameName) {
            return false;
        }

        return true;
    }

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

        for (auto& tuple : tuples) {

            out << "  " << tuple.schemeTupleToString(scheme) << endl;

        }

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

        // TODO: Re-order columns in the same order as the attributes in the rule or query
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
