#include <iostream>
#include "Token.h"
#include "Scanner.h"
#include "Parser.h"
#include <vector>


int main(int argc, char** argv) {

    // SETUP FOR LAB 2

    // get input file
    ifstream file(argv[1]);

    ostringstream os;
    os << file.rdbuf();
    string fileString = os.str();

    // Create Scanner object
    Scanner s = Scanner(fileString);

    // Return a vector (array) of Token objects
    vector<Token> t = s.Run();

    vector<Token> tokens = {
            Token(ID,"Ned",2),
            Token(LEFT_PAREN,"(",2),
            Token(STRING,"\'Ted\'",2),
            Token(COMMA,",",2),
            Token(STRING,"\'Zed\'",2),
            Token(COMMA,",",2),
            Token(STRING,"\'Zed\'",2),
            Token(COMMA,",",2),
            Token(STRING,"\'Zed\'",2),
            Token(RIGHT_PAREN,")",2),
    };

    Parser p = Parser(t);
    p.Run();


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
