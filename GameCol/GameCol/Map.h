#pragma once
#pragma comment(lib, "pdcurses.lib")
#include <vector>
#include <memory>
#include <string>
#include <map>
#include "GameObject.h"
#include "Wall.h"
#include "EmptySpace.h"
#include "Knight.h"
#include "Princess.h"
#include "Enemy.h"
#include "curses.h"

class Map {
	std::vector<std::vector<std::shared_ptr<GameObject>>> map = 
		std::vector<std::vector<std::shared_ptr<GameObject>>> (33);

public:
	Map();

	void CreateGame(std::string, std::shared_ptr<Character>&, std::vector<std::pair<std::shared_ptr<Character>, bool>>&);
	void Print();
	std::shared_ptr<GameObject> GetObject(int, int);
	void ChangeMap(int, int, std::shared_ptr<GameObject>);
};
