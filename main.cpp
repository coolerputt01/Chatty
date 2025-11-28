#include "src/ui/ui.hpp"
#include "src/server/client.h"
#include<string>


const std::string WS_URL = "ws://localhost:5000";

int main(){
	initApp();

	authLoop();

	closeApp();
	closeConnection();
	return 0;
}
