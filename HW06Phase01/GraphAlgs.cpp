#include "GraphAlgs.h"
#include "MatrixGraph.h"
#include "Graph.h"
#include <iostream>

using namespace std;

pair<vector<NodeID>, EdgeWeight> TSP(Graph* G) {
	EList adj;
	vector<NodeID> visited = vector<NodeID>();
	EdgeWeight e = 0;
	int num_nodes = G->size();
	int num_edges = G->numEdges();
	NodeID next = 0;
	NodeID start = 0; // start node

	//Add the starting vertex
	//visited.push_back(0);

	for(int i = 0; i <= num_nodes; i++) {
		// Get the adjacent nodes, next is initially the starting node: 0
		adj = G->getAdj(next);

		// Find the neighbor with the smallest weight
		list<NWPair>::const_iterator it;
		NWPair smallest(numeric_limits<int>::max(), numeric_limits<double>::infinity());

		for (it = adj.begin(); it != adj.end(); it++) {
			// Check to see if the node has not been visited
			if (find(visited.begin(), visited.end(), it->first) != visited.end()) {
				/* visited contains the node */
				continue;
			}
			// Check to see if the start node is only node adj and not visited
			else if (it->first == start) {
				list<NWPair>::const_iterator it2;
				int onlyOne = 0;
				for (it2 = adj.begin(); it2 != adj.end(); it2++) {
					if (find(visited.begin(), visited.end(), it2->first) != visited.end()) {
						continue;
					}
					else if(it2->first == start) {
						
					}
					else {
						onlyOne++;
					}
				}
				if (onlyOne == 0) {
					smallest = NWPair(it->first, it->second);
				}
			}
			else {
				/* visited does not contain the node
				check to see if the node is the smallest neighbor
				*/
				if (it->second <= smallest.second) {
					smallest = NWPair(it->first, it->second);
				}
			}
			
		}
		// Smallest has been found
		if (smallest.first != numeric_limits<int>::max() && smallest.second != numeric_limits<double>::infinity()){
			next = smallest.first;
			visited.push_back(next);
			e += smallest.second;
		}
	}
	pair<vector<NodeID>, EdgeWeight> p(visited, e);
	return p;
}
