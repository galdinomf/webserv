#include <iostream>
#include "BindSocket.hpp"

int	main( void )
{
	char port[] = "9034";
	BindSocket bs( SOCK_STREAM, AF_UNSPEC, AI_PASSIVE, port);

	std::cout << "Hello world!" << std::endl;
	return 0;
}