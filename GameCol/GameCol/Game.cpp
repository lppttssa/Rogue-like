#include "Game.h"

Game::Game(std::string Map) {
	map.CreateGame(Map, knight);
	map.Print();
}

void Game::Play() {
	while (true) {
		Move();
	}
}

void Game::Move() {
	noecho();
	char move = getch();
	MoveInDirection(knight, move);
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
	if (charToMove->Collision(*charToButtle.get())) {
		map.ChangeMap(old_pos.first, old_pos.second, charToButtle); //сюда просто пустое место
		mvaddch(old_pos.second, old_pos.first, '.');
		character->SetPos(new_pos.first, new_pos.second);

		map.ChangeMap(new_pos.first, new_pos.second, charToMove);
		mvaddch(new_pos.second, new_pos.first, charToMove->GetSym());

		refresh();
	}
}