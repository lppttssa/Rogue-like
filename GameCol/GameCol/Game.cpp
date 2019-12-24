#include <random>
#include <time.h>
#include "Game.h"

Game::Game(std::string Map) :knightRotation('d') {
	map.CreateGame(Map, knight, enemies);
	map.Print();
}

void Game::Play() {
	while (true) {
		Move();
		MoveMonster();
		MoveFireballs();
	}
}

void Game::Move() {
	noecho();
	//nodelay(stdscr, TRUE);
	char move;
	if ((move = getch()) == ERR) {
		move = 'n';
	}
	else if (move != 'e'){
		knightRotation = move;
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

void Game::MoveFireballs() {
	int i = 0;
	for (i; i < fireballs.size(); i++) {
		if (!fireballs[i].second) {
			fireballs[i] = fireballs.back();
			fireballs.pop_back();
			i--;
		}
	}
	for (auto i = fireballs.begin(); i != fireballs.end(); i++) {
		MoveInDirection(i->first, std::dynamic_pointer_cast<Fireball>(i->first)->GetDir());//надо понять,куда идти фаерболлом
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
	std::pair<int, int> fireballPlace = { 0,0 };
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
	case 'e':
		fireballPlace = GetFireballPos();//надо добавить для шара направление
		if (std::make_pair(std::make_shared<Fireball>(Fireball(1, 2, '^', fireballPlace, knightRotation)), true).first->
			Collision(*map.GetObject(fireballPlace.first, fireballPlace.second).get()) == 1) {
			fireballs.push_back(std::make_pair(std::make_shared<Fireball>(Fireball(1, 2, '^', fireballPlace, knightRotation)), true));
			map.ChangeMap(fireballPlace.first, fireballPlace.second, fireballs.back().first);
			mvaddch(fireballPlace.second, fireballPlace.first, '^');
			refresh();
		}
		break;
	default:
		printf("NO");
		break;
	}
}

void Game::TryMove(std::shared_ptr<Character>& character, std::pair<int, int> new_pos, std::pair<int, int> old_pos) {
	std::shared_ptr<GameObject> charToMove = map.GetObject(old_pos.first, old_pos.second);
	std::shared_ptr<GameObject> charToButtle = map.GetObject(new_pos.first, new_pos.second);
	auto way = charToMove->Collision(*charToButtle.get());
	if (way == 1) { //меняем местами 2 объекта
		map.ChangeMap(old_pos.first, old_pos.second, charToButtle); //сюда просто пустое место
		mvaddch(old_pos.second, old_pos.first, charToButtle->GetSym());
		character->SetPos(new_pos.first, new_pos.second);

		map.ChangeMap(new_pos.first, new_pos.second, charToMove);
		mvaddch(new_pos.second, new_pos.first, charToMove->GetSym());

	}
	else if (way == 2){ //на позицию старого ставит ., передвигает мува в новую позицию
		map.ChangeMap(old_pos.first, old_pos.second, std::dynamic_pointer_cast<GameObject>(std::make_shared<EmptySpace>(EmptySpace()))); //сюда просто пустое место
		ChangeDanger(charToMove, charToButtle);
		mvaddch(old_pos.second, old_pos.first, '.');
		character->SetPos(new_pos.first, new_pos.second);

		map.ChangeMap(new_pos.first, new_pos.second, charToMove);
		mvaddch(new_pos.second, new_pos.first, charToMove->GetSym());
	}
	else if (way == 3) { //на старую позиция ставится точка и все
		map.ChangeMap(old_pos.first, old_pos.second, std::dynamic_pointer_cast<GameObject>(std::make_shared<EmptySpace>(EmptySpace()))); //сюда просто пустое место
		ChangeDanger(charToMove, charToButtle);
		mvaddch(old_pos.second, old_pos.first, '.');
	}
	else if (way == 4) { //на оба места нужно поставить .
		map.ChangeMap(old_pos.first, old_pos.second, std::dynamic_pointer_cast<GameObject>(std::make_shared<EmptySpace>(EmptySpace())));
		map.ChangeMap(new_pos.first, new_pos.second, std::dynamic_pointer_cast<GameObject>(std::make_shared<EmptySpace>(EmptySpace())));
		mvaddch(old_pos.second, old_pos.first, '.');
		mvaddch(new_pos.second, new_pos.first, '.');
		ChangeDanger(charToMove, charToButtle);
	}
	refresh();
	//ничего не происзодит, все стоят, как стояли
}

void Game::ChangeEnemies(std::shared_ptr<GameObject> charToMove) {
	for (auto i = enemies.begin(); i != enemies.end(); i++) {
		if (i->first == charToMove) {
			i->second = false;
		}
	}
}

void Game::ChangeFireballs(std::shared_ptr<GameObject> charToMove) {
	for (auto i = fireballs.begin(); i != fireballs.end(); i++) {
		if (i->first == charToMove) {
			i->second = false;
		}
	}
}
void Game::ChangeDanger(std::shared_ptr<GameObject> obj1, std::shared_ptr<GameObject> obj2) {
	if (obj1->GetSym() != '#' && obj1->GetSym() != 'P' && std::dynamic_pointer_cast<Character>(obj1)->GetHp() <= 0) {
		ChangeEnemies(obj1);
		ChangeFireballs(obj1);
	}
	if (obj2->GetSym() != '#' && obj2->GetSym() != 'P' && std::dynamic_pointer_cast<Character>(obj2)->GetHp() <= 0) {
		ChangeEnemies(obj2);
		ChangeFireballs(obj2);
	}
}

std::pair<int, int> Game::GetFireballPos() {
	auto place = knight->GetPos();
	switch (knightRotation) {
	case 'w':
		return std::make_pair(place.first, place.second - 1);
	case 's':
		return std::make_pair(place.first, place.second + 1);
	case 'a':
		return std::make_pair(place.first - 1, place.second);
	case 'd':
		return std::make_pair(place.first + 1, place.second);
	}
}