#include <fstream>
#include "Map.h"

Map::Map() {};

void Map::CreateGame(std::string m, std::shared_ptr<Character> &knight, std::vector<std::pair<std::shared_ptr<Character>, bool>>& enemies) {
	std::ifstream file;

	file.open(m);
	if (file.fail()) {
		exit(1);
	}

	std::string line;
	int count = 0;
	bool init = false;
	while (getline(file, line)) {
		if (!init) {
			map.resize(line.length());
			!init;
		}
		for (int i = 0; i < line.size(); i++) {
			switch (line[i]) {
			case '#':
				map[count].push_back(std::dynamic_pointer_cast<GameObject>(std::make_shared<Wall>(Wall())));
				break;
			case '.':
				map[count].push_back(std::dynamic_pointer_cast<GameObject>(std::make_shared<EmptySpace>(EmptySpace())));
				break;
			case '@':
				knight = std::make_shared<Knight>(CreateKnight("Knight.txt", i, count));
				map[count].push_back(std::dynamic_pointer_cast<GameObject>(knight));
				break;
			case 'P':
				map[count].push_back(std::dynamic_pointer_cast<GameObject>(std::make_shared<Princess>(Princess())));
				break;
			case 'z':
				enemies.push_back(std::make_pair(std::make_shared<Enemy>(CreateEnemy("Zombie.txt", i, count)), true));
				map[count].push_back(std::dynamic_pointer_cast<GameObject>(enemies.back().first));
				break;
			case 'd':
				enemies.push_back(std::make_pair(std::make_shared<Enemy>(CreateEnemy("Dragon.txt", i, count)), true));
				map[count].push_back(std::dynamic_pointer_cast<GameObject>(enemies.back().first));
				break;
			case '+':
				map[count].push_back(std::dynamic_pointer_cast<GameObject>(std::make_shared<AidKit>(CreateAidKit("AidKit.txt"))));
				break;
			}	
		}
		count++;
	}
	
}

Knight Map::CreateKnight(std::string source, int x, int y) {
	std::ifstream file;
	std::vector<std::string> knight;

	file.open(source);
	if (file.fail()) {
		exit(1);
	}

	std::string line;

	while (getline(file, line)) {
		knight.push_back(line);
	}
	return Knight(atoi(knight[0].c_str()), atoi(knight[1].c_str()), atoi(knight[2].c_str()), knight[3][0], {x, y});
}

Enemy Map::CreateEnemy(std::string source, int x, int y) {
	std::ifstream file;
	std::vector<std::string> enemy;

	file.open(source);
	if (file.fail()) {
		exit(1);
	}

	std::string line;

	while (getline(file, line)) {
		enemy.push_back(line);
	}
	return Enemy(atoi(enemy[0].c_str()), atoi(enemy[1].c_str()), enemy[2][0], { x, y });
}

AidKit Map::CreateAidKit(std::string source) {
	std::ifstream file;

	file.open(source);
	if (file.fail()) {
		exit(1);
	}

	std::string line;
	getline(file, line); 
	return AidKit(atoi(line.c_str()));

}

void Map::Print() {
	initscr();
	nodelay(stdscr, TRUE);
	for (auto i : map) {
		for (auto j : i) {
			printw("%c", j->GetSym());
		}
		printw("\n");
	}
	refresh();             
}

std::shared_ptr<GameObject> Map::GetObject(int x, int y) {
	return map[y][x];
}

void Map::ChangeMap(int x, int y, std::shared_ptr<GameObject> sym) {
	map[y][x] = sym;
}

int Map::GetSize() {
	return map.size();
}