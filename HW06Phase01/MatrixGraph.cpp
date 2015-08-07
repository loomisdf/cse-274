#include "MatrixGraph.h"

#include <assert.h>

MatrixGraph::MatrixGraph(unsigned numNodes) {
	// This code will initialize the vector and set all the values to 0
	M = std::vector<std::vector<EdgeWeight>>(numNodes, std::vector<EdgeWeight>(numNodes, 0));
	num_edges = 0;
}

MatrixGraph::~MatrixGraph() {

}

void MatrixGraph::addEdge(NodeID u, NodeID v, EdgeWeight weight) {
	assert(u >= 0 && u <= size());
	assert(v >= 0 && v <= size());
	assert(u != v);
	assert(!isEdge(u, v, weight));

	M[u][v] = weight;
	M[v][u] = weight;

	num_edges++;
}

EdgeWeight MatrixGraph::weight(NodeID u, NodeID v) const {
	return M[u][v];
}

bool MatrixGraph::isEdge(NodeID u, NodeID v, EdgeWeight weight) const {
	if (M[u][v] == weight) {
		return true;
	}
	return false;
}

EList MatrixGraph::getAdj(NodeID u) const {
	EList list;
	for (int i = 0; i < (int)M.size(); i++) {
		if (M[i][u] != 0) {
			list.push_back(NWPair(i, M[i][u]));
		}
	}
	return list;
}

unsigned int MatrixGraph::degree(NodeID u) const {
	int degree = 0;
	for (int i = 0; i < (int)M.size(); i++) {
		if (M[i][u] > 0) {
			degree++;
		}
	}
	return degree;
}

unsigned int MatrixGraph::size() const {
	return M.size();
}

unsigned int MatrixGraph::numEdges() const {
	return num_edges;
}