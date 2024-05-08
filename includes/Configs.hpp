#ifndef CONFIGS_HPP
# define CONFIGS_HPP

# include <string>
# include <iostream>

class Configs
{
	public:
		Configs( void );
		Configs( const Configs & );
		Configs& operator = ( const Configs & );
		~Configs( void );

		const std::string	rootDir;

		std::string	getDefaultFileNameForDirectory( std::string& );
		bool		directoryListingEnabled( std::string& );
		bool		methodAllowedForRoute( std::string& dir , std::string method);

	private:
		// private attributes here
};

#endif