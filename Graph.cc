/**********************************************************************
Title:          Graph.cc
Author:         Erin Williams
Date Created:   5/12/18
Class:          Spring 2018 - CS335
Purpose:        Assignment #5
Description:    Graph Class - Directed and Weighted Graph
***********************************************************************/

#include "Graph.h"

namespace graphproject {

  // Function used for testing
  //template <typename Comparable>
/*  void Graph<Comparable>PrintGraph() {
    for(auto & entry : vertices_) {
      std::cout << entry.first << " ";
      std::cout << std::endl;
    }
  }
  */

  template <typename Comparable>
  bool Graph<Comparable>::Insert( const Comparable& label ) {
    auto itr = vertices_.find( label );
    //vertex already in map, return false
    if( itr != vertices_.end() ) {
      return false;
    }
    //insert new vertex in map, return true
    vertices_.insert( std::pair<Comparable, Vertex> ( label, Vertex{ label } ) );
    return true;
  }

  template <typename Comparable>
  bool Graph<Comparable>::InsertInAdjList( const Comparable& current_index,
            const Comparable& list_index, double dist ) {

    //list index vertex already in current index adjacency map,
    //or current index not in map, return false
    auto itr = vertices_.find( current_index );
    if( AreConnected( current_index, list_index ) || itr == vertices_.end() ) {
      return false;
    }
    // insert label of connected vertex and distance of edge
    // connecting current_index, return true
    itr->second.adj_.insert( std::pair<Comparable, double> (list_index, dist) );
    return true;
  }

  template <typename Comparable>
  void Graph<Comparable>::BuildGraph( const std::string &graph_filename ) {
    std::string graph_line;
    std::ifstream file(graph_filename);

    if(file.is_open()) {
      while(getline( file, graph_line )) {

        std::stringstream parser(graph_line);
        Comparable current_index, list_index; double distance;

        parser >> current_index;
        Insert( current_index );

        while( parser >> list_index >> distance ) {
          InsertInAdjList( current_index, list_index, distance );

          //increase indegree of each vertex added to adjacency list
          //used for TopologicalSort
          ++vertices_.find( list_index )->second.indegree_;
        }
      }
      file.close();
    }
  }

  template <typename Comparable>
  bool Graph<Comparable>::AreConnected( int v1, int v2 ) {
    auto itr = vertices_.find( v1 );
    // v1 not in graph
    if( itr == vertices_.end() ) {
      return false;
    }
    // If v2 is found in v1's adjacency list, return true, else return false
    return ( itr->second.adj_.find( v2 ) != itr->second.adj_.end() );
  }

  // returns weight of edge between two vertices: v1 & v2
  template <typename Comparable>
  double Graph<Comparable>::GetEdgeWeight( int v1, int v2 ) {
    auto itr = vertices_.find( v1 );
    return itr->second.adj_.find( v2 )->second;
  }

  template <typename Comparable>
  void Graph<Comparable>::InitializeVertices() {
    for( auto & entry : vertices_ ) {
        entry.second.dist_ = INF;
        entry.second.known_ = false;
    }
  }

  template <typename Comparable>
  void Graph<Comparable>::Dijkstra( const Comparable& starting_vertex ) {
    //set all vertex distances to infinity and all known to false
    InitializeVertices();

    // set distance of starting vertex to 0
    auto v_itr = vertices_.find( starting_vertex );
    v_itr->second.dist_ = 0;

    // initialize empty priority queue of vertex pointers
    // priority queue is a min heap
    std::priority_queue<Vertex*, std::vector<Vertex*>, VertexCompare> min_queue{};
    // push start vertex to queue
    min_queue.push( &v_itr->second );

    for( ; ; ) {
      // priority queue contains both known and unknown vertices in this implementation
      bool success = false;
      while( !min_queue.empty() && !success ) {
        if(!min_queue.top()->known_)
          success = true;
        else
          min_queue.pop();
      }
      if(!success)
        break;

     // v is smallest unknown vertex
      Vertex* v = min_queue.top();
      min_queue.pop();
      v->known_ = true;

      // for each vertex w adjacent to v
      auto & adj_list = v->adj_;
      for( auto & w : adj_list ) {
        // if v.dist + cvw < w.dist
        auto w_itr = vertices_.find( w.first );
        double cost_v_to_w = w.second;
        if( v->dist_ + cost_v_to_w < w_itr->second.dist_ ) {
          //update w.dist
          w_itr->second.dist_ = v->dist_ + cost_v_to_w;
          //push w to min_queue
          min_queue.push( &w_itr->second );
          // set v as path to w
          w_itr->second.path_ = v;
        }
      }
    }

    for( auto & vertex : vertices_ ) {
      std::cout << vertex.second.label_ << ": ";
      PrintPath( vertex.second );
      std::cout << " (Cost: " << vertex.second.dist_ << ")" << std::endl;
    }
  }

  template <typename Comparable>
  void Graph<Comparable>::TopologicalSort() {
    std::queue<Vertex*> q;
    std::queue<Comparable> sort_queue;

    int counter = 0;
    //push all vertices with indegree 0 to queue
    for( auto & vertex : vertices_ ) {
      if( vertex.second.indegree_ == 0 ) {
        q.push( &vertex.second );
      }
    }

    while(!q.empty()) {
      Vertex* v = q.front();
      q.pop();
      //order vertices in sort
      v->top_sort_num_ = ++counter;
      sort_queue.push(v->label_);

      //for each Vertex w adjacent to v
      auto & adj_list = v->adj_;
      for( auto w : adj_list ) {
        auto itr = vertices_.find( w.first );
        if( --itr->second.indegree_ == 0 ) {
           q.push( &itr->second );
         }
      }
    }
    if(counter != vertices_.size()) {
      std::cout << "Cycle found\n";
    }
    else {
      while(!sort_queue.empty()) {
        std::cout << sort_queue.front();
        sort_queue.pop();
        if(!sort_queue.empty()) {
          std::cout << ", ";
        }
        else {
          std::cout << std::endl;
        }
      }
    }
  }

  template <typename Comparable>
  void Graph<Comparable>::PrintPath( const Vertex& v ) {
      if( v.path_ != nullptr ) {
        PrintPath( *v.path_ );
        std::cout << ", ";
       }
       std::cout << v.label_;
  }

} //graphproject
