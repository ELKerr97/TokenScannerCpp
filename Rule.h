//
// Created by Ethan L. Kerr on 1/31/22.
//

#ifndef UNTITLED_RULE_H
#define UNTITLED_RULE_H

#include <string>
#include "Predicate.h"
#include <vector>

using namespace std;

class Rule {

private:

public:
    // headPredicate COLON_DASH predicate predicateList PERIOD
    Predicate headPredicate;
    vector<Predicate> predicateList;
    Rule(Predicate &headPredicate) : headPredicate(headPredicate) {}

    void addPredicate(const Predicate& predicate){
        predicateList.push_back(predicate);
    }

    string ruleToString() {
        string ruleString;
        ruleString += (headPredicate.predToString() + " :- ");
        for(int i = 0; i < predicateList.size() ; i++){
            if (i != predicateList.size() - 1){
                ruleString += predicateList[i].predToString() + ",";
            } else {
                ruleString += predicateList[i].predToString() + ".";
            }
        }
        return ruleString;
    }


};


#endif //UNTITLED_RULE_H
