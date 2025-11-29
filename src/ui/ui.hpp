#pragma once
#include <string>
#include <cctype>
#include <vector>
#include <memory>
#include <ncurses.h>
#include "../user/user.h"
#include "../server/client.h"

//Implementing scroll with AI(GPT)
//This is bottom here.
int scrollOffset = 0;
const std::string WS_URL = "ws://localhost:5000";


//Auth state mananger
enum class AuthState : short {
    SignIn,
    SignUp,
    InSession
};
std::unique_ptr<User> user;


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
            scrollOffset = 0;
            input.push_back(ch);
            mvwaddch(win, y, x + input.size() - 1, hide ? '*' : ch);
        }
        wrefresh(win);
    }
}

//Close app
void closeApp() {
    endwin();
    closeConnection();
}

//chat TUI loop
void drawChatwindow(const std::string& text) {
    texts.push_back(text);
    werase(chatWindow);
    box(chatWindow, 0, 0);
    int maxRows = getmaxy(chatWindow) - 2;
    int maxCols = getmaxx(chatWindow) - 2;
    
    //Advised to wrap text lines in a temporary buffer which is good but lets see how far that gets us
    std::vector<std::string> textLines;
    for(auto& text : texts){
        int start = 0;
        //Iterate through each text and cache
        while(start < static_cast<int>(text.size())){
            textLines.push_back(text.substr(start,maxCols));
            start += maxCols;
        }
    }

    //Use cache for auto scrolling
    int totalBufferSize = static_cast<int>(textLines.size());
    int startIndex = std::max(0,totalBufferSize - maxRows - scrollOffset);

    //row based printing
    int row = 1;
    for(int i = startIndex;i < totalBufferSize && row < maxRows;i++){
        mvwprintw(chatWindow, row++, 1, "%s", textLines[i].c_str());
    }
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

        InputResult username = getInput(authWindow, 4, 12);
        if (username.escapeKey){ 
            closeApp(); exit(0); 
        }
        if (username.tabKey){
            authState = (authState == AuthState::SignIn) ? AuthState::SignUp : AuthState::SignIn; continue;
        }

        InputResult password = getInput(authWindow, 5, 12, true);
        if (password.escapeKey){ 
            closeApp(); exit(0); 
        }
        if (password.tabKey){
            authState = (authState == AuthState::SignIn) ? AuthState::SignUp : AuthState::SignIn; continue;
        }

        std::string confirmPassword;
        if (authState == AuthState::SignUp) {
            InputResult confirmInput = getInput(authWindow, 6, 20, true);
            if (confirmInput.escapeKey){
                closeApp(); exit(0); 
            }
            if (confirmInput.tabKey){
                authState = AuthState::SignIn; continue; 
            }
            confirmPassword = confirmInput.text;
            if (password.text != confirmPassword) {
                mvwprintw(authWindow, 13, 2, "Passwords do not match!");
                wrefresh(authWindow);
                napms(1000);
                continue;
            }
        }

        if (!username.text.empty() && !password.text.empty()) {
            user = std::make_unique<User>(username.text, password.text);
            if (authState == AuthState::SignIn){
                authState = AuthState::InSession;
                return;
            }else {
                user->createNewUser();
                authState = AuthState::InSession;
                return;
                // drawChatwindow();
                // drawInputWindow();
            }
        }
    }
}

//draw input
void drawInputWindow() {
    werase(inputWindow);
    box(inputWindow, 0, 0);
    InputResult text = getInput(inputWindow,1,1);
    wrefresh(inputWindow);
}

void chatLoop(){
    initClient(WS_URL);
    keypad(inputWindow, TRUE);
    while(true){
        int ch = wgetch(inputWindow);
        if (ch == 17) {
            closeApp();
            exit(0);
        }else if(ch == KEY_UP) {
            scrollOffset += 1;
        }else if(ch == KEY_DOWN){
            scrollOffset = std::max(0,scrollOffset - 1);
        }else if(ch == '\n'){
            InputResult result = getInput(inputWindow,1,1);
            if(!result.text.empty()){
                texts.push_back(result.text);
                sendMessage(result.text);
                drawChatwindow(result.text);
                scrollOffset = 0;
            }
        }

    }
}
