#ifndef HTTPRESPONSE_HPP
# define HTTPRESPONSE_HPP

# include <string>
# include <map>
# include <iostream>

class HTTPResponse
{
	public:
		HTTPResponse( void );
		HTTPResponse( const HTTPResponse & );
		HTTPResponse& operator = ( const HTTPResponse & );
		~HTTPResponse( void );

		HTTPResponse( std::string code );

                std::string                        getCode( void );
                std::string                        getText( void );
                std::string                        getHTTPVersion( void );
                std::string                        getBody( void );
                std::map<std::string, std::string> getHeaders( void );

	private:
                std::string                         _code;
                std::string                         _text;
                std::string                         _httpVersion;
                std::map<std::string, std::string>  _headers;
                std::string                         _body;

                static std::map<std::string, std::string> codeMessagesInit ( void );
                static std::map<std::string, std::string> code_messages;
};


std::string     responseToString(HTTPResponse& response);

#endif