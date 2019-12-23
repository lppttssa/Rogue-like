#pragma once
#include <vector>
#include <map>
#include <chrono>
#include <ctime>
#include "Map.h"

class Game {
	Map map;
	std::shared_ptr<Character> knight;
	std::vector<std::pair<std::shared_ptr<Character>, bool>> enemies;
	std::vector<std::pair<std::shared_ptr<Character>, bool>> fireballs;
	char knightRotation;
	std::pair<int, int> GetFireballPos();
	void MoveFireballs();
	void ChangeFireballs(std::shared_ptr<GameObject>);
	void ChangeEnemies(std::shared_ptr<GameObject>);
public:
	Game(std::string);
	void Play();
	void Move();
	void MoveMonster();
	void MoveInDirection(std::shared_ptr<Character>&, char);
	void TryMove(std::shared_ptr<Character>&, std::pair<int, int>, std::pair<int, int>);
	char GetRandomMonsterMove();
};
