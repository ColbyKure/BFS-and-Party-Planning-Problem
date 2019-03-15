#ifndef MOVIEGRAPH_HPP
#define MOVIEGRAPH_HPP
/**
 * Assignment: PA3
 * Filename: MovieGraph.hpp
 * Name: Sunny Sun & Colby Kure
 * Date: 03/10/2019
 * Description: This file holds the graph with actors as nodes and 
 *      movies as weighted edges.
 **/
#include <sstream>
#include <fstream>
#include <iostream>
#include <string>
#include <queue>
#include <climits>
#include <unordered_map>

#include "ActorNode.hpp"

using namespace std;

/**
 * A function class for the priority queue of ActorNode*
 */
class ActorNodePtrComp {
public:
    bool operator()(ActorNode *& lhs, ActorNode *& rhs) {
        return lhs->minWeight > rhs->minWeight;
    }
};

class MovieGraph {
public:
    unordered_map<string, ActorNode*> actorList;
    unordered_map<string, vector<ActorNode*>> movieList;
    
    /* Constructor */
    MovieGraph(void){ }

    /* Destructor */
    ~MovieGraph(void) {
        for(auto itr : actorList) {
            delete itr.second;
        }
    }

    /* insertLine from file into graph */
    void insertLine(string actor, string movie, string year) {
        string movieYear = movie + " " + year;

        unordered_map<string, ActorNode*>::iterator node;
        node = actorList.find(actor);
        if(node == actorList.end()) {
            actorList[actor] = new ActorNode(actor);
        }

        actorList[actor]->edges.push_back(movieYear);
        movieList[movieYear].push_back(actorList[actor]);
    }
    
