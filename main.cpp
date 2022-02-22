#include <iostream>
#include "Token.h"
#include "Scanner.h"
#include "Parser.h"
#include "Scheme.h"
#include "Tuple.h"
#include "Relation.h"
#include <vector>


int main(int argc, char** argv) {

    // SETUP FOR LAB 3

    vector<string> names = { "ID", "Name", "Major"};

    Scheme scheme(names);

    Relation relation("student", scheme);

    vector<string> values[] = {
            {"'42'", "'Ann'", "'CS'"},
            {"'32'", "'Bob'", "'CS'"},
            {"'64'", "'Ned'", "'EE'"},
            {"'16'", "'Jim'", "'EE'"},
    };

    for (auto& value : values) {
        Tuple tuple(value);
        cout << tuple.schemeTupleToString(scheme) << endl;
        relation.addTuple(tuple);
    }

    cout << "relation: " << endl;
    cout << relation.relationToString();

    Relation result = relation.select(2, "'CS'");

    cout << "select Major='CS' result:" << endl;
    cout << result.relationToString();


    // get input file

    /*
    ifstream file(argv[1]);

    ostringstream os;
    os << file.rdbuf();
    string fileString = os.str();

    // Create Scanner object
    Scanner s = Scanner(fileString);

    // Return a vector (array) of Token objects
    vector<Token> t = s.Run();

    Parser p = Parser(t);
    p.Run();
    */


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
