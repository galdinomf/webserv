#include "Configs.hpp"

Configs::Configs( void ) : rootDir("/home/moacir/42_projects/webserv/project") // replace this with value coming from config file
{
	std::cout << "Configs default constructor called." << std::endl;
}

Configs::Configs( const Configs & src )
{
	std::cout << "Configs copy constructor called." << std::endl;
	*this = src;
}

Configs&	Configs::operator = ( const Configs & rhs )
{
	std::cout << "Configs copy assignment operator called." << std::endl;
	if (this != &rhs)
	{
	// insert members copy here
	}
	return *this;
}

Configs::~Configs( void )
{
	std::cout << "Configs destructor called." << std::endl;
}