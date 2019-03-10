#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "Graph.hpp"

using namespace std;

void usage(char* program_name) {
    cerr << program_name << " called with incorrect arguments." << endl;
    cerr << "Usage: " << program_name
         << " friendship_pairs_file k_value output_file"
         << endl;
    exit(-1);
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        usage(argv[0]);
    }
    char* graph_filename = argv[1];
    char* output_filename = argv[3];
    istringstream ss(argv[2]);

    //create Graph
    Graph fbGraph;
    if(!fbGraph.loadFromFile(graph_filename)) {
        cerr << graph_filename << " not loaded\n";
        return -1;
    }

    //get k
    int k = -1;
    ss >> k; //converting stringstream to int
    
    //open outfile
    ofstream out(output_filename);
    if(!out.is_open()) {
        cerr << output_filename << "not opened!\n";
    }

    //find the invitees
    vector<int> invitees;
    fbGraph.socialgathering(invitees, k);

    //print names
    for(int person : invitees) {
        out << person << endl;
    }

    out.close();
}
