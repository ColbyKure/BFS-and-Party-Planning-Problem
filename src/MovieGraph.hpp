/**
 * Assignment: PA3
 * Filename: MovieGraph.hpp
 * Name: Sunny Sun & Colby Kure
 * Date: 03/10/2019
 * Description: This file holds the graph with actors as nodes and 
 *      movies as weighted edges.
 **/

#ifndef MOVIEGRAPH_HPP
#define MOVIEGRAPH_HPP

#include <iostream>
#include "ActorNode.hpp"
class MovieGraph {
public:
    unordered_map<string, ActorNode *> actorList;
    unordered_map<string, vector<string>> awm; //actors within same movie
    vector<int> weights;
    
    
    /* Constructor */
    MovieGraph(void){}

    /* Destructor */
    ~MovieGraph(void) {
        for (auto itr : actorList) {
            delete itr.second;
        }
    } 
    
    /**
     * Loads the graph with data from in_filename
     * Each line is formatted:
     *      [actor]<tab>[movie]<tab>[year]
     */
    bool loadMovies(const char* in_filename) {
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
     * According to each line it inserts actors as nodes, movie as edges, and 
     * year as weight into the graph.
     */
    void insertLine(string actor, string movie, string year) {
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
    }

    /**
     * Prim's algorithm
     */
    void getMovieConnections(ActorNode * starting, int numDegree){
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
        	     starting->weights = ; //TODO set year
		     //TODO set movies
	    	     queue.push(actorList[actor]);
	         }
	         //if it is already visited
		 else if (actorList[actor]->done || degree == numDegree){
		     movieList = getMovieList(starting:)
		 
		 }
	    }
    
        }
    }
    
    
    /**
     * return the whole list vector of ints
     */
    vector<int> getMovieList(ActorNode * starting, int numberOfDegree) {
         
    }

};
#endif
