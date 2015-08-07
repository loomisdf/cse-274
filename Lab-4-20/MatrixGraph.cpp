#include "MatrixGraph.h";

#include <assert.h>;

MatrixGraph::MatrixGraph(int numNodes) {
	M = vector<vector<unsigned>>(numNodes,vector<unsigned>(numNodes));
	// Initialize M with 0s
	for(int i = 0; i < numNodes; i++) {
		for( int j = 0; j < numNodes; j++) {
			M[i][j] = 0;
		}
	}
	num_edges = 0;
}

MatrixGraph::~MatrixGraph() {

}

void MatrixGraph::addEdge(NodeID u, NodeID v) {
	assert(u >= 0 && u <= size());
	assert(v >= 0 && v <= size());
	assert(u != v);
	assert(!isEdge(u, v));

	M[u][v] = 1;
	M[v][u] = 1;

	num_edges++;
}

bool MatrixGraph::isEdge(NodeID u, NodeID v) const {
	if(M[u][v] == 1) {
		return true;
	}
	return false;
}

EList MatrixGraph::getAdj(NodeID u) const {
	EList list(degree(u));
	for(int i = 0; i < M.size(); i++) {
		if(M[i][u] == 1) {
			list.push_back(i);
		}
	}
	return list;
}

unsigned int MatrixGraph::degree(NodeID u) const {
	int degree = 0;
	for(int i = 0; i < M.size(); i++) {
		if(M[i][u] == 1) {
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

