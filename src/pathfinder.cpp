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
  
  if (argc != 4) {
    usage(argv[0]);
  }
  

  char* graph_filename = argv[1];
  char* pairs_filename = argv[2];
  char* output_filename = argv[3];

  //TODO   
 /* You can call the pathfinder function from here */
 //make a graph
 Graph fbGraph;
 
 if (!loadFromFile(graph_filename)){
     return 1;
 }
     ifstream infile(pairs_filename);
    
 while (infile) { 
 
     //get each line in file
     string pairs; 
     if (!getline(infile, pairs)){
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
      }
      
      if (record.size() != 2) {
             continue;
      }
         //TODO
 
 }

     pathFinder()
 
    
}  
