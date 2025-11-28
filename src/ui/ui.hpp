#pragma once
#include <string>
#include <cctype>
#include <vector>
#include <ncurses.h>
#include "../user/user.h"


//AUth state mananger
enum class AuthState : short {
    SignIn,
    SignUp,
    LoggedIn
};

AuthState authState = AuthState::SignIn;


//define windows
WINDOW* chatWindow;
WINDOW* inputWindow;
WINDOW* authWindow;

//Keep all chat texts
std::vector<std::string> texts;

//Manage special inputs
struct alignas(8) InputResult {
    std::string text;
    bool submitted;
    bool escapeKey;
    bool tabKey;
};

//Start TUI
void initApp() {
    initscr();
    cbreak();
    noecho();
    curs_set(1);
    ESCDELAY = 5;
    start_color();
    keypad(stdscr, TRUE);
    int height, width;
    getmaxyx(stdscr, height, width);
    chatWindow = newwin(height - 3, width, 3, 0);
    inputWindow = newwin(3, width, height - 3, 0);
    authWindow = newwin(height, width, 0, 0);
    mvprintw(1, 1, "Chatty");
    box(chatWindow, 0, 0);
    box(inputWindow, 0, 0);
    box(authWindow, 0, 0);
    wrefresh(inputWindow);
    wrefresh(authWindow);
}


//Another inout helper
InputResult getInput(WINDOW* win, int y, int x, bool hide = false) {
    std::string input;
    int ch;
    wmove(win, y, x);
    wrefresh(win);
    while (true) {
        ch = wgetch(win);
        if (ch == ERR) continue;
        if (ch == 27) return {input, false, true, false};
        if (ch == '\t') return {input, false, false, true};
        if (ch == '\n') return {input, true, false, false};
        if (ch == KEY_BACKSPACE || ch == 127) {
            if (!input.empty()) {
                input.pop_back();
                mvwaddch(win, y, x + input.size(), ' ');
                wmove(win, y, x + input.size());
            }
        } else if (isprint(ch)) {
            input.push_back(ch);
            mvwaddch(win, y, x + input.size() - 1, hide ? '*' : ch);
        }
        wrefresh(win);
    }
}

//Close app
void closeApp() {
    endwin();
}

//chat TUI loop
void drawChatwindow(const std::string& text) {
    texts.push_back(text);
    werase(chatWindow);
    box(chatWindow, 0, 0);
    int maxRows = getmaxy(chatWindow) - 2;
    int start = texts.size() > maxRows ? texts.size() - maxRows : 0;
    int row = 1;
    for (size_t i = start; i < texts.size(); i++)
        mvwprintw(chatWindow, row++, 1, "%s", texts[i].c_str());
    wrefresh(chatWindow);
}

//draw signin
void drawSignIn() {
    werase(authWindow);
    box(authWindow, 0, 0);
    mvwprintw(authWindow, 2, 2, "Chatty - Sign In");
    mvwprintw(authWindow, 4, 2, "Username: ");
    mvwprintw(authWindow, 5, 2, "Password: ");
    mvwprintw(authWindow, 7, 2, "[-ENTER-] Login");
    mvwprintw(authWindow, 10, 2, "[-TAB-] Switch to Sign Up");
    wrefresh(authWindow);
}

//drawsignup
void drawSignUp() {
    werase(authWindow);
    box(authWindow, 0, 0);
    mvwprintw(authWindow, 2, 2, "Chatty - Sign Up");
    mvwprintw(authWindow, 4, 2, "Username: ");
    mvwprintw(authWindow, 5, 2, "Password: ");
    mvwprintw(authWindow, 6, 2, "Confirm Password: ");
    mvwprintw(authWindow, 9, 2, "[-ENTER-] Create Account");
    mvwprintw(authWindow, 11, 2, "[-TAB-] Switch to Sign In");
    wrefresh(authWindow);
}

//Id rewrite this and create a helper for swicth between states more freely
void authLoop() {
    while (true) {
        if (authState == AuthState::SignIn) drawSignIn();
        else drawSignUp();

        InputResult u = getInput(authWindow, 4, 12);
        if (u.escapeKey) { closeApp(); exit(0); }
        if (u.tabKey) { authState = (authState == AuthState::SignIn) ? AuthState::SignUp : AuthState::SignIn; continue; }

        InputResult p = getInput(authWindow, 5, 12, true);
        if (p.escapeKey) { closeApp(); exit(0); }
        if (p.tabKey) { authState = (authState == AuthState::SignIn) ? AuthState::SignUp : AuthState::SignIn; continue; }

        std::string confirm;
        if (authState == AuthState::SignUp) {
            InputResult c = getInput(authWindow, 6, 20, true);
            if (c.escapeKey) { closeApp(); exit(0); }
            if (c.tabKey) { authState = AuthState::SignIn; continue; }
            confirm = c.text;
            if (p.text != confirm) {
                mvwprintw(authWindow, 13, 2, "Passwords do not match!");
                wrefresh(authWindow);
                napms(1000);
                continue;
            }
        }

        if (!u.text.empty() && !p.text.empty()) {
            User user(u.text, p.text);
            if (authState == AuthState::SignIn) return;
            else { user.createNewUser(); return; }
        }
    }
}

//draw input
void drawInputWindow(const std::string& text) {
    werase(inputWindow);
    box(inputWindow, 0, 0);
    mvwprintw(inputWindow, 1, 1, "%s", text.c_str());
    wrefresh(inputWindow);
}
