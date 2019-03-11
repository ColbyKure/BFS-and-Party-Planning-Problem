/**
 * Assignment Name: PA 3
 * Filename: movieconnections.cpp 
 * Name: Sunny Sun & Colby Kure
 * Date: 03/07/2019
 * Description: This file contains the main method in which we try to find
 * 		the paths of nodes that are passed in via the pairs_filename
 *		and if there is a path we return the path in our outfile.
 **/
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
 
#include "MST.hpp"

using namespace std;

void usage(char* program_name) {
    cerr << program_name << " called with incorrect arguments." << endl;
    cerr << "Usage: " << program_name
	 << " actor_pairs.txt output.txt"
	 << endl;
    exit(-1);
}

int main(int argc, char* argv[]) {

    if(argc != 3) {
	    usage(argv[0]);
    }

    char* graph_filename = argv[1];
    char* output_filename = argv[2];

    /* You can call the pathfinder function from here */
    MovieGraph mst;

    if(!mst.loadFromFile(graph_filename)){
	    return -1;
    }

    movieconnections(output_filename);
    return 1;
}
