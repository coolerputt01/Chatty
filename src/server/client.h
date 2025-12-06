#include "ixwebsocket/IXWebSocket.h"
#include "ixwebsocket/IXNetSystem.h"
#include "../ui/ui.hpp"
#include "../messages/message.hpp"
#include <string>
#include <iostream>


#pragma once

ix::WebSocket ws;

void drawChatwindow(const Message& msg);
std::string getCurrentTime();

void initClient(const std::string& url,std::unique_ptr<User>& user){
    ix::initNetSystem();
    ws.setUrl(url);

    ws.setOnMessageCallback(
        [&user](const ix::WebSocketMessagePtr& msg){
            if(msg->type == ix::WebSocketMessageType::Message){
                Message m;
                m.text = msg->str;
                m.time = getCurrentTime();
                m.username = user->username;
                drawChatwindow(m);
            }else if(msg->type == ix::WebSocketMessageType::Error){
                std::cerr<<"Error occurred while connecting to ws"<< msg->errorInfo.reason <<'\n'<<std::flush;
            }
        }
    );

    ws.start();
}

void closeConnection() {
    ws.stop();
}
void sendMessage(const std::string& text){
    ws.send(text);
}

