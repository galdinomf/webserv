#include <iostream>
#include "HTTPServer.hpp"

int	main( void )
{
	char port[] = "9034";
	BindSocket bs( SOCK_STREAM, AF_UNSPEC, AI_PASSIVE, port);

	BindSocket bs2(bs);

	std::cout << "bs.getSocketID() = " << bs.getSocketID() <<  std::endl;
	std::cout << "bs2.getSocketID() = " << bs2.getSocketID() <<  std::endl;

	char port2[] = "7000";
	HTTPServer server(port2, 20);
	std::cout << "server.getBindSocket().getSocketID() = " << server.getBindSocket().getSocketID() <<  std::endl;

	server.start();

	return 0;
}