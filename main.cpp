#include "src/ui/ui.h"
#include<string>


int main(){
	initApp();
	std::string text;

	int ch = getch();
	while(ch != 27){
		if(ch == '\n'){
			// TODO: send message to server;
			drawChatwindow(text);
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
	return 0;
}
