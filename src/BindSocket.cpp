#include "BindsSocket.hpp"

BindsSocket::BindsSocket( void )
{
	std::cout << "BindsSocket default constructor called." << std::endl;
}

BindsSocket::BindsSocket( const BindsSocket & src )
{
	std::cout << "BindsSocket copy constructor called." << std::endl;
	*this = src;
}

BindsSocket&	BindsSocket::operator = ( const BindsSocket & rhs )
{
	std::cout << "BindsSocket copy assignment operator called." << std::endl;
	if (this != &rhs)
	{
	// insert members copy here
	}
	return *this;
}

BindsSocket::~BindsSocket( void )
{
	std::cout << "BindsSocket destructor called." << std::endl;
}