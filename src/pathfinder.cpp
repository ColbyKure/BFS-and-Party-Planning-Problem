/**
 * Assignment Name: PA 3
 * Filename: pathfinder.cpp 
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
#include "Graph.hpp"

using namespace std;

void usage(char* program_name) {
    cerr << program_name << " called with incorrect arguments." << endl;
    cerr << "Usage: " << program_name
	 << " friendship_pairs_file test_pairs_file output_file"
	 << endl;
    exit(-1);
}

int main(int argc, char* argv[]) {

    if(argc != 4) {
	    usage(argv[0]);
    }

    char* graph_filename = argv[1];
    char* pairs_filename = argv[2];
    char* output_filename = argv[3];

    /* You can call the pathfinder function from here */
    Graph fbGraph;
    ifstream infile(pairs_filename);
    ofstream out(output_filename);

    if (!fbGraph.loadFromFile(graph_filename)){
	    return -1;
    }

    infile.seekg(0, ios::beg);
    while(infile) {
        //get each line in file
	string pairs; 
	if(!getline(infile, pairs)){
	    break;
	}
	//get each char in line
	istringstream ss(pairs);
	vector<string> record;
	while (ss) {
	    string s;
	    if (!getline(ss, s, ' ')){
	        break;
	    }
	    record.push_back(s);

	    if(record.size() != 2) {
	        continue;
            }
            //found path to find
            int num1 = strtol(record[0].c_str(), nullptr, 10);
	    int num2 = strtol(record[1].c_str(), nullptr, 10);

    	    Node * from = fbGraph.map[num1]; 
    	    Node * to = fbGraph.map[num2];
	    
	    //checks if there is an existing path
    	    bool hasPath = fbGraph.pathfinder(from, to);

	    if(!out.is_open()) {
                cerr << output_filename << " not opened!\n";
	        return -1;
            }

	    if(!hasPath){
                out << endl;
                continue;
            }

	    vector<int> path = fbGraph.getPath(from, to);
	    for (int i = path.size()-1; i >= 0; i--){
                if(i == 0) {
                    out << path[i];
                    break;
                }
	        out << path[i] << " ";
	    }	     
	    out << endl;
        }
    }
    //close files
    if(out.is_open()) {
        out.close();
    }
    if(infile.is_open()) {
        infile.close();
    }
    return 1;
}
