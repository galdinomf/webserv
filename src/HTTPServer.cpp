#include "HTTPServer.hpp"

HTTPServer::HTTPServer( void )
{
	// std::cout << "HTTPServer default constructor called." << std::endl;
}

HTTPServer::HTTPServer( char * port )
{
	_socket = BindSocket( SOCK_STREAM, AF_UNSPEC, AI_PASSIVE, port);
}

HTTPServer::HTTPServer( const HTTPServer & src )
{
	// std::cout << "HTTPServer copy constructor called." << std::endl;
	*this = src;
}

HTTPServer&	HTTPServer::operator = ( const HTTPServer & rhs )
{
	// std::cout << "HTTPServer copy assignment operator called." << std::endl;
	if (this != &rhs)
	{
	// insert members copy here
	}
	return *this;
}

HTTPServer::~HTTPServer( void )
{
	// std::cout << "HTTPServer destructor called." << std::endl;
}

BindSocket HTTPServer::getBindSocket( void ) const
{
	return _socket;
}