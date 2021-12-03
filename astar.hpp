#pragma once

#include <vector>
#include <utility>
#include "astar_graph.hpp"

void aStarSearch(Grid& inputGraph, Coord start, Coord end, std::vector<Coord>& bestPath);
