#include<string>
#include<vector>
#include<ncurses.h>
#include "../user/user.h"

#pragma once

enum class AuthState {
    SignIn,
    SignUp
};

AuthState authState = AuthState::SignIn;

WINDOW* chatWindow;
WINDOW* inputWindow;
WINDOW* authWindow;
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
    //chatWindow = newwin(height - 3,width,3,0);
    //inputWindow = newwin(3,width,height-3,0);
    authWindow = newwin(height,width,0,0);
    mvprintw(1,1,"Chatty");
    //box(chatWindow,0,0);
    //box(inputWindow,0,0);
    box(authWindow,0,0);
    wrefresh(inputWindow);
    wrefresh(authWindow);
};

std::string getInput(WINDOW* win, int y, int x, bool hide = false) {
    std::string input;
    int ch;

    while ((ch = wgetch(win)) != '\n') {
        if (ch == KEY_BACKSPACE || ch == 127) {
            if (!input.empty()) {
                input.pop_back();
                mvwdelch(win, y, x + input.size());
            }
        } else if (isprint(ch)) {
            input.push_back(ch);
            mvwprintw(win, y, x, "%s", 
                hide ? std::string(input.size(), '*').c_str() : input.c_str()
            );
        }
        wrefresh(win);
    }

    return input;
}


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
    int row = 1;
    for(size_t i = start; i < texts.size(); i++){
        mvwprintw(chatWindow, row++, 1, "%s", texts[i].c_str());
    }
    wrefresh(chatWindow);
};
void drawSignIn() {
    werase(authWindow);
    box(authWindow, 0, 0);

    mvwprintw(authWindow, 2, 2, "Chatty - Sign In");
    mvwprintw(authWindow, 4, 2, "Username: ");
    mvwprintw(authWindow, 5, 2, "Password: ");
    mvwprintw(authWindow, 7, 2, "[ENTER] Login");
    mvwprintw(authWindow, 9, 2, "[TAB] Switch to Sign Up");

    wrefresh(authWindow);
}
void drawSignUp() {
    werase(authWindow);
    box(authWindow, 0, 0);

    mvwprintw(authWindow, 2, 2, "Chatty - Sign Up");
    mvwprintw(authWindow, 4, 2, "Username: ");
    mvwprintw(authWindow, 5, 2, "Password: ");
    mvwprintw(authWindow, 6, 2, "Confirm Password: ");
    mvwprintw(authWindow, 9, 2, "[ENTER] Create Account");
    mvwprintw(authWindow, 11, 2, "[TAB] Switch to Sign In");

    wrefresh(authWindow);
}

void authLoop() {
    int ch;

    while (true) {
        if (authState == AuthState::SignIn) {
            drawSignIn();
        } else {
            drawSignUp();
        }

        mvwprintw(authWindow, 4, 12, "");
        std::string username = getInput(authWindow, 4, 12);

        mvwprintw(authWindow, 5, 12, "");
        std::string password = getInput(authWindow, 5, 12, true);

        if (authState == AuthState::SignUp) {
            mvwprintw(authWindow, 6, 20, "");
            std::string confirm = getInput(authWindow, 6, 20, true);

            if (password != confirm) {
                mvwprintw(authWindow, 13, 2, "Passwords do not match!");
                wrefresh(authWindow);
                napms(1000);
                continue;
            }
        }

        ch = wgetch(authWindow);

        if (ch == '\t') {
            authState = (authState == AuthState::SignIn) 
                        ? AuthState::SignUp 
                        : AuthState::SignIn;
            continue;
        }
        User user(username,password);
        if (ch == '\n') {
            if (authState == AuthState::SignIn) {
                return;
            } else {
                user.createNewUser();
                return;
            }
        }
    }
}

void drawInputWindow(const std::string& text){
    werase(inputWindow);
    box(inputWindow,0,0);
    mvwprintw(inputWindow, 1, 1, "%s", text.c_str());
    wrefresh(inputWindow);
};