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


}
