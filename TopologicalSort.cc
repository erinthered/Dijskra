/**********************************************************************
Title:          TopologicalSort.cc
Author:         Erin Williams
Date Created:   4/30/18
Class:          Spring 2018 - CS335
Purpose:        Assignment #5
Description:    Driver file for Topological Sorting
***********************************************************************/

#include <string>

#include "Graph.h"

using namespace std;

int main(int argc, char **argv) {

  if(argc != 2) {
    cout << "Usage: " << argv[0] << " graph_file" << endl;
    return 0;
  }

  const string graph_file(argv[1]);

  graphproject::Graph<int> graph;
  graph.BuildGraph( graph_file );
  graph.TopologicalSort();

  return 0;
}
