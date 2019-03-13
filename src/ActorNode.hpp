#ifndef ACTORNODE_HPP
#define ACTORNODE_HPP
/**
 * Assignment:PA3, part 3, Prim's Algorithm
 * Filename: ActorNode.hpp
 * Name: Colby Kure, Sunny Sun
 * Date: 3/11/19
 * Description: This file holds node class 
 **/

#include <iostream>
#include <vector>

using namespace std;

class ActorNode {
public:
    string name;
    vector<string> edges;
    bool done;
    ActorNode * prev;
    int minWeight;
    //vector<ActorNode*> edges;
    //vector<string> movieNames;
    //vector<int> years;

    /* Constructor for Node */
    ActorNode(string actor);
    /*: prev(0) {
        actor_name = name;
        minWeight = 0;
        done = false;
    }*/

    /* Destructor */
    ~ActorNode(); 
    //{ } //default
};

#endif
