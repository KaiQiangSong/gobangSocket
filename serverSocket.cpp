#include "serverSocket.h"
#include "socketexception.h"
#include "gobangServer.h"

#include <pthread.h>
#include <iostream>
#include <unistd.h>
#include <list>

bool ServerSocket::serviceFlag = true;
gobangServer ServerSocket::gbServer;

ServerSocket :: ServerSocket(const int port)
{
	if (! Socket::Create())
	{
		throw SocketException("Could not create server socket.");
	}
	if (! Socket::Bind(port))
	{
		throw SocketException("Could not bind to port.");
	}
	if (!Socket::Listen())
	{
		throw SocketException("Could not listen to socket.");
	}
}

ServerSocket::~ServerSocket()
{
}

void ServerSocket::Accept(Socket& socket)
{
	if (!Socket::Accept(socket))
	{
		throw SocketException("Could not accept socket.");
	}
}

bool ServerSocket::Service()
{
	Socket* clientSocket = new Socket;
	Accept(*clientSocket);

	//create new thread for a new client
	pthread_t newThread;
	int returnCode =
	pthread_create(&newThread,NULL,ProcessMsg,static_cast<void*>(clientSocket));
	if (returnCode)
	{
		std::cout << "Failed to detach thread." << std::endl;
		return false;
	}
	return true;
}

void ServerSocket::Run()
{
	while (ServerSocket::serviceFlag)
	{
		if (ServerSocket::gbServer.get_size() >= static_cast<unsigned int>(MAXCONNECTION))
			ServerSocket::serviceFlag = false;
		else
			ServerSocket::serviceFlag = Service();
		sleep(1);
	}
}

void* ServerSocket::ProcessMsg(void * arg)
{
	std::string message;
	Socket* clientSocket = static_cast<Socket*> (arg);
	
	std::cout << "Accept one Clinet : " << clientSocket->getAddress() <<  std::endl;

	if (ServerSocket::serviceFlag)
	{
		Receive(*clientSocket,message);
		
		std::cout << "Receive Message : " << clientSocket->getAddress() <<  std::endl;
		std::cout << message << std::endl;
		std::cout << std::endl;
		
		message = ServerSocket::gbServer.Reply(message);
		
		std::cout << "Send Message : " << clientSocket->getAddress()  <<  std::endl;
		std::cout << message << std::endl;
		std::cout << std::endl;
		
		
		Send(*clientSocket, message);
	}
	pthread_exit(NULL);
	return NULL;
}

