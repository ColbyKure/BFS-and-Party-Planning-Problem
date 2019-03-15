#include <vector>
#include <string>
#include <climits>
#include <iostream>
#include <unordered_map>

#include "MovieGraph.hpp"
#include "ActorNode.hpp"

int testinsertLine() { // xx lines
    cout << "Testing insertLine... ";

    //Testing Constructor()
    MovieGraph graph;

    //Testing insertLine(string actor, string movie, string year)
    string n1 = "CARUSO, DAVID (I)";
    string m1 = "JADE";
    string y1 = "1995";
    graph.insertLine(n1, m1, y1);

    auto tmp1 = graph.actorList.find(n1);
    ActorNode * node1;
    if(tmp1 == graph.actorList.end()) {
        cout << "\nerror: MovieGraph::insertLine\n\t";
        cout << "actorList did not contain " << n1 << endl;
        cout << "exiting\n";
        return -1;
    }
    else {
        node1 = tmp1->second;
    }

    if(node1->done) {
        cout << "\nerror: MovieGraph::insertLine\n\t";
        cout << "done field in node wrong\n";
    }

    if(n1.compare(node1->name) != 0) {
        cout << "\nerror: MovieGraph::insertLine\n\t";
        cout << node1->name << " should be " << n1 << endl;
    }

    if(node1->prev != 0) {
        cout << "\nerror: MovieGraph::insertLine\n\t";
        cout << "node.prev should be null\n";
    }

    //inserting 2nd line (old actor, new movie)
    string n2 = "CARUSO, DAVID (I)";
    string m2 = "GOLD";
    string y2 = "1949";
    graph.insertLine(n2, m2, y2);

    auto tmp2 = graph.actorList.find(n2);
    ActorNode * node2;
    if(tmp2 == graph.actorList.end()) {
        cout << "\nerror: MovieGraph::insertLine\n\t";
        cout << "actorList did not contain " << n2 << endl;
        cout << "exiting\n";
        return -1;
    }
    else {
        node2 = tmp2->second;
    }

    if(node1 != node2) {
        cout << "\nerror: MovieGraph::insertLine\n\t";
        cout << "nodes should be the same!!!\n";
    }

    if(node2->edges.size() != 2) {
        int i = node2->edges.size();
        cout << "\nerror: MovieGraph::insertLine\n\t";
        cout << n2 << " only has " << i << " edges\n";
        cout << "\tshouldhave 2\n";
    }

    //inserting 3rd line (new actor, old movie)
    string n3 = "CARUSO, PHILLIP V.";
    string m3 = "GOLD";
    string y3 = "1949";
    graph.insertLine(n3, m3, y3);

    auto tmp3 = graph.actorList.find(n3);
    ActorNode * node3;
    if(tmp3 == graph.actorList.end()) {
        cout << "\nerror: MovieGraph::insertLine\n\t";
        cout << "actorList did not contain " << n3 << endl;
        cout << "exiting\n";
        return -1;
    }
    else {
        node3 = tmp3->second;
    }

    if(node3->edges.size() != 1) {
        cout << "\nerror: MovieGraph::insertLine\n\t";
        cout << node3 << " has wrong number of edges\n";
    }

    if(node3->edges[0].compare(node1->edges[1]) != 0) {
        cout << "\nerror: MovieGraph::insertLine\n\t";
        cout << "edges should match\n";
    }

    string movieYear1 = m1 + '\t' + y1;
    if(movieYear1.compare(node1->edges[0]) != 0) {
        cout << "\nerror: MovieGraph::insertLine\n\t";
        cout << "edges not correct\n";
    }

    auto tmp4 = graph.movieList.find(movieYear1);
    if(tmp4 == graph.movieList.end()) {
        cout << "\nerror: MovieGraph::insertLine\n\t";
        cout << m1 <<"not found in movieList\n";
    }

    auto tmp5 = graph.movieList.find(node3->edges[0]);
    if(tmp5 == graph.movieList.end()) {
        cout << "\nerror: MovieGraph::insertLine\n\t";
        cout << m2 << "not found in movieList\n";
    }

    if(tmp5->second.size() != 2) {
        cout << "\nerror: MovieGraph::insertLine\n\t";
        cout << "size of vector<ActorNode*> is wrong\n";
    }
    
    cout << "DONE!\n";
    return 1;
}

int testActorNode() { // 47 lines
    cout << "Testing ActorNode... "; 

    //Testing Constructor()
    string str = "[Actor's Name]";
    ActorNode node1(str);

    if(node1.name.compare(str)) {
        cout << "\nerror: ActorNode::Constructor\n\t";
        cout << node1.name << " supposed to be " << str << endl;
    }

    node1.minWeight = INT_MAX;
    if(node1.minWeight != INT_MAX) {
        cout << "\nerror: ActorNode.minWeight\n\t";
        cout << "INT_MAX not working properly?\n";
    }

    node1.done = true;
    if(!node1.done) cout << "\nerror: ActorNode.done\n";

    if(node1.prev != nullptr) {
        cout << "\nerror: ActorNode.prev\n\t";
        cout << "should be nullptr\n";
    }

    node1.prev = &node1;
    if(node1.prev == nullptr) {
        cout << "\nerror: ActorNode.prev\n\t";
        cout << "should be " << hex << &node1 << endl;
    }

    if(!node1.edges.empty()) {
        cout << "\nerror: ActorNode.edges\n\t";
        cout << "edges should be empty\n";
    }

    cout << "DONE!\n";
    return 1;
}

int main() {
    testActorNode();
    testinsertLine();
    //used gdb to confirm loadMovies works properly

    cout << "**********Testing Done!**********\n";
    return 1;
}
