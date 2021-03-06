#ifndef ClientSocket_H
#define ClientSocket_H

#include "socket.h"
#include <string>

class ClientSocket : public Socket
{
public:
	ClientSocket(const std::string& host, const int port);
	virtual ~ClientSocket();

	bool Send(const std::string& message);
	int Receive(std::string& mssage);
};

#endif