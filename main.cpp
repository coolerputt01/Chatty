#include "src/ui/ui.h"
#include "src/server/client.h"
#include<string>


const std::string WS_URL = "ws://localhost:5000";

int main(){
	initApp();
	initClient(WS_URL);

	authLoop();

	closeApp();
	closeConnection();
	return 0;
}
