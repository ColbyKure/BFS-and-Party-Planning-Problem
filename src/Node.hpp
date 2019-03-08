/**
 * Assignment Name: PA 3
 * Filename: Node.hpp 
 * Name: Sunny Sun & Colby Kure
 * Date: 03/07/2019
 * Description: This file contains methods we need when we need to create 
 *		nodes for the graph or delete nodes.
 **/
#include <cstdlib>
#ifndef NODE_HPP
#define NODE_HPP

#include <iostream>

using namespace std;

class Node {
public:
    bool done;              // visited node
    int name;               // id number for person
    int dist;               // dist from start
    Node * prev;            // prev node in path
    vector<int> friends;    // edges of graph

    /* Constructor for Node. */
    Node(int id) : done(false), dist(-1), prev(0) {
        name = id;
    }

    /* Destructor for Node. */
    ~Node(void) { }

    /* Setter for friends */
    void addFriend(const int & newFriend) {
        friends.push_back(newFriend);
    }

    /* Prints Node Data to out */
    void print(void) {
        cout << endl << "name = " << name << endl;
        cout << "done = ";
        if(done) { cout << "true\n"; }
        else { cout << "falsn\n"; }
        cout << "dist = " << dist << endl;
        cout << "prev = " << prev << endl;
        cout << name << " has " << friends.size() << "friends\n";
        for(unsigned int i = 0; i < friends.size(); ++i) {
            cout << "\t" << i << ": " << friends[i] << endl;
        }
        cout << "Finished printing " << name << endl;
    }

    /* Prints Node Data to out num friends (short version)*/
    void peek(const unsigned int & num) {
        cout << "(name, done, dist, prev) == (" << name << ", " << done 
	     << ", " << dist << ", " << prev << ")\n";
        cout << "printing " << num << "/" << friends.size() 
	     << " many friends\n";
        for(unsigned int i = 0; ((i < friends.size()) | (i < num)); ++i) {
            cout << "(" << i << ": " << friends[i] << ") ";
            if(i % 4 == 0) { cout << endl; }
        }
        cout << "Finished printing " << name << endl;
    }

    /** 
     *  Overload LESS-THAN operator
     *
     *  Less-than compares Node in the priority queue by the id number of that
     *  person. Lower id nodes have higher priorty.
     */
    bool operator<(const Node& other) {
        return name > other.name;
    }
};

#endif  // NODE_HPP
