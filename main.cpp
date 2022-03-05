#include <iostream>
#include "Token.h"
#include "Scanner.h"
#include "Parser.h"
#include "Scheme.h"
#include "DatalogProgram.h"
#include "Tuple.h"
#include "Relation.h"
#include "Database.h"
#include <vector>
#include <string>

using namespace std;


int main(int argc, char** argv) {

    ifstream file(argv[1]);

    ostringstream os;
    os << file.rdbuf();
    string fileString = os.str();

    // Create Scanner object
    Scanner s = Scanner(fileString);

    // Return a vector (array) of Token objects
    vector<Token> t = s.Run();

    Parser p = Parser(t);

    // Create datalogProgram object
    DatalogProgram datalogProgram = p.Run();

    Database database = Database(datalogProgram);

    database.createDatabase();
    /*

    cout << datalogProgram.schemes[0].predToString() << endl;
    cout << datalogProgram.schemes[0].getName() << endl;
    cout << datalogProgram.schemes[0].paramToString(0) << endl;
    cout << datalogProgram.schemes[0].paramToString(1) << endl;

    // Test: get a fact from datalog
    cout << datalogProgram.facts[0].predToString() << endl;
    cout << datalogProgram.facts[0].paramToString(0) << endl;
    cout << datalogProgram.facts[0].paramToString(1) << endl;


    // Test: get a query from datalog
    cout << datalogProgram.queries[0].predToString() << endl;

     /*

    // SETUP FOR LAB 3
    /*
    vector<string> names = { "ID", "Name", "Major"};

    Scheme scheme(names);

    Relation relation("student", scheme);

    vector<string> values[] = {
            {"'42'", "'Ann'", "'CS'"},
            {"'32'", "'Bob'", "'CS'"},
            {"'64'", "'Ned'", "'EE'"},
            {"'16'", "'Jim'", "'EE'"},
    };

    // Add Tuples to relation
    for (auto& value : values) {
        Tuple tuple(value);
        cout << tuple.schemeTupleToString(scheme) << endl;
        relation.addTuple(tuple);
    }

    cout << "relation: " << endl;
    cout << relation.relationToString();

    // Example of using select
    Relation result = relation.select(2, "'CS'");

    cout << "select Major='CS' result:" << endl;
    cout << result.relationToString();
     */


    // get input file






     // SETUP FOR PROJECT 1

/*
    // get input file
    ifstream file(argv[1]);

    ostringstream os;
    os << file.rdbuf();
    string fileString = os.str();

    // Create Scanner object
    Scanner s = Scanner(fileString);

    // Return a vector (array) of Token objects
    vector<Token> t = s.Run();

    // Convert token objects to strings and print them out
    for(long unsigned int i=0; i < t.size() ; i++) {
        cout << t.at(i).toString() << endl;
    }

    cout << "Total Tokens = " << t.size() << endl;
*/

}
