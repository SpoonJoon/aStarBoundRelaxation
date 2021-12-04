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

// Heuristic function. Currently uses Manhattan Distance (movement in 4 directions)
// If we allow diagonal directions, then this must update
static unsigned int h(Coord& end, Coord& other) {
	return (std::max(other.x, end.x) - std::min(other.x, end.x)) + (std::max(other.y, end.y) - std::min(other.y, end.y));
}

static bool evalCell(Grid& inputGraph, Coord& current, Coord& neighbor, Coord& end) {
	if (inputGraph.valid(neighbor)) {
		Cell& c = *inputGraph.getCell(current);
		Cell& n = *inputGraph.getCell(neighbor);
		if (!n.blocked) {
			// Assuming each grid movement is 1 distance unit and movement is only in 4 directions (up down left right)
			double newDistance = c.distanceFromStart + 1.0;
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

void aStarSearch(Grid& inputGraph, Coord start, Coord end, std::vector<Coord>& bestPath) {

	inputGraph.getCell(start)->distanceFromStart = 0;
	inputGraph.getCell(start)->estDistanceToEnd = h(end, start);

	// This vector should be changed to a priority queue for better performance
	std::vector<Coord> openSet;
	openSet.push_back(start);

	while (!openSet.empty()) {
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

		openSet.erase(std::remove(openSet.begin(), openSet.end(), c), openSet.end());

		const static int xOffsets[] = {-1, 0, 0, 1};
		const static int yOffsets[] = {0, -1, 1, 0};
		for (int i = 0; i < 4; i++) {
			Coord neighbor {.x = c.x + xOffsets[i], .y = c.y + yOffsets[i]};
			if (evalCell(inputGraph, c, neighbor, end)) {
				if (std::find(openSet.begin(), openSet.end(), neighbor) == openSet.end()) {
					openSet.push_back(neighbor);
				}
			}
		}
	}

}
