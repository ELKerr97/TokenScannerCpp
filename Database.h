//
// Created by Ethan L. Kerr on 2/28/22.
//

#ifndef UNTITLED_DATABASE_H
#define UNTITLED_DATABASE_H

#include "DatalogProgram.h"
#include <vector>
#include <string>
#include "Relation.h"
#include "Scheme.h"
#include "Tuple.h"
#include "Variable.h"

using namespace std;

class Database {

private:

    DatalogProgram datalogProgram;
    vector<Relation> relations;
    vector<Variable> variables;

public:

    Database(const DatalogProgram& datalogProgram) : datalogProgram(datalogProgram) {}

    void createDatabase() {

        // Create empty Relations
        createEmptyRelations();

        // Add Tuples to Relations
        addTuplesToRelations();

        // Evaluate Queries
        evaluateQueries();

    }

    void createEmptyRelations() {

        // For each scheme...
        for(long unsigned int i = 0; i < datalogProgram.schemes.size() ; i ++ ) {
            vector<string> attributes;

            // For each attribute in scheme...
            for (long unsigned int j = 0; j < datalogProgram.schemes[i].parameters.size() ; j ++) {

                // Add attribute
                attributes.push_back(datalogProgram.schemes[i].parameters[j].printName());

            }

            // Create new scheme object with attribute names
            Scheme newScheme = Scheme(attributes);

            // Create new relation object with scheme name and scheme
            Relation newRelation = Relation(datalogProgram.schemes[i].getName(), newScheme);

            // Add new relation to vector of Relations
            relations.push_back(newRelation);
        }
    }

    void addTuplesToRelations() {
        // Iterate through each relation
        for(long unsigned int i = 0; i < relations.size(); i ++) {

            // Iterate through each fact
            for (long unsigned int j = 0; j < datalogProgram.facts.size(); j++) {

                // Check if fact and relation name are the same
                if (datalogProgram.facts[j].getName() == relations[i].relationNameToString()) {

                    // Make a temporary vector of tuple values
                    vector<string> tupleValues;

                    // Iterate through each fact parameter
                    for (long unsigned int factParameter = 0;
                         factParameter < datalogProgram.facts[j].parameters.size(); factParameter++) {

                        // Add each parameter to temporary tuple value
                        tupleValues.push_back(datalogProgram.facts[j].parameters[factParameter].printName());
                    }

                    // Create new Tuple object from temporary tuple values
                    Tuple newTuple = Tuple(tupleValues);

                    // Add Tuple object to correct relation
                    relations[i].addTuple(newTuple);
                }

            }

        }

    }

    void evaluateQueries() {

        // Iterate through each query
        for(auto & query : datalogProgram.queries){
            cout << query.predToString() << "? ";
            // Iterate through each Relation
            for(auto relation : relations) {

                //cout << relation.relationNameToString() << endl;

                // Check if query and relation match
                if (query.getName() == relation.relationNameToString()) {

                    // Iterate through each parameter in query
                    for (long unsigned int qParamIndex = 0; qParamIndex < query.parameters.size(); qParamIndex++) {

                        // Is parameter a constant?
                        if (query.parameters[qParamIndex].isConstant()) {


                            // If constant, select tuples from Relation that have same values as constant in same position as constant
                            relation = relation.selectSingleIndex(qParamIndex, query.parameters[qParamIndex].name);

                            // Is parameter a variable?
                        } else {

                            bool repeatVar = false;

                            // Check if the variable has already been accounted for in the query
                            for (auto &variable: variables) {
                                if (query.parameters[qParamIndex].name ==
                                    variable.getVariableName()) {
                                    repeatVar = true;
                                }
                            }

                            // If first time variable shows up in query, add new variable
                            if (!repeatVar) {

                                Variable newVariable = Variable(
                                        query.parameters[qParamIndex].name,
                                        query.repeatParameters(
                                                query.parameters[qParamIndex].name));

                                //cout << newVariable.getVariableName() << endl;

                                // Add new variable to variables to be used when projecting the relation
                                variables.push_back(newVariable);

                                if(newVariable.indices.size() > 1) {
                                    // Multiple indices. Assuming the same variable can only show up twice.
                                    relation = relation.selectMultipleIndexes(newVariable.indices);
                                }

                            }

                        }

                    }



                }

                //cout << relation.relationToString() << endl;

                // TODO: Project
                // First, check if the relation has any tuples. If not, the query evaluates to no.
                if(relation.getTupleNum() != 0) {

                    // TODO: Rename
                    vector<string> newSchemeNames;
                    for(auto & variable : variables) {
                        newSchemeNames.push_back(variable.name);
                    }

                    relation.rename(newSchemeNames);

                    // If no variables given in query, simply print yes followed by the number of tuples
                    if(variables.empty()) {

                        cout << "Yes(" << relation.getTupleNum() << ")" << endl;

                    } else {
                        vector<int> projectIndices;
                        //cout << relation.relationToString() << endl;

                        // Iterate through each variable and do a project and collect indices of those variables
                        for(auto & variable : variables) {

                            projectIndices.push_back(variable.indices[0]);

                        }
                        Relation projectedRelation = relation.project(projectIndices);
                        cout << "Yes(" << relation.getTupleNum() << ")" << endl;
                        cout << projectedRelation.relationToString() << endl;
                        projectIndices.clear();
                    }
                } else {
                    cout << "No" << endl;
                }

                // Iterate through each relation




            }



            variables.clear();
        }
    }


};


#endif //UNTITLED_DATABASE_H
