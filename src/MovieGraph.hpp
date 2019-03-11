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
    }
    
    /**
     * According to each line it inserts actors as nodes, movie as edges, and 
     * year as weight.
     */
    void MovieGraph::insertLine(string actor, string movie, string year) {
    }

    getMovieList(Node * from, Node * to) {
    }


};
#endif
