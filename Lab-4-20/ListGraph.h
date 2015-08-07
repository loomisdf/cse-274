// listGraph.h

#include <vector>
#include "Graph.h"

#pragma once

using namespace std;

class ListGraph : public Graph {
 public:
  ListGraph(int numNodes);
  ~ListGraph();

  // Modifiers
  virtual void addEdge(NodeID u, NodeID v);
  
  // Inspectors
  virtual bool isEdge(NodeID u, NodeID v) const;
  virtual EList getAdj(NodeID u) const;
  virtual unsigned degree(NodeID u) const;
  virtual unsigned size() const;
  virtual unsigned numEdges() const;

 private:
  ListGraph() {;}

  vector<EList> edgeList;
  int num_edges;
};
