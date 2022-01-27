#include <iostream>
#include "Token.h"
#include "Scanner.h"

int main(int argc, char** argv) {

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

}
