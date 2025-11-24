#include "src/ui/ui.h"
#include "src/server/client.h"
#include<string>


const std::string WS_URL = "ws://localhost:5000";

int main(){
	initApp();
	initClient(WS_URL);
	std::string text;

	int ch = getch();
	while(ch != 27){
		if(ch == '\n'){
			// TODO: send message to server;
			drawChatwindow(text);
			sendMessage(text);
			text.clear();
		}else if(ch == KEY_BACKSPACE){
			if(!text.empty())
				text.pop_back();
		}else{
			text.push_back(ch);
		}
		drawInputWindow(text);
		ch = getch();
	}
	closeApp();
	closeConnection();
	return 0;
}
