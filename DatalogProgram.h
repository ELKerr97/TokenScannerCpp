//
// Created by Ethan L. Kerr on 1/31/22.
//

#ifndef UNTITLED_DATALOGPROGRAM_H
#define UNTITLED_DATALOGPROGRAM_H

#include "Predicate.h"
#include "Rule.h"
#include "Graph.h"
#include "Node.h"
#include <vector>
#include <string>
#include <set>
#include <stack>
#include <bits/stdc++.h>

using namespace std;

class DatalogProgram {

private:
    //Graph dependencyGraph = Graph(0);
    //Graph reverseGraph = Graph(0);

public:
    set<int> scc; // Strongly Connected Components
    vector<int> forestNodes; // Nodes set in reverse post-order
    vector<Predicate> schemes;
    vector<Predicate> facts;
    vector<Rule> rules;
    vector<Predicate> queries;
    set<string> domains;

    // Methods
    DatalogProgram() {}

    /**
     * Creates a reverse graph, gets all the nodes in order, finds SCC's and evaluated rules in order.
     */
     /*
    void run() {

        // Make a reverse dependency graph from the rules
        reverseGraph = makeReverseGraph(rules);

        // Put all the nodes in the correct order
        for(int i = 0; i < rules.size(); i ++){

            // Iterate through each node and do a depth-first search. ***Initially in reverse post-order
            // (highest number will be at the beginning)
            dfsForest(i);
        }

        dependencyGraph = makeGraph(rules);

        set<int>::reverse_iterator rit;

        // Print Dependency Graph
        cout << "Dependency Graph\n" << dependencyGraph.toString() << endl;

        // Print Rule Evaluation
        cout << "Rule Evaluation" << endl;

        // Run dfs on the original dependency graph, starting with the node with the highest post-order number.
        for(rit = forestNodes.rbegin(); rit != forestNodes.crend(); rit ++) {

            cout << "SCC: R" << *rit << endl;
            // Reset the SCC's after each iteration
            scc.clear();

            // depth-first search
            dfs(*rit);

            // Evaluate rules in SCC's in numerical order (should be in order because they're in a set)
            vector<Rule> rulesInSCC;

            set<int>::reverse_iterator itr; // Using reverse iterator to make sure rules are evaluated in right order
             // Put rules in SCC into a set
            for(itr = scc.rbegin(); itr != scc.rend(); itr++){

                rulesInSCC.push_back(rules.at(*itr));

            }

            // Clear the rules
            rulesInSCC.clear();
        }

    }
      */

    /**
     * Depth-First Search will identify Strongly Connected Components and add them to scc to be evaluated after all
     * returns are finished.
     * @param nodeX
     * @param graph
     */
    void dfs(unsigned int nodeX, Graph& dependencyGraph){

        // Mark this node as visited and add it to SCC's if it hasn't been visited
        if (!dependencyGraph.nodes[nodeX].visited) {
            scc.insert(nodeX);
            dependencyGraph.nodes[nodeX].visited = true;
        }

        // iterate through each adjacent node
        for(auto & nodeY : dependencyGraph.nodes[nodeX].adjacentNodeIDs){
            // Check if that node has been visited
            if(!dependencyGraph.nodes[nodeY].visited && !dependencyGraph.nodes[nodeY].adjacentNodeIDs.empty()) {
                // If not visited, add it as an SCC and run dfs on that node
                scc.insert(nodeY);
                dfs(nodeY, dependencyGraph);

            }
        }
    }

    /**
     * Finds the reverse-post-order for the nodes and stores it in forestNodes
     * @param nodeX
     * @param graph
     */
    void dfsForest(int nodeX, Graph& reverseGraph) {

        // Mark this node as visited
        reverseGraph.nodes[nodeX].visited = true;


        // iterate through each adjacent node
        for(auto & nodeY : reverseGraph.nodes[nodeX].adjacentNodeIDs){

            // Check if that node has been visited
            if(!reverseGraph.nodes[nodeY].visited) {

                // If not visited, run dfs on that node

                dfsForest(nodeY, reverseGraph);

            }

        }

            // Check if node has been inserted yet
        bool insert = true;
        for(auto & nodeNum : forestNodes){
            if(nodeNum == nodeX){
                insert = false;
            }
        }
        if(insert){
            forestNodes.push_back(nodeX);
        }
        // On return, add the node. This will be in reverse post-order.


/*
        // TEST: Print statements to ensure correct order
        for(auto & id : forestNodes) {

            cout << id << ",";

        }
        cout << "\n";
*/

    }

