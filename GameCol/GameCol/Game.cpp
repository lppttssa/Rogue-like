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
	//nodelay(stdscr, TRUE);
	char move;
	if ((move = getch()) == ERR) {
		move = 'n';
	}
	MoveInDirection(knight, move);
}

void Game::MoveMonster() {
	int i = 0;
	for (i; i < enemies.size(); i++) {
		if (!enemies[i].second) {
			enemies[i] = enemies.back();
			enemies.pop_back();
			i--;
		}
	}
	for (auto i = enemies.begin(); i != enemies.end(); i++) {
		char move = GetRandomMonsterMove();
		MoveInDirection(i->first, move);
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

void Game::MoveInDirection(std::shared_ptr<Character> &character, char direction) {
	std::pair<int, int> place = character->GetPos();
	switch (direction) {
	case 'w':
		TryMove(character, std::make_pair(place.first, place.second - 1), place);
		break;
	case 's':
		TryMove(character, std::make_pair(place.first, place.second + 1), place);
		break;
	case 'a':
		TryMove(character, std::make_pair(place.first - 1, place.second), place);
		break;
	case 'd':
		TryMove(character, std::make_pair(place.first + 1, place.second), place);
		break;
	default:
		printf("NO");
	}
}

void Game::TryMove(std::shared_ptr<Character>& character, std::pair<int, int> new_pos, std::pair<int, int> old_pos) {
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
	else if (way == 2){ //knight eats zombie and goes to zombie pos
		map.ChangeMap(old_pos.first, old_pos.second, std::dynamic_pointer_cast<GameObject>(std::make_shared<EmptySpace>(EmptySpace()))); //сюда просто пустое место
		for (auto i = enemies.begin(); i != enemies.end(); i++) {
			if (i->first == charToButtle) {
				i->second = false;
			}
		}
		mvaddch(old_pos.second, old_pos.first, '.');
		character->SetPos(new_pos.first, new_pos.second);

		map.ChangeMap(new_pos.first, new_pos.second, charToMove);
		mvaddch(new_pos.second, new_pos.first, charToMove->GetSym());
	}
	else if (way == 3) { //zombie goes to knight and knight kill zombie and stays on his position
		map.ChangeMap(old_pos.first, old_pos.second, std::dynamic_pointer_cast<GameObject>(std::make_shared<EmptySpace>(EmptySpace()))); //сюда просто пустое место
		if (charToMove->GetSym() == 'z') {
			ChangeEnemies(charToMove);
		}
		mvaddch(old_pos.second, old_pos.first, '.');
	}
	refresh();
}

void Game::ChangeEnemies(std::shared_ptr<GameObject> charToMove) {
	for (auto i = enemies.begin(); i != enemies.end(); i++) {
		if (i->first == charToMove) {
			i->second = false;
		}
	}
}