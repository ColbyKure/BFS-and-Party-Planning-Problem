#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <unordered_map>

#include "Node.hpp"

using namespace std;

/**
 *  A function class for the use as the compare class in the priority queue.
 */
class NodePtrComp {
public:
    bool operator()(Node *& n1, Node *& n2) const {
        return *n1 < *n2;
    }
};

class Graph {
 protected:
    /* protected nember variables */

 public:
    /* public member variables */
    unordered_map<int, Node*> map;  // map of all nodes
    int size;                       // number of nodes
    int numEdges;

    Graph(void);

    ~Graph(void);

    void insert(int n1, int n2);

    bool loadFromFile(const char* in_filename);
    
    vector<int> getPath(Node* to);

    bool pathfinder(Node* from, Node* to);
    
    void socialgathering(vector<string>& invitees, const int& k);

};

#endif  // GRAPH_HPP
