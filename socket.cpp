#include "socket.h"
#include <stdlib.h>
#include <memory.h>
#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <sstream>

Socket::Socket():m_sockfd(-1)
{
}

Socket::~Socket()
{
	if (IsValid())
		close(m_sockfd);
}

//server function
bool Socket::Create()
{
	m_sockfd = socket(AF_INET,SOCK_STREAM,0);
	return IsValid();
}

bool Socket::Bind(const int port)
{
	if (!IsValid())
		return false;

	m_address.sin_family = AF_INET;
	m_address.sin_addr.s_addr = htonl(INADDR_ANY);
	m_address.sin_port = htons(port);

	int bindReturn = bind(m_sockfd,(struct sockaddr*)&m_address, sizeof(m_address));
	if (bindReturn == -1)
		return false;
	return true;
}

bool Socket::Listen() const
{
	if (!IsValid())
		return false;
	int listenReturn = listen(m_sockfd,MAXCONNECTION);
	if (listenReturn == -1)
		return false;
	return true;
}

bool Socket::Accept(Socket& clientSocket) const
{
	int clientaddrLength = sizeof(clientSocket.m_address);
	clientSocket.m_sockfd = accept(m_sockfd,(struct sockaddr*) &clientSocket.m_address,(socklen_t*)&clientaddrLength);
	if (clientSocket.m_sockfd == -1)
		return false;
	return true;
}
//end server function

bool Socket::Connect(const std::string& host, const int port)
{
	if (!IsValid())
		return false;

	m_address.sin_family=AF_INET;
	m_address.sin_port= htons(port);
	m_address.sin_addr.s_addr=inet_addr(host.c_str());

	int connectReturn=connect(m_sockfd,(struct sockaddr*)&m_address,sizeof(m_address));
	if (connectReturn == -1)
		return false;
	return true;
}

bool Socket::Send(Socket& socket, const std::string& message)
{
	int result = send(socket.m_sockfd,message.c_str(),message.length(),MSG_NOSIGNAL);
	if (result == -1)
		return false;
	return true;
}

int Socket::Receive(Socket& socket, std::string& message)
{
	char buffer[MAXRECEIVE+1];
	message.clear();
	memset(buffer,0,MAXRECEIVE+1);

	int numberRead=recv(socket.m_sockfd,buffer,MAXRECEIVE,0);
	if (numberRead == -1)
	{
		std::cout << "Error in Socket:: Receive" << std::endl;
		return 0;
	}
	else if (numberRead == 0)
		return 0;
	else
	{
		message = buffer;
		return numberRead;
	}
}

void Socket::SetNoBlocking(const bool flag)
{
	if (IsValid())
	{
		int opts;
		opts = fcntl(m_sockfd, F_GETFL);
		if (opts < 0) return;
		if (flag)
			opts = (opts | O_NONBLOCK);
		else
			opts = (opts & ~O_NONBLOCK);
		fcntl(m_sockfd, F_SETFL,opts);
	}
}

bool Socket::IsValid() const
{
	return m_sockfd!= -1;
}

std::string Socket::getPort()
{
	char str[INET_ADDRSTRLEN];
	inet_ntop(AF_INET,&(m_address.sin_addr),str,INET_ADDRSTRLEN);
	return std::string (str);
}

std::string Socket::getAddress()
{
	return std::string(inet_ntoa(m_address.sin_addr));
}