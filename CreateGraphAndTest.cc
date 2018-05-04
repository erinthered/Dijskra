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
#include <vector>
#include <sstream>
#include <utility>
#include "Vertex.h"

using namespace std;

void InsertVectorInGraph(vector<graphproject::Vertex*> &a_graph, int index) {
  if( a_graph.capacity() < index ) {
    a_graph.reserve(2 * index);
  }
  if(a_graph[index] == nullptr) {
    a_graph[index] = new graphproject::Vertex;
  }
}

void BuildGraph( const string &graph_filename, vector<graphproject::Vertex*> &a_graph ) {
  string graph_line;
  ifstream file(graph_filename);

  if(file.is_open()) {
    while(getline( file, graph_line )) {

      stringstream parser(graph_line);
      int current_index, list_index; double distance;

      parser >> current_index;
      InsertVectorInGraph(a_graph, current_index);

      while(parser >> list_index >> distance) {
        InsertVectorInGraph(a_graph, list_index);
        std::pair<graphproject::Vertex*, double> adjacent_vertex_and_distance(a_graph[list_index], distance);
        a_graph[current_index]->adj.push_back(adjacent_vertex_and_distance);
      }
    }
    file.close();
  }
}

void TestConnected(const string &adj_filename, vector<graphproject::Vertex*> &a_graph) {
  
}

int main(int argc, char **argv) {

  if(argc != 3) {
    cout << "Usage: " << argv[0] << " graph_file adjacency_file" << endl;
    return 0;
  }

  const string graph_file(argv[1]);
  const string adjacency_file(argv[2]);

  // vector of size 10
  vector<graphproject::Vertex*> graph(10);
  BuildGraph(graph_file, graph);
  TestConnected(adjacency_file, graph);

  cout << "Size of graph: " << graph.size() << endl;
  for(auto & entry : graph ) {
    if(entry != nullptr) {
      for(auto & list : entry->adj ) {
        cout << "Distance: " << list.second << endl;
      }
    }

  }


  return 0;
}
