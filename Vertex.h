/**********************************************************************
Title:          Vertex.h
Author:         Erin Williams
Date Created:   4/30/18
Class:          Spring 2018 - CS335
Purpose:        Assignment #5
Description:    Vertex Class for a Graph
***********************************************************************/

#ifndef VERTEX_H
#define VERTEX_H

#include<list>
#include<utility>
namespace graphproject {

class Vertex {
public:
  //explicit Vertex( Comparable name ) : name_ { name } {}
  std::list<std::pair<Vertex *, double>> adj; //adjacency list

private:
//  Comparable name_;

//  bool known;
//  float dist;
//  Vertex * path;

};

} //graphproject

#endif //VERTEX_H
