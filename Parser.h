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
    bool printDatalogProgram = true;

    string match(TokenType t) {
        string tokenValue = tokens.at(tokenIndex).getValue();
        // cout << "match: " << tokens.at(tokenIndex).getValue() << endl;
        if (tokenType() == t){

            // If token type matches, advance token index to look at next token and return tokenValue
            if (tokenIndex < tokens.size() - 1){
                tokenIndex ++ ;
            }
            return tokenValue;

        } else {
            // Throw an error if the token type does not match
            printDatalogProgram = false;
            return "";
        }
    }

    string throwError() {
        string errorThrown = "Failure!\n  " + tokens.at(tokenIndex).toString();
        return errorThrown;
    }

public:
    Parser(const vector<Token>& tokens) : tokens(tokens) { }

    TokenType tokenType() const{
        return tokens.at(tokenIndex).getType();
    }

    void Run() {
        // Create datalog structure
        createDatalog();
        // If no errors, print Datalog Program
        if(printDatalogProgram) {

            // Print the datalog data structure
            cout << datalogProgram.printDatalog() << endl;
        } else {
            // If there is an error, print only that to the console
            cout << throwError() << endl;
        }
    }

    void createDatalog() { // TODO: Throw error for empty lists
        if (tokenType() == SCHEMES) { // Schemes:

            match(SCHEMES); // Schemes
            match(COLON); // :
            if(!printDatalogProgram){return;}

            // Check for empty Scheme
            if(tokenType() == FACTS){
                throwError();
                printDatalogProgram = false;
                return;
            }

            // Add Schemes
            while (tokens.at(tokenIndex).getType() != FACTS) {
                Predicate scheme = parseScheme();
                if(!printDatalogProgram){return;}
                datalogProgram.addScheme(scheme);
            }

            match(FACTS);
            match(COLON);
            if(!printDatalogProgram){return;}


            // Add Facts
            while (tokens.at(tokenIndex).getType() != RULES) {
                Predicate fact = parseFact();
                if(!printDatalogProgram){return;}
                datalogProgram.addFact(fact);
            }

            match(RULES);
            match(COLON);
            if(!printDatalogProgram){return;}

            // Add Rules
            while (tokens.at(tokenIndex).getType() != QUERIES) {
                Rule rule = parseRule();
                if(!printDatalogProgram){return;}
                datalogProgram.addRule(rule);
            }

            match(QUERIES);
            match(COLON);
            if(!printDatalogProgram){return;}

            // Check for empty Query
            if(tokenType() == EOF_TYPE){
                throwError();
                printDatalogProgram = false;
                return;
            }

            // Add Queries
            while (tokens.at(tokenIndex).getType() != EOF_TYPE) {
                Predicate query = parseQuery();
                if(!printDatalogProgram){return;}
                datalogProgram.addQuery(query);

            }

            match(EOF_TYPE);

            // Handle extra tokens at the end of file
            if (!tokens.empty()){
                match(EOF_TYPE);
            }

        } else {
            printDatalogProgram = false;
            return;
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
            datalogProgram.addDomain(tokens.at(tokenIndex - 1).getValue());
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
            if(!printDatalogProgram){return p;}
            idList(p); // ,N,A,P
            match(RIGHT_PAREN); // )
            return p;
        } else {
            Predicate pError("Scheme Error");
            printDatalogProgram = false;
            throwError();
            return pError;
        }
    }

    Predicate parseFact() {
        if (tokenType() == ID){
            Predicate p(match(ID));
            match((LEFT_PAREN));
            p.addParam(match(STRING));
            if(!printDatalogProgram){return p;}
            datalogProgram.addDomain(tokens.at(tokenIndex - 1).getValue());
            stringList(p);
            match(RIGHT_PAREN);
            match(PERIOD);
            return p;
        } else {
            Predicate pError("Fact Error");
            printDatalogProgram = false;
            throwError();
            return pError;
        }
    }

    Predicate parseQuery() {
        // Check if predicate starts with valid ID
        if(tokenType() == ID){
            // Check if it's a valid predicate
            Predicate p = createPredicate();
            match(Q_MARK);
            return p;
        } else {
            Predicate pError("Query Error");
            printDatalogProgram = false;
            throwError();
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
            } else {
                // If empty params list, will throw an error due to the )
                match(ID);
                return p;
            }

            // Add more parameters
            paramList(p);
            match(RIGHT_PAREN);

            // Return Predicate
            return p;
        } else {
            // Won't reach this... I don't think...
            Predicate pError("Predicate Error");
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
            Rule r(headP); // headPredicate
            match(COLON_DASH); // :-
            if(!printDatalogProgram){return r;}
            Predicate p = createPredicate();
            r.addPredicate(p);
            predicateList(r);
            match(PERIOD);
            return r;
        } else {
            Predicate pError("Rule Error");
            Rule rError(pError);
            printDatalogProgram = false;
            throwError();
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
                //datalogProgram.addDomain(tokens.at(tokenIndex - 1).getValue());
            }
            paramList(p);
        } else {
            // Lambda
            return;
        }
    }


};



#endif //UNTITLED_PARSER_H
