#include "astar.hpp"

#include <algorithm>
#include <cmath>
#include <iostream>

static void reconstructPath(std::vector<Coord>& bestPath, Grid& inputGraph, const Coord& start, Coord end) {
	while (!(end == start)) {
		bestPath.push_back(end);
		end = inputGraph.getCell(end)->predecessor;
	}
	bestPath.push_back(start);
}

static unsigned int h(Coord& end, Coord& other) {
#ifdef CONSTANT_HEURISTIC
	return 0;
#else
	unsigned int dy = (std::max(other.y, end.y) - std::min(other.y, end.y));
	unsigned int dx = (std::max(other.x, end.x) - std::min(other.x, end.x));
	double e = 1.0; // Adjust value to relax or tighten bound
	return 1.0 * ((dx + dy) + (sqrt(2.0) - 2.0) * std::min(dy, dx));
#endif
}

static bool evalCell(Grid& inputGraph, Coord& current, Coord& neighbor, Coord& end, double dist) {
	if (inputGraph.valid(neighbor)) {
		Cell& c = *inputGraph.getCell(current);
		Cell& n = *inputGraph.getCell(neighbor);
		if (!n.blocked) {
			// Assuming each grid movement is 1 distance unit and movement is only in 4 directions (up down left right)
			double newDistance = c.distanceFromStart + dist;
			if (newDistance < n.distanceFromStart) {
				n.predecessor = current;
				n.distanceFromStart = newDistance;
				n.estDistanceToEnd = newDistance + h(end, neighbor);
				return true;
			}
		}
	}
	return false;
}

int aStarSearch(Grid& inputGraph, Coord start, Coord end, std::vector<Coord>& bestPath) {

	int nExpanded = 0;

	inputGraph.getCell(start)->distanceFromStart = 0;
	inputGraph.getCell(start)->estDistanceToEnd = h(end, start);

	// This vector should be changed to a priority queue for better performance
	std::vector<Coord> openSet;
	openSet.push_back(start);

	while (!openSet.empty()) {
		nExpanded++;
		// Find node with minimum estDistanceToEnd: can be done faster with a min heap
		Coord& c = openSet.front();
		for (auto& node : openSet) {
			if (inputGraph.getCell(node)->estDistanceToEnd < inputGraph.getCell(c)->estDistanceToEnd) {
				c = node;
			}
		}

		if (c == end) {
			reconstructPath(bestPath, inputGraph, start, end);
			break;
		}

		for (auto it = openSet.begin(); it != openSet.end(); it++) {
			if (*it == c) {
				openSet.erase(it);
				break;
			}
		}

		const static int xOffsets[] = {-1, 0, 0, 1, -1, -1, 1, 1};
		const static int yOffsets[] = {0, -1, 1, 0, 1, -1, 1, -1};
		for (int i = 0; i < 8; i++) {
			Coord neighbor {.x = c.x + xOffsets[i], .y = c.y + yOffsets[i]};
			// Diagonal distance is sqrt(2) and horizontal/vertical distance is 1
			if (evalCell(inputGraph, c, neighbor, end, (i >= 4) ? sqrt(2.0) : 1.0)) {
				if (std::find(openSet.begin(), openSet.end(), neighbor) == openSet.end()) {
					openSet.push_back(neighbor);
				}
			}
		}
	}

	return nExpanded;

}
