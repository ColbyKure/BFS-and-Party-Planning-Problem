/**
 * Assignment Name: PA 3
 * Filename: Graph.cpp 
 * Name: Sunny Sun & Colby Kure
 * Date: 03/07/2019
 * Description: This file contains methods in which we try to find the path
 * 		between two nodes and bool of whether there exists a path
 *		between the two nodes. We also load from file and create the
 *		graph in this file.
 **/
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
 * Function Name: insert(int n1, int n2)
 * Description: This function inserts an edge into the graph.
 * Parameter: two integers representing the name of the nodes
 * Returns: void
 **/
void Graph::insert(int n1, int n2) {
    //find n1 else add new Node
    auto node1 = map.find(n1);
    if(node1 == map.end()) {
        map[n1] = new Node(n1);
        ++size;
    }

    //find n2 else add new Node
    auto node2 = map.find(n2);
    if(node2 == map.end()) {
        map[n2] = new Node(n2);
        ++size;
    }

    //then add edges both directions
    map[n1]->addFriend(n2);
    map[n2]->addFriend(n1);

    ++numEdges;
}
 
/**
 * Function Name: loadFromFile(const char* in_filename)
 * Description: Read in relationships from an inputfile to create a graph.
 *		Insert edges according to file contents.
 * Parameter: char pointer of filepath
 * Returns: boolean
 * 	    true if inserted properly.
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
 * Function Name: getPath(Node * from, Node* to) 
 * Description: This functions find the path between 2 nodes. The function 
 * 		uses BFS to search the graph for paths. When the path is 
 * 		found the program saves the path. Edges are not weighted. 
 * 		Path not found write newline only.
 * Parameter:  two node objects 
 * Returns: Vector<int>: the path going from one node to the other
 **/
vector<int> Graph::getPath(Node * from, Node * to) {
    vector<int> path;
    if(from == to) {
        for(unsigned int i = 0; i < from->friends.size(); i++) {
            if(from->friends[i] == to->name) {
                path.push_back(to->name);
            }
        }
        path.push_back(to->name);
        return path;
    }
    Node * curr = to;
    path.push_back(curr->name);
    while(true){
        curr = curr->prev;
        if(curr->dist == 0) break;
	    path.push_back(curr->name);
    }
    path.push_back(from->name);
    return path;
}


/**
 * Function Name: pathfinder(Node* from, Node* to)
 * Description: This function finds if there is a path between 2 nodes. 
 *		The function uses BFS to search the graph for paths.
 * Parameter: two node objects 
 * Returns: boolean True if there is a path
 *		    False if there is no path
 **/
bool Graph::pathfinder(int from, int to) {
    //id not valid 
    Node * left;
    Node * right;
    if(map.find(from) == map.end()) {
        left = nullptr;
    }
    else {
        left = map[from];
    }
    if(map.find(to) == map.end()) {
        right = nullptr;
    }
    else {
        right = map[to];
    }

    if((left == nullptr) | (right == nullptr)) {
        return false;
    }
    if(left == right) {
        return true;
    }

    //init all data in nodes
    //for(unordered_map<int,Node*>::iterator iter = map.begin(); iter != map.end(); iter++) {
    for(auto iter : map) {
        iter.second->done = false;
        iter.second->prev = nullptr;
        iter.second->dist = -1;
    }

    //create queue for BFS
    queue<Node*> queue;

    //start algorithm
    left->done = true;
    left->dist = 0;
    queue.push(left);

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
                if(map[n] == right) {
                    return true; //exit early
                }
                queue.push(map[n]);
            }
        }
    }
    return false; //ids not connected
}

/**
 * Function Name: socialgathering(vector<string>& invitees, const int& k) 
 * Description: This function will take the list of invitees and they are 
 * 		invited to the party. Then, it finds all those who know more 
 *		than k people that are already invited to the party and then
 *		they get invited.
 * Parameter: Vector<string> = people who got invited
 *	      int k = number of people
 * Returns: void & makes full list of invitees.
 **/
void Graph::socialgathering(vector<int>& invitees, const int& k) {
    //find degrees of all node
    vector<int> kicked;
    for (unordered_map<int,Node*>::iterator iter = map.begin(); 
                iter != map.end(); iter++){
        iter->second->done = true;
        iter->second->prev = nullptr; //leaves this alone
        iter->second->dist = iter->second->friends.size();
        if(iter->second->dist < k) {
            kicked.push_back(iter->second->name);
            iter->second->done = false;
            cout << "init " << iter->second->name << endl;
        }
    }

    //decrement for each friend of kickee
    int currDist = 0;
    for(unsigned int i = 0; i < kicked.size(); ++i) {
        cout << "delete edges for " << kicked[i] << endl;
        for(int buddy : map[kicked[i]]->friends) {
            currDist = map[buddy]->dist;
            map[buddy]->dist = currDist - 1;

            if(buddy == 1285) {
                cout << "1285 has edges = " << currDist << endl;
            }

            if((currDist <= k) & (map[buddy]->done)) {
                kicked.push_back(map[buddy]->name);
                //cout << "kicking " << map[buddy]->name << endl;
                map[buddy]->done = false;
            }
        }
    }

    for(unordered_map<int,Node*>::iterator iter = map.begin(); 
                iter != map.end(); iter++){
        if(iter->second->done) {
            invitees.push_back(iter->second->name);
        }
    }

    sort(invitees.begin(), invitees.end());
}
