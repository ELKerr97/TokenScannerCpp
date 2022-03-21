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
    set<int> joinIndices;
    set<Tuple> newTuples;

public:

    Relation(const string& name, const Scheme& scheme) : name(name), scheme(scheme) { }

    int getSize() {
        return tuples.size();
    }

    void doUnion(Relation r){
        for(auto & tuple : r.tuples){
            tuples.insert(tuple);
        }
    }

    Tuple joinTuples(const Tuple& leftTuple, const Tuple& rightTuple){
        // Join two tuples

        vector<string> values;

        // Add all the values from the left tuple first
        for(auto & leftValue : leftTuple) {

            values.push_back(leftValue);
        }


        // Add rest of values in right tuple that correspond to the correct indices
        for(auto & index : joinIndices){

            values.push_back(rightTuple.at(index));

        }


/*
        // Add all the values in the right tuple that aren't in the left tuple (no repeats allowed in this case)
        for(auto & rightValue : rightTuple){

            bool repeat = false;

//            for(auto & value : values){
//                if(value == rightValue){
//
//                    repeat = true;
//                }
//            }

            if(rightValue == values.at(values.size() - 1)){
                repeat = true;
            }

            if(!repeat){
                values.push_back(rightValue);
            }

        }
        */


        Tuple joinedTuple = Tuple(values);
        return joinedTuple;
    }

    Scheme joinSchemes(const Scheme& leftScheme, const Scheme& rightScheme){
        // Join two schemes
        vector<string> newSchemeNames;

        for(auto & name : leftScheme) {
            //cout << name << endl;
            newSchemeNames.push_back(name);
        }
/*
        for(auto & index : joinIndices){
            //cout << "yep" << rightScheme.at(index) << endl;
            newSchemeNames.push_back(rightScheme.at(index));
        }
        */


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

    // Get different tuples
    set<Tuple> diffTuples(Relation r) {
        set<Tuple> diffTuples;

        if(tuples.empty()){
            for(auto & rightTuple : r.tuples){
                diffTuples.insert(rightTuple);
            }
        } else {
            for(auto & leftTuple : tuples){
                for(auto & rightTuple : r.tuples){
                    if(leftTuple != rightTuple ){

                        bool repeat = false;
                        for(auto & curTuple : tuples){
                            if(curTuple == rightTuple){
                                repeat = true;
                            }
                        }

                        if(!repeat){
                            //cout << tuple2.schemeTupleToString(r.scheme) << endl;
                            diffTuples.insert(rightTuple);
                        }
                    }
                }
            }
        }


        return diffTuples;
    }

    Relation join(Relation r) {

        const Scheme& leftScheme = scheme;
        const Scheme& rightScheme = r.scheme;
        setJoinIndices(leftScheme, rightScheme);

        Scheme newScheme = joinSchemes(leftScheme, rightScheme);

        Relation newRelation = Relation("intermediateRelation", newScheme);

        for (const Tuple& leftTuple : tuples) {

            for (const Tuple& rightTuple : r.tuples) {

                // If tuples in scheme are join-able, make the tuples
                if(joinable(leftScheme, rightScheme, leftTuple, rightTuple)){

                    Tuple joinedTuple = joinTuples(leftTuple, rightTuple);

                    newRelation.addTuple(joinedTuple);

                }
            }
        }
        joinIndices.clear();
        //cout << newRelation.relationNameToString() << endl;
        //cout << newRelation.relationToString() << endl;
        return newRelation;
    }

    void setJoinIndices(const Scheme& leftScheme, const Scheme& rightScheme) {

        // Find the indices from the right tuple to add to the left tuple.
        for (unsigned leftIndex = 0; leftIndex < leftScheme.size(); leftIndex++) {
            const string &leftName = leftScheme.at(leftIndex);

            for (unsigned rightIndex = 0; rightIndex < rightScheme.size(); rightIndex++) {
                const string &rightName = rightScheme.at(rightIndex);

                // Add that index if the names are not the same.
                if(leftName != rightName){
                    bool isInLeft = false;
                    for(auto & left : leftScheme){
                        if(rightName == left){
                            isInLeft = true;
                        }
                    }
                    if(!isInLeft){
                        //cout << rightIndex << endl;
                        joinIndices.insert(rightIndex);
                    }
                }
            }
        }
    }

    static bool joinable(const Scheme& leftScheme, const Scheme& rightScheme,
                         const Tuple& leftTuple, const Tuple& rightTuple) {

        bool foundSameName = false;
        bool joinable = false;
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

                    if(leftValue == rightValue) {
                        joinable = true;

                    }
                }
            }
        }

        // If none of the scheme names match, they **are join-able
        if(!foundSameName) {
            joinable = true;
        }

        return joinable;
    }

    vector<string> getScheme() {
        return scheme;
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
