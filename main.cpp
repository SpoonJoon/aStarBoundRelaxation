#include "astar.hpp"
#include <iostream>
#include <fstream>

int main(int argc, char** argv) {

	std::string input = argv[1];
	
    std::string temp;
    std::ifstream lim(input);
	getline(lim,temp);
	int dXsize = 0;
	int dYsize = 0;
	std::string x = "";
	std::string y = "";
	int flag = 0;
	for (auto i:temp){
		if(i == ' '){
			flag =1;
		} else if(i == '0'){
			x+=i;
		} else if(i =='1'){
			y+=i;
		}

	}
	dXsize = stoi(x);
	dYsize = stoi(y);
	bool nodes[dXsize][dYsize];
	for(int i = 0; i < dXsize;i++){
		for(int j = 0; j < dYsize;j++){
			getline(lim,temp);
			if(stoi(temp) == 0){
			nodes[i][j] = false;
			} else {
			nodes[i][j] = true;
			}
		
		}
		
	}

	const int xSize = 100;
	const int ySize = 50;

    Grid grid(xSize, ySize);
    for (int x = 0; x < xSize; x++) {
        for (int y = 0; y < ySize; y++) {
            grid.getCell(x, y)->blocked = nodes[x][y];
        }
    }
    std::vector<Coord> path;
    aStarSearch(grid, Coord{.x=0, .y=0}, Coord{.x=xSize-1, .y=ySize-1}, path);
    std::cout << "Search finished. Printing solution:" << std::endl;
    for (auto& c: path) {
        std::cout << '(' << c.x << ", " << c.y << ')' << std::endl;
    }
    std::cout << "Terminate\n";
	std::cout << "size=" << path.size() << std::endl;
    return 0;
}