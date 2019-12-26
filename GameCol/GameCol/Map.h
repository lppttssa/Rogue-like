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
#include "Fireball.h"
#include "curses.h"
#include "AidKit.h"

class Map {
	std::vector<std::vector<std::shared_ptr<GameObject>>> map = 
		std::vector<std::vector<std::shared_ptr<GameObject>>> (1);
	Enemy CreateEnemy(std::string, int, int);
	Knight CreateKnight(std::string, int, int);
	AidKit CreateAidKit(std::string);
public:
	Map();
	int GetSize();
	void CreateGame(std::string, std::shared_ptr<Character>&, std::vector<std::pair<std::shared_ptr<Character>, bool>>&);
	void Print();
	std::shared_ptr<GameObject> GetObject(int, int);
	void ChangeMap(int, int, std::shared_ptr<GameObject>);
};
