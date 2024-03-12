#ifndef HTTPSERVER_HPP
# define HTTPSERVER_HPP

# include "BindSocket.hpp"

class HTTPServer
{
	public:
		HTTPServer( void );
		HTTPServer( const HTTPServer & );
		HTTPServer& operator = ( const HTTPServer & );
		~HTTPServer( void );

        HTTPServer( char * port, int backLog );

        int       start();

        BindSocket getBindSocket( void ) const;
        int        getBackLog( void ) const;

	private:
        BindSocket  _socket;
        int         _backLog;
};

#endif