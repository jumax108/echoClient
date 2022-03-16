#include "headers/echoClient.h"

int main(){

	CEchoClient echoClient;

	echoClient.Connect(L"127.0.0.1", 6000, 100, 2, false);

	for(;;){
	}

	return 0;

}
