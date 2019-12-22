#include <fstream>
#include "Map.h"

Map::Map() {};

void Map::CreateGame(std::string m, std::shared_ptr<Character> &knight, std::vector<std::shared_ptr<Character>>& enemies) {
	std::ifstream file;

	file.open(m);
	if (file.fail()) {
		exit(1);
	}

	std::string line;
	int count = 0;
	while (getline(file, line)) {
		for (int i = 0; i < line.size(); i++) {
			switch (line[i]) {
			case '#':
				map[count].push_back(std::dynamic_pointer_cast<GameObject>(std::make_shared<Wall>(Wall())));
				break;
			case '.':
				map[count].push_back(std::dynamic_pointer_cast<GameObject>(std::make_shared<EmptySpace>(EmptySpace())));
				break;
			case '@':
				knight = std::make_shared<Knight>(Knight(12, 6, '@', {i, count}));
				map[count].push_back(std::dynamic_pointer_cast<GameObject>(knight));
				break;
			case 'P':
				map[count].push_back(std::dynamic_pointer_cast<GameObject>(std::make_shared<Princess>(Princess())));
				break;
			case 'z':
				enemies.push_back(std::make_shared<Enemy>(Enemy(6, 3, 'z', { i, count })));
				map[count].push_back(std::dynamic_pointer_cast<GameObject>(enemies.back()));
				break;
			}	
		}
		count++;
	}
}

void Map::Print() {
	initscr();
	for (auto i : map) {
		for (auto j : i) {
			printw("%c", j->GetSym());
		}
		printw("\n");
	}
	refresh();               //print any changes done to the standard screen

	echo();
	getch();                 //Wait for user input
	endwin();
}

std::shared_ptr<GameObject> Map::GetObject(int x, int y) {
	return map[y][x];
}

void Map::ChangeMap(int x, int y, std::shared_ptr<GameObject> sym) {
	map[y][x] = sym;
}