#include <random>
#include <thread>       
#include <chrono>
#include "Game.h"
#include "Knight.h"

Game::Game(std::string Map) :knightRotation('d') {
	map.CreateGame(Map, knight, enemies);
	map.Print();
}

void Game::Play() {	
	InitScreen();
	while (true) {
		Move();
		MoveMonster();
		MoveFireballs();
	}
}

void Game::Move() {
	noecho();
	
	char move;
	if ((move = getch()) == ERR) {
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
	else {
		if (move != 'e') {
			knightRotation = move;
		}

		MoveInDirection(knight, move); 
		refresh();
	}

}
	void Game::MoveMonster() { 

	int i = 0;
	for (i; i < enemies.size();) {
		if (!enemies[i].second) {
			enemies.erase(enemies.begin() + i);
		}
		else {
			i++;
		}
	}
	for (auto i = enemies.begin(); i != enemies.end(); i++) {
		char move = GetRandomMonsterMove();
		MoveInDirection(i->first, move);
		if (std::dynamic_pointer_cast<GameObject>(i->first)->GetSym() == 'd' && move != 'n') {
			static std::default_random_engine rand(time(NULL));
			std::uniform_int_distribution<int> r(0, 3);
			if (r(rand) == 1) {
				CreateFireball(move, i->first);
			}
		}
	}
}

	void Game::MoveFireballs() {
	int i = 0;
	for (i; i < fireballs.size();) {
		if (!fireballs[i].second) {
			fireballs.erase(fireballs.begin() + i);
		}
		else {
			i++;
		}
	}
	for (auto i = fireballs.begin(); i != fireballs.end(); i++) {
		MoveInDirection(i->first, std::dynamic_pointer_cast<Fireball>(i->first)->GetDir());
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
	case 'e':
		CreateFireball(knightRotation, knight);
		break;
	default:
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
	if (obj1->GetSym() != '#' && obj1->GetSym() != 'P' && obj1->GetSym() != '+' && std::dynamic_pointer_cast<Character>(obj1)->GetHp() <= 0) {
		ChangeEnemies(obj1);
		ChangeFireballs(obj1);
	}
	if (obj2->GetSym() != '#' && obj2->GetSym() != 'P' && obj2->GetSym() != '+' && std::dynamic_pointer_cast<Character>(obj2)->GetHp() <= 0) {
		ChangeEnemies(obj2);
		ChangeFireballs(obj2);
	}
}

std::pair<int, int> Game::GetFireballPos(char direction, std::shared_ptr<Character>& character) {
	auto place = character->GetPos();
	switch (direction) {
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

void Game::CreateFireball(char direction, std::shared_ptr<Character>& character) {
	auto fireballPlace = GetFireballPos(direction, character);//надо добавить для шара направление
	if (std::make_pair(std::make_shared<Fireball>(Fireball(1, 2, '^', fireballPlace, direction)), true).first->
		Collision(*map.GetObject(fireballPlace.first, fireballPlace.second).get()) == 1) {
		fireballs.push_back(std::make_pair(std::make_shared<Fireball>(Fireball(1, 2, '^', fireballPlace, direction)), true));
		map.ChangeMap(fireballPlace.first, fireballPlace.second, fireballs.back().first);
		mvaddch(fireballPlace.second, fireballPlace.first, '^');
		refresh();
	}
}

Fireball Game::CreateFireball(std::string source, int x, int y, int dir) {
	std::ifstream file;
	std::vector<std::string> fireball;

	file.open(source);
	if (file.fail()) {
		exit(1);
	}

	std::string line;

	while (getline(file, line)) {
		fireball.push_back(line);
	}
	return Fireball(atoi(fireball[0].c_str()), atoi(fireball[1].c_str()), fireball[2][0], { x, y }, dir);
}

void Game::InitScreen() {
	std::ifstream file;
	mvaddstr(0, map.GetSize() + 15, "WELLCOME TO ROGUE-LIKE GAME!!");
	mvaddstr(1, map.GetSize() + 4, "YOUR MAIN GOAL IS TO REACH YOUR BEAUTIFULL PRINCESS!!");
	mvaddstr(2, map.GetSize() + 23, "Characters:");
	mvaddstr(3, map.GetSize() + 19, "hp:");
	mvaddstr(3, map.GetSize() + 33, "damage:");

	mvaddstr(4, map.GetSize() + 10, "Knight:");
	mvaddstr(4, map.GetSize() + 19, std::to_string(knight->GetHp()).c_str());
	mvaddstr(4, map.GetSize() + 33, std::to_string(knight->GetDamage()).c_str());

	mvaddstr(5, map.GetSize() + 10, "Zombie:");
	file.open("Zombie.txt");
	std::string line;
	getline(file, line);
	mvaddstr(5, map.GetSize() + 19, line.c_str());
	getline(file, line);
	mvaddstr(5, map.GetSize() + 33, line.c_str());
	file.close();

	mvaddstr(6, map.GetSize() + 10, "Dragon:");
	file.open("Dragon.txt");
	getline(file, line);
	mvaddstr(6, map.GetSize() + 19, line.c_str());
	getline(file, line);
	mvaddstr(6, map.GetSize() + 33, line.c_str());
	file.close();
	refresh();
}
