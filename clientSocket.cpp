#include "clientSocket.h"
#include "socketexception.h"

ClientSocket::ClientSocket(const std::string &host, const int port)
{
	if (!Socket::Create())
		throw SocketException("Could not create client socket.");
	if (!Socket::Connect(host,port))
		thorw SocketException("Could not connect to port.");
}

ClientSocket::~ClientSocket()
{

}

bool ClientSocket::Send(const std::string & message)
{
	return Socket::Send(static_cast<Socket&>(*this),message);
}

int ClientSocket::Receive(std::string & message)
{
	return Socket::Receive(static_cast<Socket&>(*this),message);
}