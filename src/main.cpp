#include <iostream>
#include "BindSocket.hpp"

int	main( void )
{
	char port[] = "9034";
	BindSocket bs( SOCK_STREAM, AF_UNSPEC, AI_PASSIVE, port);

	BindSocket bs2(bs);

	std::cout << "bs.getSocketID() = " << bs.getSocketID() <<  std::endl;
	std::cout << "bs2.getSocketID() = " << bs2.getSocketID() <<  std::endl;
	return 0;
}