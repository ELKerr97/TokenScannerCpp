//
// Created by Ethan L. Kerr on 1/31/22.
//

#ifndef UNTITLED_DATALOGPROGRAM_H
#define UNTITLED_DATALOGPROGRAM_H

#include "Predicate.h"
#include "Rule.h"
#include <vector>
#include <string>

using namespace std;

class DatalogProgram {

private:
    // vector of predicates called schemes
    // vector of predicates called facts
    // vector of rules called rules
    // vector of predicates called queries
    // toString function that prints them all out

public:
    // Vectors
    vector<Predicate> schemes;
    vector<Predicate> facts;
    vector<Rule> rules;
    vector<Predicate> queries;
    vector<string> domains;

    // Methods
    DatalogProgram() {}

    string printDatalog() {
        string datalog;

        datalog += "Success!\n";

        // Print out schemes
        datalog += ("Schemes(" + to_string(schemes.size()) + "):\n");
        for(int i = 0; i < schemes.size() ; i ++ ){
            datalog += "\t" + schemes[i].predToString() + "\n";
        }

        // Print out facts
        datalog += ("Facts(" + to_string(facts.size()) + "):\n");
        for(int i = 0; i < facts.size() ; i ++ ){
            datalog += "\t" + facts[i].predToString() + "\n";
        }

        // Print out rules
        datalog += ("Rules(" + to_string(rules.size()) + "):\n");
        for(int i = 0; i < rules.size() ; i ++ ){
            datalog += "\t" + rules[i].ruleToString() + "\n";
        }

        // Print out queries
        datalog += ("Queries(" + to_string(queries.size()) + "):\n");
        for(int i = 0; i < queries.size() ; i ++ ){
            datalog += "\t" + queries[i].predToString() + "?\n";
        }

        // Print out domains
        datalog += ("Domain(" + to_string(domains.size()) + "):\n");
        for(int i = 0; i < domains.size() ; i ++ ){
            if(i < domains.size() - 1){
                datalog += "\t" + domains[i] + "\n";
            } else {
                datalog += "\t" + domains[i];
            }

        }

        return datalog;
    }


    // TODO : add schemes, facts, rules and queries to the vectors in datalog
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
        domains.push_back(domain);
    }
};


#endif //UNTITLED_DATALOGPROGRAM_H
