#include "astar.hpp"
#include <iostream>

int main() {
    const int xSize = 8;
    const int ySize = 4;
    bool blocked[ySize][xSize] = {
        {0, 0, 0, 0, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 1, 1, 1},
        {1, 1, 0, 1, 1, 0, 0, 0},
        {1, 0, 0, 0, 0, 0, 0, 0}
    };
    Grid grid(xSize, ySize);
    for (int x = 0; x < xSize; x++) {
        for (int y = 0; y < ySize; y++) {
            grid.getCell(x, y)->blocked = blocked[y][x];
        }
    }
    std::vector<Coord> path;
    aStarSearch(grid, Coord{.x=0, .y=0}, Coord{.x=7, .y=3}, path);
    std::cout << "Search finished. Printing solution:" << std::endl;
    for (auto& c: path) {
        std::cout << '(' << c.x << ", " << c.y << ')' << std::endl;
    }
    std::cout << "Terminate\n";
    return 0;
}