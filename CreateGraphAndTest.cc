/**********************************************************************
Title:          CreateGraphAndTest.cc
Author:         Erin Williams
Date Created:   4/30/18
Class:          Spring 2018 - CS335
Purpose:        Assignment #5
Description:    Driver program for Graph Representation
***********************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Graph.h"

using namespace std;

void TestConnected(const string &adj_filename, graphproject::Graph<int> &a_graph) {
  string adj_line;
  ifstream file(adj_filename);

  if(file.is_open()) {
    while(getline( file, adj_line )) {

      stringstream parser(adj_line);
      int vertex1, vertex2;
      parser >> vertex1 >> vertex2;

      cout << vertex1 << " " << vertex2 << ": ";

      if(a_graph.AreConnected(vertex1, vertex2)) {
          cout << "Connected, weight of edge is ";
          cout << a_graph.GetEdgeWeight( vertex1, vertex2 ) << endl;
      }
      else {
          cout << "Not connected\n";
      }
    }
    file.close();
  }
}

int main(int argc, char **argv) {

  if(argc != 3) {
    cout << "Usage: " << argv[0] << " graph_file adjacency_file" << endl;
    return 0;
  }

  const string graph_file(argv[1]);
  const string adjacency_file(argv[2]);

  graphproject::Graph<int> graph;
  graph.BuildGraph(graph_file);
  TestConnected(adjacency_file, graph);

  return 0;
}
