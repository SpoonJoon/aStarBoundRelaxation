#include <iostream>
#include <queue>
#include <memory>
#include <limits>
#include <algorithm>
#include <functional>
#include <vector>

struct Node {
	size_t i;	// Index of this node (not related to order, just for ID)
	std::vector<std::pair<Node*, double> > successors;
};

//MinPriorityQueue
template<class T, class C = std::vector<T>, class P = std::greater<typename C::value_type> >
struct MinQueue : std::priority_queue<T,C,P> {
   typename C::iterator begin() { return std::priority_queue<T, C, P>::c.begin(); }
   typename C::iterator end() { return std::priority_queue<T, C, P>::c.end(); }
};

void reconstructPath(Node* predecessors[], Node* current) {
	// From wikipedia. Correctness not guaranteed
	// declare the path and initialize it with the current node
	// while current in predecessors:
	//		current = predecessors[current->i]
	//		insert current at the beginning of the path
	// return the path
}

bool findNode(MinQueue<Node*> &openSet, Node* node) {
	for (auto itr = openSet.begin(); itr!=openSet.end(); itr++){
		if(*itr == node)
			return true;
	}
	return false;
}

void aStar(Node& startPt, Node& goalPt, Node nodes[], std::size_t n, std::function<double(Node&)> heuristic) {
	
	//std::priority_queue<Node*> openSet;
	//new queue
	MinQueue<Node*> openSet;
	openSet.push(&startPt);

	// Stores the preceding node for each node on the most optimal path thus far
	std::unique_ptr<Node*[]> pathPredecessors(new Node*[n]);

	// Stores the distance of the most optimal path known
	std::unique_ptr<double[]> bestDistance(new double[n]);
	std::fill_n(bestDistance.get(), n, std::numeric_limits<double>::infinity());

	// Store the estimate of the optimal path if it goes through a certain node
	std::unique_ptr<double[]> estimatedDistance(new double[n]);
	std::fill_n(estimatedDistance.get(), n, std::numeric_limits<double>::infinity());

	estimatedDistance.get()[startPt.i] = heuristic(startPt);

	while (openSet.size() > 0) {
		Node* current = openSet.top();
		if (current == &goalPt) {
			// reconstruct path
		}
		openSet.pop();

		for (std::pair<Node*, double> successor : current->successors) {
			double distance = bestDistance[current->i] + successor.second;
			if (distance < bestDistance[successor.first->i]) {
				pathPredecessors[successor.first->i] = current;
				bestDistance[successor.first->i] = distance;
				estimatedDistance[successor.first->i] = distance + heuristic(*successor.first);
				// If the successor is not in openSet, then
				//	openSet.push(successor.first);
				if(findNode(openSet, successor.first))
					openSet.push(successor.first);
			}
		}
	}

}

int main(int argc, char** argv) {

}