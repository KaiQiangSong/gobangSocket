#ifndef SocketException_H
#define SocketException_H

#include <string>

class SocketException
{
private:
	std::string m_description;
public:
	SocketException(std::string desescription):m_description(desescription){};
	~SocketException(){};

	std::string Description() { return m_description; }
};

#endif