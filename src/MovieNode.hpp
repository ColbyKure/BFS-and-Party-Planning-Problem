/**
 * Assignment:
 * Filename:
 * Name:
 * Date:
 * Description:
 **/

#ifndef ACTORNODE_HPP
#define ACTORNODE_HPP

#include <iostream>

using namespace std;

class ActorNode {
public:
    string actor_name;
    vector<ActorNode*> edges;
    vector<string> movie_names;
    vector<int> years;
    Node * prev;

    /* Constructor for Node */
    ActorNode(string name) {
        actor_name = name;
        edges 
    }
}
