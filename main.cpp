#include <iostream>
#include "Token.h"
#include "Scanner.h"
#include "Parser.h"
#include "Scheme.h"
#include "DatalogProgram.h"
#include "Tuple.h"
#include "Relation.h"
#include "Database.h"
#include "Node.h"
#include <vector>
#include <string>

using namespace std;


int main(int argc, char** argv) {

    ifstream file(argv[1]);

    ostringstream os;
    os << file.rdbuf();
    string fileString = os.str();

    // Lab 5
    Node node;
    node.addEdge(4);
    node.addEdge(8);
    node.addEdge(2);
    cout << node.toString() << endl;

}
