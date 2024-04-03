#include "HTTPResponse.hpp"

HTTPResponse::HTTPResponse( void )
{
	std::cout << "HTTPResponse default constructor called." << std::endl;
}

HTTPResponse::HTTPResponse( std::string code )
{
	_code = code;
	std::cout << "HTTPResponse default constructor called." << std::endl;
}

HTTPResponse::HTTPResponse( const HTTPResponse & src )
{
	std::cout << "HTTPResponse copy constructor called." << std::endl;
	*this = src;
}

HTTPResponse&	HTTPResponse::operator = ( const HTTPResponse & rhs )
{
	std::cout << "HTTPResponse copy assignment operator called." << std::endl;
	if (this != &rhs)
	{
	// insert members copy here
	}
	return *this;
}

HTTPResponse::~HTTPResponse( void )
{
	std::cout << "HTTPResponse destructor called." << std::endl;
}

std::string HTTPResponse::getCode( void )
{
    return _code;
}

std::string HTTPResponse::getText( void )
{
    return _text;
}

std::string HTTPResponse::getHTTPVersion( void )
{
    return _httpVersion;
}

std::string HTTPResponse::getBody( void )
{
    return _body;
}

std::map<std::string, std::string> HTTPResponse::getHeaders( void )
{
    return _headers;
}