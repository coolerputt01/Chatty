#include<iostream>
#include<ncurses.h>


int main(){
	initscr();
	cbreak();
	noecho();
	keypad(stdscr,TRUE);
	printw("Hello TUI");
	refresh();
	getch();
	endwin();
	
	return 0;
}
