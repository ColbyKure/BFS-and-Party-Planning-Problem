#ifndef NODE_HPP
#define NODE_HPP

#include <iostream>

using namespace std;

class Node {

private: 
    bool done;              // visited node
    int name;               // id number for person
    int dist;               // dist from start
    Node * prev;            // prev node in path
    vector<int> friends;    // edges of graph

    /*   Getter for dist.  */
    int getDist(void) { return dist; }

    /*   Getter for prev.  */
    Node * getPrev(void) { return prev; }

    /*   Getter for done.  */
    bool isDone(void) { return done; }

public:

    /* Constructor for Node. */
    Node(void) : done(false), dist(-1), prev(0) { }

    /* Destructor for Node. */
    ~Node(void) { }

    /* Setter for friends */
    void setFriends(const vector<int> & newFriends) {
        for(unsigned int i = 0; i < newFriends.size(); ++i) {
            friends.push_back(newFriends[i]);
        }
    }

    /* Setter for friends */
    void setFriends(const int & newFriends) {
        friends.push_back(newFriends);
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
        cout << "(name, done, dist, prev) == (" << name << ", " << done << ", " << dist << ", " << prev << ")\n";
        cout << "printing " << num << "/" << friends.size() << " many friends\n";
        for(unsigned int i = 0; (i < friends.size() | i < num); ++i) {
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
