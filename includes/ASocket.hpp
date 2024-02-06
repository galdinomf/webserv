#ifndef ASOCKET_HPP
# define ASOCKET_HPP

# include<iostream>

class ASocket
{
	public:
		ASocket( void );
		ASocket( const ASocket & );
		ASocket& operator = ( const ASocket & );
		~ASocket( void );

		ASocket(int sockType, int family, int flags, char *port);

		virtual void	socketInit( void ) = 0;

		int	getSocketID( void );

	private:
		int		_socketID;
};

int callSocket(int sockType, int family, int flags, char *port);

#endif