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
#include "Graph.h"
#include <set>

using namespace std;

class Database {

private:

    DatalogProgram datalogProgram;
    vector<Relation> relations;
    vector<Variable> variables;
    Graph dependencyGraph = Graph(0);
    Graph reverseGraph = Graph(0);

public:

    Database(const DatalogProgram& datalogProgram) : datalogProgram(datalogProgram) {}

    void createDatabase() {

        // Create empty Relations
        createEmptyRelations();

        // Add Tuples to Relations
        addTuplesToRelations();

        // Evaluate Rules
        evaluateComponents();

        // Evaluate Queries
        cout << "\nQuery Evaluation" << endl;
        evaluateQueries();

    }

    void evaluateComponents() {

        // Make a reverse dependency graph from the rules
        reverseGraph = datalogProgram.makeReverseGraph(datalogProgram.rules);

        // Put all the nodes in the correct order
        for(long unsigned int i = 0; i < datalogProgram.rules.size(); i ++){

            // Iterate through each node and do a depth-first search. ***Initially in reverse post-order
            // (highest number will be at the beginning)
            datalogProgram.dfsForest(i, reverseGraph);
        }

        dependencyGraph = datalogProgram.makeGraph(datalogProgram.rules);

        // Print Dependency Graph
        cout << "Dependency Graph\n" << dependencyGraph.toString() << endl;

        // Print Rule Evaluation
        cout << "Rule Evaluation" << endl;

        vector<int>::reverse_iterator rit;
        // Run dfs on the original dependency graph, starting with the node with the highest post-order number.
        for(rit = datalogProgram.forestNodes.rbegin(); rit != datalogProgram.forestNodes.rend(); rit ++) {

            // Reset the SCC's after each iteration
            datalogProgram.scc.clear();

            // depth-first search
            datalogProgram.dfs(*rit, dependencyGraph);

            set<int>::iterator itr1;

            // Check if there are Components to evaluate
            if(!datalogProgram.scc.empty()) {
                cout << "SCC: ";
                long unsigned int counter = 0;
                for (itr1 = datalogProgram.scc.begin(); itr1 != datalogProgram.scc.end(); itr1++) {

                    counter ++;
                    if(counter == datalogProgram.scc.size()){
                        cout << "R" << *itr1;
                    } else {
                        cout << "R" << *itr1 << ",";
                    }

                }
                cout << endl;


                // Evaluate rules in SCC's in numerical order (should be in order because they're in a set)
                vector<int> rulesInSCC;

                set<int>::iterator itr; // Using reverse iterator to make sure rules are evaluated in right order
                // Put rules in SCC into a set
                for (itr = datalogProgram.scc.begin(); itr != datalogProgram.scc.end(); itr++) {

                    rulesInSCC.push_back(*itr);

                }

                evaluateRules(rulesInSCC);

                // Clear the rules
                rulesInSCC.clear();
            }
        }

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

    /**
     * evaluateRules() evaluates rules in database.
     * This is repeated until there are no changes to the tuples in the relations.
     */
    void evaluateRules(vector<int> ruleIndices) {

        // Will run until there are no changes
        bool changes = true;
        int iterations = 0;

        vector<Relation> ruleRelations;

        while (changes) {

            // Keep track of how many iterations through the rules
            iterations ++;

            // set to false at beginning of loop, will switch to true when a tuple is added to a relation
            changes = false;
            int numChanges = 0;

            // Go through each rule in vector of rules
            for(auto & index : ruleIndices){
                Rule rule = datalogProgram.rules.at(index);
                cout << rule.ruleToString() << endl;
                vector<Relation> rightSideRules;

                // Evaluate the right side of the rule
                for(auto & rightRule : rule.predicateList){

                    // Iterate through each Relation
                    for(auto & relation : relations){
                        Relation newRelation = relation;
                        // Check if rule and relation match
                        if(rightRule.name == relation.relationNameToString()){

                            // Iterate through each parameter in rule.
                            // All parameters will be variables, so no need to check for constants.
                            for(long unsigned int rParamIndex = 0; rParamIndex < rightRule.parameters.size() ; rParamIndex ++){

                                // Is it a constant?
                                if (rightRule.parameters[rParamIndex].isConstant()){

                                    // if constant, select tuples from relation that have same values
                                    newRelation = newRelation.selectSingleIndex(rParamIndex, rightRule.parameters[rParamIndex].name);

                                    // Is it a variable?
                                } else {
                                    bool repeatVar = false;

                                    // Check if the variable has already been accounted for in the rule
                                    for (auto &variable: variables) {
                                        if (rightRule.parameters[rParamIndex].name ==
                                            variable.getVariableName()) {
                                            repeatVar = true;
                                        }
                                    }

                                    // If first time variable shows up in rule, add new variable
                                    if (!repeatVar) {

                                        Variable newVariable = Variable(
                                                rightRule.parameters[rParamIndex].name,
                                                rightRule.repeatParameters(
                                                        rightRule.parameters[rParamIndex].name));

                                        // Add new variable to variables to be used when projecting the relation
                                        variables.push_back(newVariable);

                                        // Make sure there are variables to add to relation
                                        if(!newVariable.indices.empty()) {

                                            // Create the new relation with
                                            newRelation = newRelation.selectMultipleIndexes(newVariable.indices);
                                        }

                                    }
                                }

                            }

                            // Rename
                            vector<string> newSchemeNames;
                            for(auto & variable : variables) {
                                newSchemeNames.push_back(variable.name);
                            }

                            newRelation.rename(newSchemeNames);

                            // Project
                            vector<int> projectIndices;

                            // Iterate through each variable and do a project and collect indices of those variables
                            for(auto & variable : variables) {

                                projectIndices.push_back(variable.indices[0]);

                            }
                            Relation projectedRelation = newRelation.project(projectIndices);
                            //cout << projectedRelation.relationToString();
                            projectIndices.clear();

                            rightSideRules.push_back(projectedRelation);
                        }
                    }

                    variables.clear();

                }

                // Join Rules

                // Start with the first relation
                Relation singleRelation = rightSideRules[0];

                // If two or more predicates on right-hand side, join intermediate results
                if(rightSideRules.size() > 1) {

                    // Iterate through each right-hand side rule
                    for(unsigned int i = 0; i < rightSideRules.size()-1; i ++){
                        // Join each relation together
                        singleRelation = singleRelation.join(rightSideRules[i + 1]);

                    }

                    //cout << singleRelation.relationToString() << endl;

                }

                // Project Rules
                // Get columns for the project
                vector<int> ruleProjectIndices;
                for(auto & headVariable : rule.headPredicate.parameters){
                    int index = 0;

                    // Iterate through each scheme variable
                    for(auto & variable : singleRelation.getScheme()){
                        // If a match, we know an index for the project.
                        if(headVariable.name == variable){
                            ruleProjectIndices.push_back(index);

                            // If not, keep looking.
                        } else {
                            index ++;

                        }
                    }

                }

                //cout << singleRelation.relationToString() << endl;

                Relation projectedRelation = singleRelation.project(ruleProjectIndices);

                //cout << projectedRelation.relationToString() << endl;


                // Rename Rules
                vector<string> newSchemeNames;
                for(auto & scheme : datalogProgram.schemes){

                    if(rule.headPredicate.name == scheme.name){
                        for(auto & name : scheme.parameters){
                            newSchemeNames.push_back(name.printName());
                        }
                    }
                }

                projectedRelation.rename(newSchemeNames);

                //ruleRelations.push_back(projectedRelation);

                set<Tuple> newTuples;

                // Union
                // Find relation in database whose name matches the name of the head of the rule
                for(auto & relation : relations){
                    int beforeRelSize = relation.getSize();

                    // Match head rule name with relation name
                    if(rule.headPredicate.name == relation.relationNameToString()){

                        newTuples = relation.diffTuples(projectedRelation);

                        // Add the tuples from the projected relation
                        relation.doUnion(projectedRelation);

                    }

                    int afterRelSize = relation.getSize();

                    // If at least one tuple was added, changes is true
                    if(beforeRelSize != afterRelSize){

                        // If a rule has no adjacent nodes, evaluate only once.
                        if(dependencyGraph.nodes.at(index).adjacentNodeIDs.empty()){
                            changes = false;

                            // If an SCC contains only one rule and that rule does not depend on itself,
                            // evaluate only once.
                        } else if(dependencyGraph.nodes.at(index).adjacentNodeIDs.size() >= 1) {

                            // Set initially to false
                            changes = false;
                            // Check the adjacent nodes to see if the rule depends on itself
                            vector<int> possibleCycles;

                            // Iterate through each rule in the SCC
                            for(auto & ruleIndex : ruleIndices){

                                // Insert possible cycle
                                possibleCycles.push_back(ruleIndex);

                                // Iterate through each adjacent node for the node in SCC
                                for(auto & adjacentNode : dependencyGraph.nodes.at(ruleIndex).adjacentNodeIDs) {

                                    // Check if the adjacent node traces back to a previous node in SCC
                                    for(auto & possibleCycle : possibleCycles){

                                        // If it does, we have a cycle
                                        if(possibleCycle == adjacentNode){

                                            changes += 1;

                                        }
                                    }

                                }

                            }

                            for(auto & adjacentNode : dependencyGraph.nodes.at(index).adjacentNodeIDs) {
                                // If the rule does depend on itself, evaluate again. If not, it stays false
                                if(adjacentNode == index) {

                                    numChanges += 1;
                                }

                                // Check for a cycle. This only works for two adjacent nodes.
                                for(auto & backAdjNode : dependencyGraph.nodes.at(adjacentNode).adjacentNodeIDs){

                                    if(backAdjNode == index){

                                        numChanges += 1;

                                    }

                                }

                            }

                            // If an SCC has more than one rule, evaluate again
                        } else {

                            //cout << "repeat\n";
                            numChanges += 1;

                        }

                        // If any changes have been made to any of the rules, evaluate them again
                        if(numChanges != 0){
                            changes = true;
                        }

                        // Print the tuples
                        for(auto & tuple : newTuples){
                            cout << "  " <<  tuple.schemeTupleToString(projectedRelation.getScheme()) << endl;
                        }

                        // Reset for next iteration
                        ruleRelations.clear();
                    }


                }

                // Reset for next rule
                rightSideRules.clear();
            }
        }

        vector<int>::iterator ruleIt;
        cout <<  iterations << " passes: ";
        long unsigned int counter = 0;
        for(ruleIt = ruleIndices.begin(); ruleIt != ruleIndices.end(); ruleIt ++){

            counter ++;
            if(counter == ruleIndices.size()){
                cout << "R" << *ruleIt;
            } else {
                cout << "R" << *ruleIt << ",";
            }

        }
        ruleIndices.clear();
        cout << endl;
    }

    void evaluateQueries() {

        // Iterate through each query
        for(auto & query : datalogProgram.queries){
            cout << query.predToString() << "? ";

            // Iterate through each Relation
            for(auto relation : relations) {

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

                                // Add new variable to variables to be used when projecting the relation
                                variables.push_back(newVariable);

                                if(newVariable.indices.size() > 1) {

                                    // Multiple indices.
                                    relation = relation.selectMultipleIndexes(newVariable.indices);
                                }

                            }

                        }

                    }

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

                            // Iterate through each variable and do a project and collect indices of those variables
                            for(auto & variable : variables) {

                                projectIndices.push_back(variable.indices[0]);

                            }
                            Relation projectedRelation = relation.project(projectIndices);
                            cout << "Yes(" << relation.getTupleNum() << ")" << endl;
                            cout << projectedRelation.relationToString();
                            projectIndices.clear();

                        }
                    } else {
                        cout << "No" << endl;
                    }

                }

            }

            variables.clear();
        }
    }


};


#endif //UNTITLED_DATABASE_H
