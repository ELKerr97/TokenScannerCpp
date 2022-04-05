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
#include "Graph.h"
#include "Rule.h"
#include <vector>
#include <string>

using namespace std;


int main(int argc, char** argv) {

    ifstream file(argv[1]);

    ostringstream os;
    os << file.rdbuf();
    string fileString = os.str();


    /*
    vector<Rule> rules;

    for (auto& rulePair : ruleNames) {
        string headName = rulePair.first;
        Predicate headPredicate = Predicate(headName);
        Rule rule = Rule(headPredicate);
        vector<string> bodyNames = rulePair.second;
        for (auto& bodyName : bodyNames)
            rule.addPredicate(Predicate(bodyName));
        rules.push_back(rule);
    }
     */

    // Create Scanner object
    Scanner s = Scanner(fileString);

    // Return a vector (array) of Token objects
    vector<Token> t = s.Run();

    Parser p = Parser(t);

    // Create datalogProgram object
    DatalogProgram datalogProgram = p.Run();

    //Database database = Database(datalogProgram);

    //database.createDatabase();
    Graph graph = datalogProgram.makeGraph(datalogProgram.rules);
    Graph reverseGraph = datalogProgram.makeReverseGraph(datalogProgram.rules);

    // Start at the first node
    // datalogProgram.dfs(0, reverseGraph);
    // datalogProgram.dfs(2, reverseGraph);

    datalogProgram.run();


    //cout << "Reverse Graph: \n" << reverseGraph.toString();


}
