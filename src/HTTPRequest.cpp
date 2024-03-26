#include "HTTPRequest.hpp"

HTTPRequest::HTTPRequest( void )
{
	std::cout << "HTTPRequest default constructor called." << std::endl;
}

HTTPRequest::HTTPRequest( std::string& method, std::string& requestURI, 
                          std::string& httpVersion, std::map<std::string, std::string> headers, 
                          std::string& body )
{
    _method = method;
    _requestURI = requestURI;
    _httpVersion = httpVersion;
    _headers = headers;
    _body = body;

	std::cout << "HTTPRequest default constructor called." << std::endl;
}

HTTPRequest::HTTPRequest( const HTTPRequest & src )
{
	std::cout << "HTTPRequest copy constructor called." << std::endl;
	*this = src;
}

HTTPRequest&	HTTPRequest::operator = ( const HTTPRequest & rhs )
{
	std::cout << "HTTPRequest copy assignment operator called." << std::endl;
	if (this != &rhs)
	{
        // _method = rhs.method;
        // _requestURI = rhs.requestURI;
        // _httpVersion = rhs.httpVersion;
        // _headers = rhs.headers;
        // _body = rhs.body;
	}
	return *this;
}

HTTPRequest::~HTTPRequest( void )
{
	std::cout << "HTTPRequest destructor called." << std::endl;
}

std::string HTTPRequest::getMethod( void )
{
    return _method;
}

std::string HTTPRequest::getRequestURI( void )
{
    return _requestURI;
}

std::string HTTPRequest::getHTTPVersion( void )
{
    return _httpVersion;
}

std::string HTTPRequest::getBody( void )
{
    return _body;
}

std::map<std::string, std::string> HTTPRequest::getHeaders( void )
{
    return _headers;
}