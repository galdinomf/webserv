#ifndef MSGPROCESSOR_HPP
# define MSGPROCESSOR_HPP

# include <string>
# include <algorithm>
# include "HTTPResponse.hpp"
# include "HTTPRequest.hpp"

# include <iostream> // MAY BE REMOVED LATER
# include <ostream>  // MAY BE REMOVED LATER
# include <cstring>  // MAY BE REMOVED LATER
#include <fstream> // may be moved to another file
#include <sstream> // may be moved to another file

class MsgProcessor
{
    private:
            MsgProcessor();
    
    public:
            static std::string processRequest( std::string& msg);
            static std::string parse_request(HTTPRequest& req, std::string line);
            static std::string responseToString(HTTPResponse response);

            static HTTPResponse buildBadRequestResponse();
            static HTTPResponse buildNotImplementedResponse();
};

#endif