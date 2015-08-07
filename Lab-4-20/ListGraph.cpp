#include "ListGraph.h";

#include <assert.h>;

ListGraph::ListGraph(int numNodes) {
	edgeList = vector<EList>(numNodes);
	num_edges = 0;
}

ListGraph::~ListGraph() {
	
}

void ListGraph::addEdge(NodeID u, NodeID v) {
	assert(u >= 0 && u <= size());
	assert(v >= 0 && v <= size());
	assert(u != v);
	assert(!isEdge(u, v));

	edgeList[u].push_back(v);
	edgeList[v].push_back(u);

	num_edges++;
}

bool ListGraph::isEdge(NodeID u, NodeID v) const {
	EList::const_iterator it;
	for(it = edgeList[u].begin(); it != edgeList[u].end(); it++) {
		if(*it == v) {
			return true;
		}
	}
	return false;
}

EList ListGraph::getAdj(NodeID u) const {
	EList::const_iterator it;
	EList list(degree(u));
	for(it = edgeList[u].begin(); it != edgeList[u].end(); it++) {
		list.push_back(*it);
	}
	return list;
}

unsigned int ListGraph::numEdges() const {
	return num_edges;
}

unsigned int ListGraph::degree(NodeID u) const {
	EList::const_iterator it;
	int degree = 0;
	for(it = edgeList[u].begin(); it != edgeList[u].end(); it++) {
		degree++;
	}
	return degree;
}

unsigned int ListGraph::size() const {
	return edgeList.size();
}