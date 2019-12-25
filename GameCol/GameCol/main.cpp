#include "Game.h"

int main(){
	initscr();
	printw("Would you like to play a game?\n");
	refresh();
	/*char choice = getch();
	if (choice == 'y') {
		noecho();
		clear();
		Game game("simple.txt");
		game.Play();
	}*/
	clear();
	Game game("Map.txt");
	game.Play();
}