#ifndef ASOCKET_HPP
# define ASOCKET_HPP

# include<iostream>
# include<cstdlib>
# include<netdb.h>
# include<unistd.h>

class ASocket
{
	public:
		ASocket( void );
		ASocket( const ASocket & );
		ASocket& operator = ( const ASocket & );
		~ASocket( void );

		ASocket(int sockType, int family, int flags, char *port);

		virtual void	socketInit( void ) = 0;

		int					getSocketID( void ) const;
		struct addrinfo*	getAddrInfo( void ) const;

	protected:
		int					_socketID;
	private:
    	struct addrinfo*	_ai;
};

int callSocket(int sockType, int family, int flags, char *port, 
                struct addrinfo **ai);

#endif