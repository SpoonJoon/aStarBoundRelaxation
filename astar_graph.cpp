#include "astar_graph.hpp"

Grid::Grid(unsigned int xSize, unsigned int ySize) : xSize(xSize), ySize(ySize), cells(new Cell[xSize * ySize]) { }

Cell* Grid::getCell(unsigned int x, unsigned int y) {
	return &cells[x + y * xSize];
}

bool Grid::valid(const Coord& c) {
	return c.x < xSize && c.y < ySize;
}

bool Coord::operator==(const Coord& other) {
	return other.x == x && other.y == y;
}