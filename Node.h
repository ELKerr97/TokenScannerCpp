//
// Created by Ethan L. Kerr on 3/28/22.
//

#ifndef UNTITLED_NODE_H
#define UNTITLED_NODE_H
#include <string>
#include <vector>
#include <set>
#include <iostream>

using namespace std;

class Node {

private:

public:
    set<int> adjacentNodeIDs;
    bool visited;

    /**
     * Add an edge from current node to an adjacent node
     * @param adjacentNodeID
     */
    void addEdge(int adjacentNodeID) {
        adjacentNodeIDs.insert(adjacentNodeID);
    }

    /**
     * Print the adjacent Node ID's
     */
    string toString() {
        stringstream printedNodes;
        int count = 0;
        for(auto& nodeID : adjacentNodeIDs){
            count ++;

            printedNodes << "R" << nodeID;

            // Print comma if not at the end of the set
            if(count != adjacentNodeIDs.size()){

                printedNodes << ",";

            }

        }

        return printedNodes.str();
    }



};


#endif //UNTITLED_NODE_H
