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

class MovieGraph {
public:
    unordered_map<string, Node *> actorList;
    vector<string> movie_names;
    vector<int> weights;
    /**
     * Loads the graph with data from in_filename
     * Each line is formatted:
     *      [actor]<tab>[movie]<tab>[year]
     */
    bool MovieGraph::loadMovies(const char* in_filename) {
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
    void MovieGraph::insertLine(string actor, string movie, string year) {
    }

    getMovieList(Node * from, Node * to) {
    }


};
#endif
