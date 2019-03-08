#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <set>
#include <sstream>
#include <string>
#include <utility>
#include <unordered_map>
#include <queue>

#include "Graph.hpp"
#include "Node.hpp"

using namespace std;

/* Constructor */
Graph::Graph(void) : size(0), numEdges(0) { }

/* Destructor */
Graph::~Graph(void) {
  for (auto itr : map) {
    delete itr.second;
  }
}

/**
 * This function inserts an edge into the graph.
 *
 * Returns true if edge inserted.
 **/
void Graph::insert(int n1, int n2) {
    //if not in graph make a new Node
    Node * left = map[n1];
    if(left == nullptr) {
        left = new Node(n1);
        map[n1] = left;
        ++size;
    }
    Node * right = map[n2];
    if(right == nullptr) {
        right = new Node(n2);
        map[n2] = right;
        ++size;
    }

    //then add edges both directions
    left->addFriend(n2);
    right->addFriend(n1);

    ++numEdges;
}
 
/**
 * Read in relationships from an inputfile to create a graph.
 * Insert edges according to file contents.
 *
 * Return true if inserted properly.
 **/
bool Graph::loadFromFile(const char* in_filename) {
    ifstream infile(in_filename);
    infile.seekg(0, ios::beg);
    
    while (infile) { 
        //get each line in file
        string s; 
        if (!getline(infile, s)) break;

        //get each char in line
        istringstream ss(s);
        vector<string> record;
        while (ss) {
            string s;
            if (!getline(ss, s, ' ')) break;
            record.push_back(s);
        }
        
        if (record.size() != 2) {
            continue;
        }

        int n1 = strtol(record[0].c_str(), nullptr, 10);
        int n2 = strtol(record[1].c_str(), nullptr, 10);
        insert(n1, n2);
    }

    //if not end of file then throw error
    if(!infile.eof()) {
        cerr << "Failed to read " << in_filename << "!\n";
        return false;
    }

    //close file 
    infile.close();
    return true;
}

/**
 * This functions find the path between 2 nodes. The function uses BFS to search
 * the graph for paths. When the path is found the program saves the 
 * path. Edges are not weighted. path not found write newline only.
 *
 * Returns the path.
 **/
vector<int> Graph::getPath(Node * from, Node* to) {
    vector<int> path;
    if(from == to) {
        for(unsigned int i = 0; i < from->friends.size(); ++i) {
            if(from->name == from->friends[i]) {
                path.push_back(to->name);
            }
        }
        return path;
    }
    Node * curr = to;
    while(true){
	    path.push_back(curr->name);
        if(curr->prev == from) break;
        curr = curr->prev;
    }
    path.push_back(from->name);
    return path;
}




/**
 * This functions find a path between 2 nodes. The function uses BFS to search
 * the graph for paths. When the path is found the program exits and saves the 
 * path. Edges are not weighted. path not found write newline only.
 *
 * Returns true if path is found.
 **/
bool Graph::pathfinder(Node* from, Node* to) {
    //id not valid 
    if((from == nullptr) | (to == nullptr)) {
        return false;
    }

    //init all data in nodes
    for (auto iter = map.begin(); iter != map.end(); iter++) {
        iter->second->done = false;
        iter->second->prev = nullptr;
        iter->second->dist = -1;
    }

    //base case from equals to
    if(from == to) {
        to->prev = from;
        return true;
    }

    //create queue for BFS
    queue<Node*> queue;

    //start algorithm
    from->done = true;
    from->dist = 0;
    queue.push(from);

    //loop while queue non-empty/visited_some
    Node * curr;
    while (!queue.empty()) {
        curr = queue.front();      // get next 
        queue.pop();
        for (int n : curr->friends) {
            //set data in non-visited nodes
            if (!map[n]->done) {
                map[n]->done = true;
                map[n]->prev = curr;
                map[n]->dist = curr->dist + 1;

                //is this the elem were looking for?
                if (map[n] == to) {
                    return true; //exit early
                }
                queue.push(map[n]);
            }
        }
    }
    return false; //ids not connected
}

/**
 *  This function will take the list of invitees and they are invited
 *  to the party. Then, it finds all those who know more than k people
 *  that are already invited to the party and then they get invited.
 *
 *  Returns with the full list of invitees. 
 **/
void Graph::socialgathering(vector<string>& invitees, const int& k) {
    //init data in all nodes
    for (auto iter : map) {
        iter.second->done = false;
        iter.second->prev = nullptr; //leaves this alone
        iter.second->dist = -1;
    }

    //base case k is more than size of invitees.
    if ((int)invitees.size() < k) {
        return; //no one new can go
    }

    //create priority queue
    priority_queue<Node*, vector<Node*>, NodePtrComp> pq; 
    //queue<int> que;

    //TODO
    /*//add all invitees to pq mark done
    for (auto iter : invitees) {
        *iter->dist = k;        // dist = numPplKnown
        *iter->done = true;     // done == invited
        pq.push(*iter);
    }*/

    //empty out pq updating graph data as you pop each node
    Node * curr;
    int numKnown;
    while (!pq.empty()) { 
        curr = pq.top();      // get next 
        pq.pop();
        for (int n : curr->friends) {
            if (!map[n]->done) {
                numKnown = map[n]->dist;
                map[n]->dist = ++numKnown;
                if (numKnown == k) {
                    map[n]->done = true;
                    //TODO push map[n]->second to invitees
                    pq.push(map[n]);
                }
            }
        }
    }
}

