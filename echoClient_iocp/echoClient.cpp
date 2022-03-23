#include "headers/echoClient.h"

CEchoClient::CEchoClient(int sendNum, int delay, bool beReconnect, int reconnectRatio, int maxPacketNum, int workerThreadNum):
	CLanClient(maxPacketNum, workerThreadNum)
{

	_echoSendData = 0;
	_echoRecvData = 0;

	_sendNum = sendNum;
	_delay = delay;

	_beReconnect = beReconnect;
	_reconnectRatio = reconnectRatio;

	_requestDisconnect = false;

	_ip = nullptr;
	_port = 0;
	_maxSendPacketNum = 0;
	_workerThreadNum = 0;
	_onNagle = false;

	_randSeed = 0;
	srand(_randSeed);
}

void CEchoClient::OnEnterJoinServer(){

	_echoSendData = 0;
	_echoRecvData = 0;

	for(int sendCnt = 0; sendCnt < _sendNum; ++sendCnt){

		CPacketPtr_Lan packet;
		packet << _echoSendData;
		_echoSendData += 1;

		sendPacket(packet);
	}

}

void CEchoClient::OnLeaveServer(){

	if(_requestDisconnect == false){
		CDump::crash();
	}
	
	Connect(_ip, _port, _onNagle);
	
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

	//if(_beReconnect == true && _echoSendData > 1000000){

		if(rand()%100 < _reconnectRatio){
			// request disconnect
			_requestDisconnect = true;
			if(Disconnect() == false){
				CDump::crash();
			}

		}

	//}
}

void CEchoClient::OnError(int errorCode, const wchar_t* errorMsg){

	wprintf(L"\ncode: %d\n", errorCode);
	wprintf(L"msg: %s\n\n", errorMsg);

}