#include "ASocket.hpp"

ASocket::ASocket( void )
{
	std::cout << "ASocket default constructor called." << std::endl;
}

ASocket::ASocket(int sockType, int family, int flags, char *port)
{
	_ai = NULL;
	_socketID = callSocket(sockType, family, flags, port, &_ai);
	if (_socketID == -1)
	{
		std::cerr << "failed to get a socket" << std::endl;
		exit(1);
	}
}

ASocket::ASocket( const ASocket & src )
{
	std::cout << "ASocket copy constructor called." << std::endl;
	*this = src;
}

ASocket&	ASocket::operator = ( const ASocket & rhs )
{
	std::cout << "ASocket copy assignment operator called." << std::endl;
	if (this != &rhs)
	{
	// insert members copy here
	}
	return *this;
}

ASocket::~ASocket( void )
{
	std::cout << "ASocket destructor called." << std::endl;
}

int	ASocket::getSocketID( void ) const
{
	return _socketID;
}

struct addrinfo*	ASocket::getAddrInfo( void ) const
{
	return _ai;
}