#include "headers/echoClient.h"

CEchoClient::CEchoClient(){

	echoData = 0;

}

void CEchoClient::OnEnterJoinServer(){

	printf("join server\n");

	CPacketPtr_Lan packet;
	packet << echoData;

	sendPacket(packet);

}

void CEchoClient::OnLeaveServer(){

	printf("disconnected\n");

}

void CEchoClient::OnRecv(CPacketPointer packet){

	int data;
	packet >> data;

	if(echoData == data){
		
		printf("sendData: %d, recvData: %d\n", echoData, data);
		Sleep(1000);

		echoData += 1;
		CPacketPtr_Lan packet;
		packet << echoData;
		
		sendPacket(packet);

	} else {
		printf("error: sendData: %d, recvData: %d\n", echoData, data);
	}


}

void CEchoClient::OnSend(int sendSize){
	printf("sent\n");
}

void CEchoClient::OnError(int errorCode, const wchar_t* errorMsg){

	wprintf(L"code: %d\n", errorCode);
	wprintf(L"msg: %s\n", errorMsg);

}