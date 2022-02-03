//
// Created by Ethan L. Kerr on 1/28/22.
//

#ifndef UNTITLED_PARSER_H
#define UNTITLED_PARSER_H

#include <iostream>
#include <vector>
#include "Token.h"
#include "DatalogProgram.h"
#include "Predicate.h"
#include "Rule.h"
#include <string>

using namespace std;

class Parser {
private:
    unsigned int tokenIndex = 0;
    vector<Token> tokens;
    DatalogProgram datalogProgram;

    string match(TokenType t) {
        string tokenValue = tokens.at(tokenIndex).getValue();
        cout << "match: " << tokens.at(tokenIndex).getValue() << endl;
        if (tokenType() == t){

            // If token type matches, advance token index to look at next token and return tokenValue
            tokenIndex ++ ;
            return tokenValue;

        } else { // TODO: Stop parser when an error is thrown
            // Throw an error if the token type does not match
            throwError();
            return "";
        }
    }

    void throwError() {
        cout << "Failure!\n\t" << tokens.at(tokenIndex).toString() << endl;
    }

public:
    Parser(const vector<Token>& tokens) : tokens(tokens) { }

    TokenType tokenType() const{
        return tokens.at(tokenIndex).getType();
    }

    void createDatalog() { // TODO: Create datalog, check for errors, print datalog to console
        if(tokenType() == SCHEMES) { // Schemes:
            match(SCHEMES); // Schemes
            match(COLON); // :

        }
    }

    void idList(Predicate& predicate) {
        if (tokenType() == COMMA) {
            match(COMMA);
            predicate.addParam(match(ID));
            idList(predicate);
        } else {
            // lambda
            return;
        }
    }

    void stringList(Predicate& predicate) {
        if (tokenType() == COMMA) {
            match(COMMA);
            predicate.addParam(match(STRING));
            stringList(predicate);
        } else {
            // lambda
            return;
        }
    }

    Predicate parseScheme() { // TODO: return a Predicate rather than void
        if (tokenType() == ID) {
            // The first ID will be the name of the predicate
            Predicate p(match(ID)); // snap
            match(LEFT_PAREN); // (
            p.addParam(match(ID)); // S
            idList(p); // ,N,A,P
            match(RIGHT_PAREN); // )
            return p;
        } else {
            Predicate pError("Error");
            throwError();
            return pError;
        }
    }

    Predicate parseFact() { // TODO: return a Predicate rather than void
        if (tokenType() == ID){
            Predicate p(match(ID));
            match((LEFT_PAREN));
            p.addParam(match(STRING));
            stringList(p);
            match(RIGHT_PAREN);
            match(PERIOD);
            cout << p.predToString() << endl;
            return p;
        } else {
            Predicate pError("Error");
            throwError();
            return pError;
        }
    }

    Predicate parseQuery() { // TODO: check for predicate. Not sure what to do for this quite yet.
        // Check if predicate starts with valid ID
        if(tokenType() == ID){
            // Check if it's a valid predicate
            Predicate p = createPredicate();
            match(Q_MARK);
            return p;
        } else {
            Predicate pError("Error");
            return pError;
        }
    }

    Predicate createPredicate() {
        if (tokenType() == ID){
            Predicate p(match(ID));
            match(LEFT_PAREN);

            // Parameter can have an ID or STRING
            if (tokenType() == ID){
                p.addParam(match(ID));
            } else if (tokenType() == STRING){
                p.addParam(match(STRING));
            }

            // Add more parameters
            paramList(p);
            match(RIGHT_PAREN);

            // Return Predicate
            return p;
        } else {

            // Won't reach this... I don't think...
            Predicate pError("error");
            return pError;
        }
    }

    void predicateList(Rule& rule) {
        if (tokenType() == COMMA){
            match(COMMA);
            Predicate p = createPredicate();
            rule.addPredicate(p);
            predicateList(rule);
        } else {
            return;
        }
    }

    Rule parseRule() {
        if(tokenType() == ID){
            Predicate headP = createPredicate();
            cout << headP.predToString() << endl;
            Rule r(headP); // headPredicate
            match(COLON_DASH); // :-
            Predicate p = createPredicate();
            r.addPredicate(p);
            predicateList(r);
            match(PERIOD);
            cout << r.ruleToString() << endl;
            return r;
        } else {
            Predicate pError("Error");
            Rule rError(pError);
            return rError;
        }
    }

    void paramList(Predicate& p) {
        if (tokenType() == COMMA) {
            match(COMMA);
            if (tokenType() == ID){
                p.addParam(match(ID));
            } else if (tokenType() == STRING){
                p.addParam(match(STRING));
            }
            paramList(p);
        } else {
            // Lambda
            return;
        }
    }



/*
    void ruleList() {
        if (tokenType() == COMMA){
            match(COMMA);

        }
    }

    void rule() {
        if (tokenType() == ID){
            match(ID);
            match(LEFT_PAREN);
            match(ID);
            idList();
            match(RIGHT_PAREN);
            match(COLON_DASH);


        }
    }
*/

};



#endif //UNTITLED_PARSER_H
