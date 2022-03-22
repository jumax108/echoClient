#pragma once
#define WIN32_LEAN_AND_MEAN
#include <stdio.h>

#include "objectFreeListTLS/headers/objectFreeListTLS.h"
#include "stack/headers/stack.h"
#include "queue/headers/queue.h"

#include "lanClient/headers/lanClient.h"
#pragma comment(lib, "lib/lanClient/lanClient_iocp")

class CEchoClient: public CLanClient{

public:
	CEchoClient(int sendNum, int delay);

	void OnEnterJoinServer();
	void OnLeaveServer();

	void OnRecv(CPacketPtr_Lan packet);
	void OnSend(int sendSize);

	void OnError(int errorCode, const wchar_t* errorMsg);

private:

	unsigned __int64 _echoSendData;
	unsigned __int64 _echoRecvData;
	int _sendNum;

	int _delay;

};