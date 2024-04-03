#include "HTTPResponse.hpp"

std::string responseToString(HTTPResponse& response)
{
    // build response's status line
    std::string responseAsString(response.getHTTPVersion());
    responseAsString.append(response.getCode());
    responseAsString.append(response.getText());
    responseAsString.append("\r\n");
    // append all headers
    std::map<std::string, std::string> m = response.getHeaders();
    std::map<std::string, std::string>::iterator it;
    for (it = m.begin(); it != m.end(); it++)
    {
        responseAsString.append(it->first);
        responseAsString.append(": ");
        responseAsString.append(it->second);
        responseAsString.append("\r\n");
    }
    //append body
    responseAsString.append("\r\n");
    responseAsString.append(response.getBody());

    return responseAsString;
}