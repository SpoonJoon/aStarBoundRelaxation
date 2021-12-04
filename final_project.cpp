#include "astar.hpp"
#include <iostream>
#include "maze.hpp"

int main() {
	const int xSize = 8;
	const int ySize = 6;
	bool blocked[ySize][xSize] = {
		{0, 1, 1, 0, 1, 0, 1, 0},
		{0, 0, 0, 0, 1, 0, 1, 0},
		{1, 1, 1, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 1, 1, 0},
		{0, 1, 1, 1, 1, 1, 1, 0},
		{0, 0, 0, 0, 1, 0, 0, 0}
	};
	Grid grid(problem::x, problem::y);
	for (int x = 0; x < problem::x; x++) {
		for (int y = 0; y < problem::y; y++) {
			grid.getCell(x, y)->blocked = problem::blocked[x][y];
		}
	}
	std::vector<Coord> path;
	int steps = aStarSearch(grid, Coord{.x=0, .y=0}, Coord{.x=problem::x - 1, .y=problem::y - 1}, path);
	std::cout << "Search finished. Printing solution:" << std::endl;
	for (auto& c : path) {
		std::cout << '(' << c.x << ", " << c.y << ')' << std::endl;
		if (problem::blocked[c.x][c.y]) {
			std::cout << "FAIL\n";
		}
	}
	std::cout << "Terminate\n";
	std::cout << "size=" << path.size() << std::endl;
	std::cout << "steps=" << steps << std::endl;

	return 0;
}