    /**
     * Loads the graph with data from in_filename
     * Each line is formatted:
     *      [actor]<tab>[movie]<tab>[year]
     */
    bool loadMovies(const char* in_filename) {
    	ifstream infile(in_filename);
    	infile.seekg(0, ios::beg);
   
        bool first = true;
        while (infile) { 
            //get each line in file
            string s; 
            if (!getline(infile, s)) break;
            if (first) { //skip header line in file
                first = false;
                continue;
            }
            //get each char in line
            istringstream ss(s);
            vector<string> record;
            while (ss) {
                string s;
                if (!getline(ss, s, '\t')) break;
                record.push_back(s);
            } 
            if (record.size() != 3) {
                continue;
            }
            insertLine(record[0], record[1], record[2]);
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
     * Prim's Algorithm
     */
    void connectMovies(ActorNode * start) {
        //init data values
        for(auto iter = actorList.begin(); iter != actorList.end(); iter++) {
            iter->second->prev = nullptr;
            iter->second->minWeight = INT_MAX;
            iter->second->done = false;
        }

        //init priority queue
        priority_queue<ActorNode*, vector<ActorNode*>, ActorNodePtrComp> pq;
        pq.push(start);

        //loop until empty
        ActorNode * curr;
        while(!pq.empty()) {
            curr = pq.top();
            pq.pop();
            //continue until we find a new node
            if(curr->done) continue;
            curr->done = true;
            //loop through movies curr was in
            for(string movieYear : curr->edges) {
                vector<ActorNode*> actors = movieList[movieYear];
                int weight = getWeight(movieYear); //call to getWeight
                //find all other actors in this movie
                for(ActorNode* actor : actors) {
                    if(actor->done) continue; //if already in tree continue
                    //if weight is less than current weight add to pq
                    if(weight < actor->minWeight) {
                        actor->prev = curr;
                        actor->prevEdge = movieYear;
                        actor->minWeight = weight;
                        pq.push(actor);
                    }
                } 
            } 
        } //loop while pq non-empty
    }

    /* gets data after Prim's */
    vector<vector<ActorNode*>*> getData() {
        //base case 
        vector<vector<ActorNode*>*> ret;

        //init fields 
        for(auto iter = actorList.begin(); iter != actorList.end(); iter++) {
            iter->second->done = false;
            iter->second->minWeight = -1; //use minWeight for degree
        }

        for(auto iter = actorList.begin(); iter != actorList.end(); iter++) {
            if(!iter->second->done) {
                (void)setDegree(iter->second, ret);
            }
        }
        return ret;
    }

    /* helper to set degree from start */
    int setDegree(ActorNode * node, vector<vector<ActorNode*>*> & ret) {
        //if start node
        if(node->prev == nullptr) {
            return -1;
        }
        //if already found
        if(node->done) {
            return -1;
        }

        //get path to start
        ActorNode * curr = node;
        int dist = 0;
        vector<ActorNode *> path;
        path.push_back(curr);
        while(curr->prev) { 
            curr = curr->prev;
            path.push_back(curr);
            dist++;
        }

        //path_compression-like function to set degrees 
        for(int i = 0; i < dist; ++i) {
            if(path[i]->done) continue;
            path[i]->done = true;
            path[i]->minWeight = dist - i;

            //allocate space for vector
            while(ret.size() <= (unsigned int)(dist - i)) {
                vector<ActorNode*> * empty = new vector<ActorNode*>();
                ret.push_back(empty);
            }

            ret[dist - i]->push_back(path[i]);
        }
        return 1;
    }
    
    /**
     * Extracts the year and returns it 
     * movieYear is a string formatted:
     *      <movie_title><tab><year>
     *
     * Returns: the weight of an edge which is the year
     */
    int getWeight(string movieYear) {
        unsigned int tab = movieYear.find_last_of("\t");
        string year = movieYear.substr(tab+1);
        return strtol(year.c_str(), nullptr, 10); //year is the weight
    }

    /**
     * Gets the list of movies that were used as edges in mst
     */
    vector<string> getNextDegree(vector<ActorNode *> prevDegree) {
        vector<string> ret; //return vector
        //for each movieYear in edges check prev
        vector<ActorNode*> cast;
        for(ActorNode * start : prevDegree) {
            for(string movieYear : start->edges) {
                cast = movieList[movieYear];
                for(ActorNode * end : cast) {
                    if(end->prev == start) {
                        ret.push_back(movieYear);
                    }
                }
            }
        }
        return ret;
    }

    /**
     * According to each line it inserts actors as nodes, movie as edges, and 
     * year as weight into the graph.
     */
    /*void insertLine(string actor, string movie, string year) {
    	auto node = actorList.find(actor);
	// if the actor does not previously exist in the list
	if (node == actorList.end()){
	    actorList[actor] = new ActorNode(actor);
	    actorList[actor]->movieNames.push_back(movie);
	    actorList[actor]->years.push_back(year);
	    
	}
	//if it does exist, just add movie and year
	else{
	    actorList[actor]->movieNames.push_back(movie);
	    actorList[actor]->years.push_back(year);	
	}

	if(awm.find(actor) == awm.end()){
	    //TODO what to do if same name movie different year
       	    //adding actors to existing movies
	    awm[movie].push_back(actor);
	//TODO what to do with the weight??
	}
    }*/

    /**
     * Prim's algorithm
     */
    /*void getMovieConnections(ActorNode * starting, int numDegree){
        //first initialize all the fields 
        starting->done = false;
        starting->prev = nullptr;
        starting->weights = -1;
	//TODO initialize movies and year
        queue<ActorNode *> queue;

        ActorNode * curr;
        while(!queue.empty()){
            curr = queue.front();
	    queue.pop();
	    for (ActorNode * actor : curr->edges){
	         if(!actorList[actor]->done){
        	     starting->done = true;
        	     starting->prev = curr;
        	     //starting->weights = ; //TODO set year
		     //TODO set movies
	    	     queue.push(actorList[actor]);
	         }
	         //if it is already visited
		 //else if (actorList[actor]->done || degree == numDegree){
		     //movieList = getMovieList(starting:)
		 
		 //}
	    }
    
        }
    }*/
};
#endif