    static Graph makeReverseGraph(const vector<Rule>& rules){

        // Make a graph of rules (rules are the nodes)
        Graph graph(rules.size());

        // Loop over the rules and find the dependencies. 'fromID' maps the correct node index in graph.
        for (unsigned fromID = 0; fromID < rules.size(); fromID++) {
            Rule fromRule = rules.at(fromID);

            // Use backspace to get rid of period at the end
            //cout << "from rule R" << fromID << ": " << fromRule.ruleToString() << "\b \b" << endl;

            // Loop over the predicates of the body of the current rule
            for (unsigned pred = 0; pred < fromRule.predicateList.size(); pred++) {
                // Body rule
                Predicate bodyPred = fromRule.predicateList[pred];
                //cout << "from body predicate: " << bodyPred.predToString() << endl;


                for (unsigned toID = 0; toID < rules.size(); toID++) {
                    Rule toRule = rules.at(toID);
                    //cout << "to rule R" << toID << ": " << toRule.ruleToString() << endl;

                    // If the name of a rule in the body matches the name of the head rule, they are a match.
                    // **Head rule will be dependent on the body rule
                    if(toRule.headPredicate.name == bodyPred.name){
                        //cout << "dependency found: (R" << fromID << ",R" << toID << ")" << endl;

                        // Add an edge from the head rule to the body rule
                        graph.nodes[toID].addEdge(fromID);
                    }
                }
            }
        }

        return graph;

    }

    static Graph makeGraph(const vector<Rule>& rules){

        // Make a graph of rules (rules are the nodes)
        Graph graph(rules.size());

        // Loop over the rules and find the dependencies. 'fromID' maps the correct node index in graph.
        for (unsigned fromID = 0; fromID < rules.size(); fromID++) {
            Rule fromRule = rules.at(fromID);

            // Loop over the predicates of the body of the current rule
            for (unsigned pred = 0; pred < fromRule.predicateList.size(); pred++) {
                // Body rule
                Predicate bodyPred = fromRule.predicateList[pred];

                for (unsigned toID = 0; toID < rules.size(); toID++) {
                    Rule toRule = rules.at(toID);

                    // If the name of a rule in the body matches the name of the head rule, they are a match.
                    // **Head rule will be dependent on the body rule
                    if(toRule.headPredicate.name == bodyPred.name){

                        // Add an edge from the head rule to the body rule
                        graph.nodes[fromID].addEdge(toID);
                    }
                }
            }
        }

        return graph;

    }

    string printDatalog() {
        string datalog;

        datalog += "Success!\n";
        datalog += printSchemes();
        datalog += printFacts();
        datalog += printRules();
        datalog += printQueries();
        datalog += printDomains();

        return datalog;
    }

    void addScheme(const Predicate& scheme){
        schemes.push_back(scheme);
    }

    void addFact(const Predicate& fact){
        facts.push_back(fact);
    }

    void addRule(const Rule& rule) {
        rules.push_back(rule);
    }

    void addQuery(Predicate& query){
        queries.push_back(query);
    }

    void addDomain(const string& domain){
        domains.insert(domain);
    }

    string printQueries() {
        string datalog = ("Queries(" + to_string(queries.size()) + "):\n");
        for(long unsigned int i = 0; i < queries.size() ; i ++ ){
            datalog += "  " + queries[i].predToString() + "?\n";
        }
        return datalog;
    }

    string printSchemes() {
        // Print out schemes
        string datalog = ("Schemes(" + to_string(schemes.size()) + "):\n");
        for(long unsigned int i = 0; i < schemes.size() ; i ++ ){
            datalog += "  " + schemes[i].predToString() + "\n";
        }
        return datalog;
    }

    string printFacts() {
        // Print out facts
        string datalog = ("Facts(" + to_string(facts.size()) + "):\n");
        for(long unsigned int i = 0; i < facts.size() ; i ++ ){
            datalog += "  " + facts[i].predToString() + ".\n";
        }
        return datalog;
    }

    string printRules() {
        // Print out rules
        string datalog = ("Rules(" + to_string(rules.size()) + "):\n");
        for(long unsigned int i = 0; i < rules.size() ; i ++ ){
            datalog += "  " + rules[i].ruleToString() + "\n";
        }
        return datalog;
    }

    string printDomains() {

        set<string>::iterator itr;

        // Print out domains // TODO: learn how to iterate over set lol
        string datalog = ("Domain(" + to_string(domains.size()) + "):\n");
        for(itr = domains.begin(); itr != domains.end() ; itr ++ ){
            datalog += "  " + *itr + "\n";

        }
        return datalog;
    }
};


#endif //UNTITLED_DATALOGPROGRAM_H
