#include "BindSocket.hpp"

BindSocket::BindSocket( void )
{
	std::cout << "BindSocket default constructor called." << std::endl;
}

BindSocket::BindSocket(int sockType, int family, int flags, char *port) : ASocket(sockType, family, flags, port)
{
	socketInit();
	std::cout << "BindSocket constructor called." << std::endl;
}

BindSocket::BindSocket( const BindSocket & src ) : ASocket()
{
	std::cout << "BindSocket copy constructor called." << std::endl;
	*this = src;
}

BindSocket&	BindSocket::operator = ( const BindSocket & rhs )
{
	std::cout << "BindSocket copy assignment operator called." << std::endl;
	if (this != &rhs)
	{
		this->_socketID = rhs.getSocketID();
	}
	return *this;
}

BindSocket::~BindSocket( void )
{
	std::cout << "BindSocket destructor called." << std::endl;
}

void BindSocket::socketInit( void )
{
	int	yes = 1;

	setsockopt(getSocketID(), SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
	if (bind(getSocketID(), getAddrInfo()->ai_addr, getAddrInfo()->ai_addrlen) < 0)
	{
		std::cout << getAddrInfo() << std::endl;
		close(getSocketID());
		std::cerr << "socket failed to bind" << std::endl;
		freeaddrinfo(getAddrInfo());
		exit(1);
	}
		freeaddrinfo(getAddrInfo());
}