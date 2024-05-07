#ifndef MSGPROCESSOR_HPP
# define MSGPROCESSOR_HPP

# include <string>
# include <algorithm>
# include "HTTPResponse.hpp"
# include "HTTPRequest.hpp"
# include "Configs.hpp"
# include <dirent.h>
# include <cstring>
# include <sstream>
# include <sys/stat.h>
# include<unistd.h>

# include <iostream> // MAY BE REMOVED LATER
# include <ostream>  // MAY BE REMOVED LATER
#include <fstream> // may be moved to another file

class MsgProcessor
{
    private:
            Configs& _serverConfigs;
    
    public:
            MsgProcessor(Configs&);
            std::string processRequest( std::string& msg);
            static std::string parse_request(HTTPRequest& req, std::string line);
            static std::string responseToString(HTTPResponse response);

            std::string workOnRequestAndGetResponse(HTTPRequest&, Configs&);

            std::string workOnGETMethod(HTTPRequest&, Configs&);
            std::string getRequestedFile(std::string requestURI, Configs& conf);
            std::string workOnDirectoryRequest(std::string& requestURI, Configs& conf);
            std::string writeDirectoryListing(DIR* dir);

            static HTTPResponse buildBadRequestResponse();
            static HTTPResponse buildNotImplementedResponse();
            static HTTPResponse buildRequestURITooLongResponse();
            static HTTPResponse buildNotFoundResponse();
            static HTTPResponse buildOKResponse( std::string& );
};

#endif