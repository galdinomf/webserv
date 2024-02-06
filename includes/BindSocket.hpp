#ifndef BINDSOCKET_HPP
# define BINDSOCKET_HPP

class BindSocket : public ASocket
{
	public:
		BindSocket( void );
		BindSocket( const BindSocket & );
		BindSocket& operator = ( const BindSocket & );
		~BindSocket( void );

	private:
		// private attributes here
};

#endif