/**********************************************************************
Title:          Graph.h
Author:         Erin Williams
Date Created:   5/11/18
Class:          Spring 2018 - CS335
Purpose:        Assignment #5
Description:    Graph Class - Directed and Weighted Graph
***********************************************************************/

#ifndef GRAPH_H
#define GRAPH_H

#include<limits>  //std::numeric_limits<double>::infinity()
#include<map>
#include<queue>
#include<string>
#include<sstream>
#include<iostream>
#include<fstream>
#include<queue>

#define INF std::numeric_limits<double>::infinity()

namespace graphproject {

// Directed, weighted Graph class of Vertex nodes
// Assumes that Graph input file does not contain Vertices
// with duplicate values/labels.
template <typename Comparable>
class Graph {

private:

  // Vertex Nodes
  struct Vertex {
    // Map of names of adjacent Vertices their associated edge weights
    std::map<Comparable, double> adj_;

    //Used by TopologicalSort
    int indegree_;
    int top_sort_num_;

    //Used by Dijkstra
    bool known_;
    double dist_;
    Vertex* path_;

    // Value of Vertex
    Comparable label_;

    explicit Vertex( Comparable label ) : indegree_{ 0 }, top_sort_num_{ 0 },
                    path_{ nullptr }, label_{ label } {}

    inline void IncreaseIndegree() { ++indegree_; }
  };

  // Compare vertices functor for Dijkstra's Algorithm
  // Used in the priority queue constructor
  // std::priority_queue is a max heap by default, so > operator is used
  // in VertexCompare to obtain a min heap.
  struct VertexCompare {
    bool operator() ( const Vertex* lhs, const Vertex* rhs ) {
      return lhs->dist_ > rhs->dist_;
    }
  };

  // Graph -> Comparable is the value/label of the Vertex
  std::map<Comparable, Vertex> vertices_;

public:

  // Function used for testing
  // void PrintGraph();

  // Insert a Vertex in Graph
  // Comparable is the key, Vertex is the value
  // Returns true if new Vertex inserted, false if Vertex already in graph
  bool Insert( const Comparable& label );

  // Add connected Vertex's label and edge weight to current_index's adjacency lists
  // Insert the adjacent vertex if not already in graph
  // Increase adjacent Vertex's indegree (used for TopologicalSort)
  // If list_index is already in current_index's adjacency list or current_index
  // is not in the graph, return false, else return true.
  bool InsertInAdjList( const Comparable& current_index,
            const Comparable& list_index, double dist );

  // Build Graph from a file containing labels of Vertices and connected nodes
  // with associated edge weights
  // Precondition: Vertex labels are unique, no duplicates
  // Postcondition: graph contains vertices with adjacency lists of adjacent
  // vertices and the weight of the edges between them
  void BuildGraph( const std::string &graph_filename );

  // Tests if two vertices are Connected
  // Returns true if connected, false if not connected
  bool AreConnected( int v1, int v2 );

  // returns weight of edge between two vertices: v1 & v2
  double GetEdgeWeight( int v1, int v2 );

  // Implementation of Dijkstra's Algorithm for finding the shortest path between
  // a named starting vertex and all other vertices in a graph
  // Implemented using a priority queue, so runtime is O(|E|log|V|), where |E|
  // is the number of edges in the graph and |V| is the number of vertices.
  // Prints each vertex in graph, the path from the start vertex to the end
  // vertex for each vertex in graph, and the cost of the path.
  void Dijkstra( const Comparable& starting_vertex );

  // Topological Sort of graph
  // Prints a Topological sort of graph if no cycle is found
  // Prints an error message if cycle found
  void TopologicalSort();

private:
  //Print path of vertices
  //Used by Dijkstra's Algorithm for output
  void PrintPath( const Vertex& v );

  //Intialize Vertices for Dijkstra's Algorithm
  // Postcondition: all vertices distance set to infinity, known set to false
  void InitializeVertices();

};

} //graphproject

#include "Graph.cc"
#endif //GRAPH_H
