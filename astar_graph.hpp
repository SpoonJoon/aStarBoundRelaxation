#pragma once

#include <memory>
#include <utility>
#include <limits>

struct Coord {
	unsigned int x;
	unsigned int y;
	bool operator==(const Coord&);
};

struct Cell {
	bool blocked;
	Coord predecessor;
	double distanceFromStart = std::numeric_limits<double>::infinity();
	double estDistanceToEnd = std::numeric_limits<double>::infinity();
};

class Grid {
private:
	std::unique_ptr<Cell[]> cells;
	unsigned int xSize;
	unsigned int ySize;
public:
	Grid(unsigned int xSize, unsigned int ySize);
	Cell* getCell(unsigned int x, unsigned int y);
	inline Cell* getCell(Coord c) { return getCell(c.x, c.y); }
	bool valid(const Coord& c);
};
