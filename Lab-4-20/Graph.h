/*****
 * Author   : karroje
 * Date     : 2011-04-10
 * Modified : inclezd, 04/19/2015
 * Sources  : All code is original
 * Purpose  : This class is intended to serve as the (abstract) base class for implementatons of a basic
 *            weighted, undirectly graph class.  It is intended that any such is static in terms of node size 
 *            (that is, the number of nodes of a particular object is specified at construction and never changed), 
 *            with nodes index by consecurive integers.  Weights will be positive doubles; edges may nt have a weight of 0.
 * Note     : DO NOT CHANGE THIS FILE!!! 
 */

#include <utility>
#include <list>

#pragma once

 /*
 * Useful typedefs, primarily for the purpose of readability.
 */
typedef unsigned NodeID;
typedef std::list<NodeID> EList;

class Graph {
 public:
  virtual ~Graph() {}

  /*
   * Add an undirected edge between nodes u and v.
   * 
   * Preconditions: 
   *     u and v are legal labels (i.e. 0 <= u < G.size(), 0 <= v < G.size())
   *     u != v
   *     There is no edge between u and v.
   */
  virtual void addEdge(NodeID u, NodeID v) = 0;
  
  /*
   * Return true if there is an edge between nodes u and v; return false otherwise.
   *
   * Preconditions: 
   *     u and v are legal labels (i.e. 0 <= u < G.size(), 0 <= v < G.size())
   */
  virtual bool isEdge(NodeID u, NodeID v) const = 0;

  /*
   * Return a list of NodeIDs describing the nodes adjacent to edge u.
   *
   * Precondition: 
   *	u is a legal label.
   */
  virtual EList getAdj(NodeID u) const = 0;

  /*
   * Return the degree (i.e. the number of neighbors) of node u.
   *
   * Preconditions: 
   *	u is a legal label;
   */
  virtual unsigned degree(NodeID u) const = 0;

  /*
   * Return the number of nodes in the graph.
   */
  virtual unsigned size() const = 0;

  /* 
   * Return the number of edges in the graph.
   */
  virtual unsigned numEdges() const = 0;
};
