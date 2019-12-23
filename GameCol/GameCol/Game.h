#pragma once
#include <vector>
#include <map>
#include "Map.h"

class Game {
	Map map;
	std::shared_ptr<Character> knight;
	std::vector<std::shared_ptr<Character>> enemies;
	//std::map<std::shared_ptr<Character>, bool> enemies;
public:
	Game(std::string);
	void Play();
	void Move();
	void MoveMonster();
	void MoveInDirection(std::shared_ptr<Character>&, char, int i = 0);
	void TryMove(std::shared_ptr<Character>&, std::pair<int, int>, std::pair<int, int>, int i = 0);
	char GetRandomMonsterMove();
};
