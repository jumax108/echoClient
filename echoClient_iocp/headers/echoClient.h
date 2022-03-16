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
	CEchoClient();

	void OnEnterJoinServer();
	void OnLeaveServer();

	void OnRecv(CPacketPointer packet);
	void OnSend(int sendSize);

	void OnError(int errorCode, const wchar_t* errorMsg);

private:
	int echoData;

};