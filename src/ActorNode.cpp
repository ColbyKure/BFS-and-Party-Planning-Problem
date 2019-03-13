/**
 * Assignment:PA3, part 3, Prim's Algorithm
 * Filename: ActorNode.hpp
 * Name: Colby Kure, Sunny Sun
 * Date: 3/11/19
 * Description: This file holds node class 
 **/

#include <iostream>
#include <vector>

#include "ActorNode.hpp"

using namespace std;

/* Constructor for Node */
ActorNode::ActorNode(string actor) : prev(0) {
    name = actor;
    minWeight = 0;
    done = false;
}

/* Destructor */
ActorNode::~ActorNode() { } //default
