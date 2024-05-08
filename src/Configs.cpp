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

std::string	Configs::getDefaultFileNameForDirectory( std::string& dir )
{
	dir.c_str(); // REMOVE THIS LINE
	//This function must be completed.
	//It must receive a route and return its default file name.
	//If no default files are set, the function must return an empty string.
	return "index.html";	//THIS IS A MOCK
}

bool	Configs::directoryListingEnabled( std::string& dir )
{
	dir.c_str(); // REMOVE THIS LINE
	//This function must be completed.
	//It must receive a route for a directory and check if its listing is enabled.
	//The return value is false by default.
	return false; //THIS IS A MOCK
}

bool	Configs::methodAllowedForRoute( std::string& dir , std::string method)
{
	dir.c_str(); // REMOVE THIS LINE
	method.c_str(); // REMOVE THIS LINE
	//This function must be completed.
	//It must receive a route and a method, 
	//and check if the method is allowed for the given route.
	//The return value is true for GET and false for POST and DELETE by default.
	return false; //THIS IS A MOCK
}