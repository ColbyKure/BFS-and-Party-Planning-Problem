/**
 * Assignment Name: PA 3
 * Filename: movieconnections.cpp 
 * Name: Sunny Sun & Colby Kure
 * Date: 03/07/2019
 * Description: This file contains the main method in which we try to find
 * 		the paths of nodes that are passed in via the pairs_filename
 *		and if there is a path we return the path in our outfile.
 */

#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
 
#include "MovieGraph.hpp"

using namespace std;

void usage(char* program_name) {
    cerr << program_name << " called with incorrect arguments." << endl;
    cerr << "Usage: " << program_name
	 << " GraphData.txt StartingActor.txt output.txt numberOfDegree"
	 << endl;
    exit(-1);
}

int main(int argc, char* argv[]) {

    if(argc != 5) {
        cout << argc << endl;
	    usage(argv[0]);
    }

    char* graph_filename = argv[1];
    char* actors_filename = argv[2];
    char* output_filename = argv[3];
    int numDegree = strtol(argv[4], nullptr, 10);

    /* You can call the pathfinder function from here */
    MovieGraph graph;

    if(!graph.loadMovies(graph_filename)) {
	    return -1;
    }

    //open files
    ofstream output(output_filename);
    ifstream input(actors_filename);
    if(!input.is_open()) {
        cerr << actors_filename << " not opened!\n";
        return -1;
    }
    input.seekg(0, ios::beg);

    while(input) {
        string start; 
        if (!getline(input, start)) break;

        cout << "Finding connections from " << start << endl;
        graph.connectMovies(graph.actorList[start]);

        vector<vector<string>*> data = graph.getData();
        if(numDegree > (int)data.size()) {
            cout << "change degree from " << numDegree << " to " << data.size() << endl;
            numDegree = data.size();
        }
        for(unsigned int i = 0; i < data.size(); ++i) {
            output << "degree " << i << endl;
            for(unsigned int j = 0; j < data[i]->size(); ++j) {
                output << "\t" << data[i]->at(j) << endl;
            }
            output << "size " << data[i]->size() << endl << endl;
        }
    }
    return 1;
}
