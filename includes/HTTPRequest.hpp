#ifndef HTTPREQUEST_HPP
# define HTTPREQUEST_HPP

# include <string>
# include <map>
# include <iostream>

class HTTPRequest
{
	public:
		HTTPRequest( void );
                HTTPRequest( std::string& method,      std::string& requestURI, 
                             std::string& httpVersion, std::map<std::string, std::string>    headers, 
                             std::string& body );
		HTTPRequest( const HTTPRequest & );
		HTTPRequest& operator = ( const HTTPRequest & );
		~HTTPRequest( void );

                std::string getMethod( void );
                std::string getRequestURI( void );
                std::string getHTTPVersion( void );
                std::string getBody( void );
                std::map<std::string, std::string> getHeaders( void );

                void    setMethod( std::string );
                void    setRequestURI( std::string );
                void    setHTTPVersion( std::string );
                void    setBody( std::string );

	private:
                std::string                         _method;
                std::string                         _requestURI;
                std::string                         _httpVersion;
                std::map<std::string, std::string>  _headers;
                std::string                         _body;
};


#endif