//
// Created by Ethan L. Kerr on 3/28/22.
//

#ifndef UNTITLED_GRAPH_H
#define UNTITLED_GRAPH_H
#include <string>
#include <vector>
#include <set>
#include <iostream>
#include <sstream>
#include "Node.h"
#include "map"

using namespace std;


class Graph {

private:



public:

    map<int,Node> nodes;

    /**
     * Make a graph of nodes (rules) whose ID corresponds to the order of the rules
     * @param size
     */
    Graph(int size) {

        for (int nodeID = 0; nodeID < size; nodeID++) {
            nodes[nodeID] = Node();

        }

    }

    void addEdge(int fromNodeID, int toNodeID) {
        nodes[fromNodeID].addEdge(toNodeID);
    }

    /**
     * Prints each Node in the Graph on a separate line
     * @return
     */
    string toString() {
        stringstream graph;
        for(long unsigned int i = 0; i < nodes.size() ; i ++){

            graph << "R" << i << ":" << nodes[i].toString() << endl;

        }

        return graph.str();
    }

};


#endif //UNTITLED_GRAPH_H
