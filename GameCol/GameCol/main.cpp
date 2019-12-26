#include "Game.h"

void initScreen() {
	mvaddstr(9, 35, "*****************************************");
	mvaddstr(12, 40, "WOULD YOU LIKE TO PLAY A GAME?");
	mvaddstr(15, 35, "*****************************************");
}

int main(){
	initscr();
	initScreen();
	refresh();
	char choice = getch();
	if (choice == 'y') {
		noecho();
		clear();
		Game game("Map.txt");
		game.Play();
	}
}


