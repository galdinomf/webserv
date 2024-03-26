#include "HTTPRequest.hpp"
#include <sstream>

void    add_map_entry(std::string & line, std::map<std::string, std::string>* headers)
{
    std::size_t pos = 0;
    if ((pos = line.find(": ")) != std::string::npos)
        (*headers)[line.substr(0, pos)] = line.substr(pos + 2, line.size());
}

void    parse_first_line(std::string & line, std::string* method, std::string* requestURI, std::string* version)
{
    std::istringstream stream(line);
    stream >> *method >> *requestURI >> *version;
}

HTTPRequest parse_request(std::string request)
{
    std::string method;
    std::string requestURI;
    std::string version;
    std::map<std::string, std::string> headers;
    std::string body;

    std::istringstream stream(request);
    std::string line;

    std::getline(stream, line);
    parse_first_line(line, &method, &requestURI, &version);
    while (std::getline(stream, line))
    {
        if (line == "\r")
            break;
        add_map_entry(line, &headers);
    }
    while (std::getline(stream, line))
    {
        std::cout << "line = " << line << std::endl;
        if (line.empty())
            break;
        body.append(line);
        body.push_back('\n');
    }
    return (HTTPRequest(method, requestURI, version, headers, body));
}