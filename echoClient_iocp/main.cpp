#include "headers/echoClient.h"

#include "textParser/headers/textParser.h"
#pragma comment(lib, "lib/textParser/textParser")

int main(){

	CTextParser parser("clientConfig.txt");

	wchar_t ip[20]={0, };
	char ipSingleByte[20]={0,};
	int ipLen;
	int port;

	parser.setNameSpace("Connection");
	parser.getTextByKey("ip", ipSingleByte, 20, &ipLen);
	parser.getIntByKey("port", &port);
	parser.resetNameSpace(); 

	size_t convertSize;
	mbstowcs_s(&convertSize, ip, ipSingleByte, 20);

	int maxSendPacketNum;
	int workerThreadNum;
	int onNagle;
	parser.setNameSpace("NetworkModel");
	parser.getIntByKey("maxSendPacketNum", &maxSendPacketNum);
	parser.getIntByKey("workerThreadNum", &workerThreadNum);
	parser.getIntByKey("onNagle", &onNagle);
	parser.resetNameSpace();

	int overSend;
	parser.setNameSpace("Echo");
	parser.getIntByKey("overSend", &overSend);
	parser.resetNameSpace();

	CEchoClient echoClient(100, 0, true, 100, maxSendPacketNum, workerThreadNum);

	echoClient._ip = ip;
	echoClient._port = port;
	echoClient._maxSendPacketNum = maxSendPacketNum;
	echoClient._workerThreadNum = workerThreadNum;
	echoClient._onNagle = onNagle;

	echoClient.Connect(ip, port, onNagle);

	for(;;){
		
		printf("recv TPS: %d\n", echoClient.getRecvTPS());
		printf("send TPS: %d\n", echoClient.getSendTPS());
		printf("packet pool: %I64d Chunks\n\n", CPacketPtr_Lan::getPacketPoolUsage());

		Sleep(1000);

	}

	return 0;

}
