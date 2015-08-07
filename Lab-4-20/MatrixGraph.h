// MatrixGraph.h

#include <vector>
#include "Graph.h"

#pragma once

using namespace std;

class MatrixGraph : public Graph {
 public:
  MatrixGraph(int numNodes);
  ~MatrixGraph();

  // Modifiers
  virtual void addEdge(NodeID u, NodeID v);
  
  // Inspectors
  virtual bool isEdge(NodeID u, NodeID v) const;
  virtual EList getAdj(NodeID u) const;
  virtual unsigned degree(NodeID u) const;
  virtual unsigned size() const;
  virtual unsigned numEdges() const;

 private:
  MatrixGraph() {;}

  vector<vector<unsigned>> M;
  int num_edges;
};
