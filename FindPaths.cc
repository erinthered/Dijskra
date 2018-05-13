/**********************************************************************
Title:          FindPaths.cc
Author:         Erin Williams
Date Created:   4/30/18
Class:          Spring 2018 - CS335
Purpose:        Assignment #5
Description:    Driver File for Dijkstra's Algorithm Implementation 1
***********************************************************************/

#include<string>

#include "Graph.h"

using namespace std;

int main(int argc, char **argv) {

  if(argc != 3) {
    cout << "Usage: " << argv[0] << " graph_file starting_vertex" << endl;
    return 0;
  }

  const string graph_file(argv[1]);
  const unsigned int starting_vertex = atoi(argv[2]);

  graphproject::Graph<int> graph;

  graph.BuildGraph( graph_file );
  graph.Dijkstra( starting_vertex );

  return 0;
}
