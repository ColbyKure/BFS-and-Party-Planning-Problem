/**
 * Assignment:PA3, part 3, Prim's Algorithm
 * Filename: ActorNode.hpp
 * Name: Colby Kure, Sunny Sun
 * Date: 3/11/19
 * Description: This file holds node class 
 **/

#ifndef ACTORNODE_HPP
#define ACTORNODE_HPP

#include <iostream>

using namespace std;

class ActorNode {
public:
    string actor_name;
    vector<ActorNode*> edges;
    vector<string> movieNames;
    vector<int> years;
    ActorNode * prev;

    /* Constructor for Node */
    ActorNode(string name) : prev(0) {
        actor_name = name;
    }

    /* Destructor */
    ~ActorNode() { //default }
};

#endif
