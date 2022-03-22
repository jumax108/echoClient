#include "headers/echoClient.h"

CEchoClient::CEchoClient(int sendNum, int delay){

	_echoSendData = 0;
	_echoRecvData = 0;

	_sendNum = sendNum;
	_delay = delay;
}

void CEchoClient::OnEnterJoinServer(){

	printf("join server\n");

	
	for(int sendCnt = 0; sendCnt < _sendNum; ++sendCnt){

		CPacketPtr_Lan packet;
		packet << _echoSendData;
		_echoSendData += 1;

		sendPacket(packet);
	}

}

void CEchoClient::OnLeaveServer(){

	printf("disconnected\n");

}

void CEchoClient::OnRecv(CPacketPtr_Lan packet){

	unsigned __int64 data;
	packet >> data;

	if(_echoRecvData == data){
		
		_echoRecvData += 1;

		CPacketPtr_Lan packet;
		packet << _echoSendData;
		_echoSendData += 1;
		

		sendPacket(packet);

	} else {
		printf("error: sendData: %d, recvData: %d\n", _echoRecvData, data);
		CDump::crash();
	}


}

void CEchoClient::OnSend(int sendSize){
	if(_delay > 0){
		Sleep(_delay);
	}
}

void CEchoClient::OnError(int errorCode, const wchar_t* errorMsg){

	wprintf(L"code: %d\n", errorCode);
	wprintf(L"msg: %s\n", errorMsg);

}