#include "src/ui/ui.hpp"
#include "src/server/client.h"
#include <ncurses.h>
#include "src/messages/message.hpp"
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
	Message m;
	m.text = welcomeText;
	m.time = "";
	m.username = "";
	drawChatwindow(m);
	chatLoop();

	closeApp();
	return 0;
}
