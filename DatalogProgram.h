//
// Created by Ethan L. Kerr on 1/31/22.
//

#ifndef UNTITLED_DATALOGPROGRAM_H
#define UNTITLED_DATALOGPROGRAM_H

#include "Predicate.h"
#include "Rule.h"
#include <vector>
#include <string>
#include <set>


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
    set<string> domains;


    // Methods
    DatalogProgram() {}

    string printDatalog() {
        string datalog;

        datalog += "Success!\n";
        datalog +=printSchemes();
        datalog +=printFacts();
        datalog +=printRules();
        datalog +=printQueries();
        datalog += printDomains();

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
