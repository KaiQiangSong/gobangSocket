#ifndef ServerSocket_H
#define ServerSocket_H

#include "socket.h"
#include "gobangServer.h"

#include <vector>

class ServerSocket: public Socket
{
public:
	ServerSocket(const int port);
	ServerSocket();
	virtual ~ServerSocket();

	void Accept(Socket& socket);

	void Run();
	//Run server to connect multi_clients

private:
	bool Service();
	static void* ProcessMsg(void *arg);

	static bool serviceFlag;
	static gobangServer gbServer;
};

#endif