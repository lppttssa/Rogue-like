#pragma once
#include <vector>
#include "Map.h"

class Game {
	Map map;
	std::shared_ptr<Character> knight;
	std::vector<std::shared_ptr<Character>> enemies;
public:
	Game(std::string);
	void Play();
	void Move();
	void MoveMonster();
	void MoveInDirection(std::shared_ptr<Character>&, char);
	void TryMove(std::shared_ptr<Character>&, std::pair<int, int>, std::pair<int, int>);
	char GetRandomMonsterMove();
};
