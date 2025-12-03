#include "ixwebsocket/IXWebSocket.h"
#include "ixwebsocket/IXNetSystem.h"
#include "../ui/ui.hpp"
#include <string>
#include <iostream>


#pragma once

ix::WebSocket ws;

void drawChatwindow(const std::string& text);

void initClient(const std::string& url){
    ix::initNetSystem();
    ws.setUrl(url);

    ws.setOnMessageCallback(
        [](const ix::WebSocketMessagePtr& msg){
            if(msg->type == ix::WebSocketMessageType::Message){
                drawChatwindow(msg->str);
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

