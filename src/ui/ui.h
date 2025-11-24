#include<string>
#include<vector>
#include<ncurses.h>

#pragma once


WINDOW* chatWindow;
WINDOW* inputWindow;
std::vector<std::string> texts;

void initApp(){
    initscr();
    cbreak();
	noecho();
    curs_set(1);
    ESCDELAY = 5;
    start_color();
	keypad(stdscr,TRUE);
    int height,width;
    getmaxyx(stdscr,height,width);
    chatWindow = newwin(height - 5,width,3,0);
    inputWindow = newwin(3,width,height-3,0);
    mvprintw(1,1,"Chatty");
    box(chatWindow,0,0);
    box(inputWindow,0,0);
    wrefresh(inputWindow);
};
void closeApp(){
    endwin();
};
void drawChatwindow(const std::string& text){
    texts.push_back(text);
    werase(chatWindow);
    box(chatWindow,0,0);

    int maxRows = getmaxy(chatWindow) - 2;
    int start = 0;

    if(texts.size() > maxRows){
        start = texts.size() - maxRows;
    }
    int row = 2;
    for(size_t i = start; i < texts.size(); i++){
        mvwprintw(chatWindow, row++, 1, "%s", texts[i].c_str());
    }
    wrefresh(chatWindow);
};

void drawInputWindow(const std::string& text){
    werase(inputWindow);
    box(inputWindow,0,0);
    mvwprintw(inputWindow, 1, 1, "%s", text.c_str());
    wrefresh(inputWindow);
};