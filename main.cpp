#include "src/ui/ui.hpp"
#include "src/server/client.h"
#include <ncurses.h>
#include<string>

int main(){
	initApp();
	authLoop();

	werase(authWindow);
    wrefresh(authWindow);
    delwin(authWindow);
	authWindow = nullptr;
	clear();
	refresh();


	std::string welcomeText = "Welcome to Chatty, " + user->username;
	drawChatwindow(welcomeText);
	chatLoop();

	closeApp();
	return 0;
}
