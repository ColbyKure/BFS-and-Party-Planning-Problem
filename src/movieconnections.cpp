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

        graph.connectMovies(graph.actorList[start]);
        vector<vector<ActorNode*>*> data = graph.getData();
        for(unsigned int i = 1; i < data.size() && (int)i <= numDegree; ++i) {
            output << "degree " << i << endl;
            unordered_map<string, bool> hashtable;
            for(unsigned int j = 0; j < data[i]->size(); ++j) {
                auto find = hashtable.find(data[i]->at(j)->prevEdge);
                if(find != hashtable.end()) {
                    continue;
                }
                output << "\t" << data[i]->at(j)->name << "\t" << data[i]->at(j)->prevEdge << endl;
                hashtable[data[i]->at(j)->prevEdge] = true;
            }
            output << "size " << data[i]->size() << endl << endl;
        }

        for(int i = data.size() - 1; i >= 0; --i) {
            delete(data[i]);
        }
    }

    input.close();
    output.close();
    return 1;
}
