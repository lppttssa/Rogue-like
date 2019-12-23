#include <random>
#include <time.h>
#include "Game.h"

Game::Game(std::string Map) {
	map.CreateGame(Map, knight, enemies);
	map.Print();
}

void Game::Play() {
	while (true) {
		Move();
		MoveMonster();
	}
}

void Game::Move() {
	noecho();
	char move = getch();
	MoveInDirection(knight, move);
}

void Game::MoveMonster() {
	int i;
	for (i = 0; i < enemies.size(); i++) {
		//char move = GetRandomMonsterMove();
		MoveInDirection(enemies[i], 'a',  i);
	}
}

char Game::GetRandomMonsterMove() {
	static std::default_random_engine rand(time(NULL));
	std::uniform_int_distribution<int> r(0, 4);
	int move = r(rand);
	switch (move) {
	case 0:
		return 'd';
	case 1:
		return 'a';
	case 2:
		return 's';
	case 3:
		return 'w';
	default:
		return 'n';
	}
}

void Game::MoveInDirection(std::shared_ptr<Character> &character, char direction, int i) {
	std::pair<int, int> place = character->GetPos();
	switch (direction) {
	case 'w':
		TryMove(character, std::make_pair(place.first, place.second - 1), place, i);
		break;
	case 's':
		TryMove(character, std::make_pair(place.first, place.second + 1), place, i);
		break;
	case 'a':
		TryMove(character, std::make_pair(place.first - 1, place.second), place, i);
		break;
	case 'd':
		TryMove(character, std::make_pair(place.first + 1, place.second), place, i);
		break;
	default:
		printf("NO");
	}
}

void Game::TryMove(std::shared_ptr<Character>& character, std::pair<int, int> new_pos, std::pair<int, int> old_pos, int i) {
	std::shared_ptr<GameObject> charToMove = map.GetObject(old_pos.first, old_pos.second);
	std::shared_ptr<GameObject> charToButtle = map.GetObject(new_pos.first, new_pos.second);
	auto way = charToMove->Collision(*charToButtle.get());
	if (way == 1) {
		map.ChangeMap(old_pos.first, old_pos.second, charToButtle); //сюда просто пустое место
		mvaddch(old_pos.second, old_pos.first, charToButtle->GetSym());
		character->SetPos(new_pos.first, new_pos.second);

		map.ChangeMap(new_pos.first, new_pos.second, charToMove);
		mvaddch(new_pos.second, new_pos.first, charToMove->GetSym());

	}
	else if (way == 2){ //knight vs zombie
		map.ChangeMap(old_pos.first, old_pos.second, std::dynamic_pointer_cast<GameObject>(std::make_shared<EmptySpace>(EmptySpace()))); //сюда просто пустое место
		//enemies.erase(enemies.begin() + i);
		mvaddch(old_pos.second, old_pos.first, '.');
		character->SetPos(new_pos.first, new_pos.second);

		map.ChangeMap(new_pos.first, new_pos.second, charToMove);
		mvaddch(new_pos.second, new_pos.first, charToMove->GetSym());
	}
	else if (way == 3) {
		map.ChangeMap(old_pos.first, old_pos.second, std::dynamic_pointer_cast<GameObject>(std::make_shared<EmptySpace>(EmptySpace()))); //сюда просто пустое место
		enemies.erase(enemies.begin() + i);
		mvaddch(old_pos.second, old_pos.first, '.');
	}
	refresh();
}