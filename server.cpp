#include <iostream>
#include <string>
#include "serverSocket.h"
#include "socketexception.h"

int main()
{
	std::cout << " Running Server ... " << std::endl;
	try
	{
		ServerSocket server(10205);
		server.Run();
	}
	catch(SocketException& ex)
	{
		std::cout << "Exception was caught: "  << ex.Description() << std::endl;
		std::cout << "Exiting." << std::endl;
	}
	return 0;
}