#include "ListGraph.h"

#include <assert.h>

ListGraph::ListGraph(int numNodes) {
	edgeList = std::vector<EList>(numNodes);
	num_edges = 0;
}

ListGraph::~ListGraph() {

}

void ListGraph::addEdge(NodeID u, NodeID v, EdgeWeight weight) {
	assert(u >= 0 && u <= size());
	assert(v >= 0 && v <= size());
	assert(u != v);
	assert(!isEdge(u, v));

	edgeList[u].push_back(NWPair(v, weight));
	edgeList[v].push_back(NWPair(u, weight));

	num_edges++;
}

EdgeWeight ListGraph::weight(NodeID u, NodeID v) const {
	EList::const_iterator it;
	for (it = edgeList[u].begin(); it != edgeList[u].end(); it++) {
		if (it->first == v) {
			return it->second;
		}
	}
	return false;
}

bool ListGraph::isEdge(NodeID u, NodeID v) const {
	EList::const_iterator it;
	for (it = edgeList[u].begin(); it != edgeList[u].end(); it++) {
		if (it->first == v) {
			return true;
		}
	}
	return false;
}

EList ListGraph::getAdj(NodeID u) const {
	return edgeList[u];
}

unsigned int ListGraph::numEdges() const {
	return num_edges;
}

unsigned int ListGraph::degree(NodeID u) const {
	return edgeList[u].size();
}

unsigned int ListGraph::size() const {
	return edgeList.size();
}