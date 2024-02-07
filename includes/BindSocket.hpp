#ifndef BINDSOCKET_HPP
# define BINDSOCKET_HPP

# include "ASocket.hpp"
# include <sys/socket.h>

class BindSocket : public ASocket
{
	public:
		BindSocket( void );
		BindSocket( const BindSocket & );
		BindSocket& operator = ( const BindSocket & );
		~BindSocket( void );

		BindSocket(int sockType, int family, int flags, char *port);

	private:
		void socketInit( void );
};

#endif