#pragma once

#include <vector>
#include <utility>
#include "astar_graph.hpp"

int aStarSearch(Grid& inputGraph, Coord start, Coord end, std::vector<Coord>& bestPath);
