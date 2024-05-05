#ifndef HTTPSERVER_HPP
# define HTTPSERVER_HPP

# include "BindSocket.hpp"
# include "MsgProcessor.hpp"
# include "Configs.hpp"

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
                char        _dataBuffer[512];
                Configs     _configs;

                void        _acceptNewConnection(fd_set *master, int *fdmax);
                void	    _closeAndClearSocket(int i, int nbytes, fd_set *master);
                void	    _handleDataReceived(fd_set *master, int *nbytes, int i);

};

#endif