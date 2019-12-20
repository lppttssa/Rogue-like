#pragma once
#include "Map.h"

class Game {
	Map map;
	std::shared_ptr<Character> knight;
public:
	Game(std::string);
	void Play();
	void Move();
	void MoveInDirection(std::shared_ptr<Character>&, char);
	void TryMove(std::shared_ptr<Character>&, std::pair<int, int>, std::pair<int, int>);
};
