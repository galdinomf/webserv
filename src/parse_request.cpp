#include "MsgProcessor.hpp"
#include <sstream>

void    add_map_entry(std::string & line, std::map<std::string, std::string>* headers)
{
    std::size_t pos = 0;
    if ((pos = line.find(": ")) != std::string::npos)
        (*headers)[line.substr(0, pos)] = line.substr(pos + 2, line.size());
}

std::string    parse_first_line(std::string & line, std::string* method, std::string* requestURI, std::string* version)
{
    std::string lastElement;
    std::istringstream stream(line);


    if (line.substr((strlen(line.c_str()) - 1), 1) != "\r")
        return MsgProcessor::responseToString(MsgProcessor::buildBadRequestResponse());
    stream >> *method >> *requestURI >> *version >> lastElement;
    
    if ((*method == "") || (*requestURI == "") || (*version == "") || (lastElement != ""))
        return MsgProcessor::responseToString(MsgProcessor::buildBadRequestResponse());
    // printf("lastElement = %s\n", lastElement.c_str());
    // printf("lastElement[0] = %d\n", lastElement.c_str()[0]);
    // printf("version[8] = %d\n", version->c_str()[8]);
    // if (lastElement != "\r\n")
    //     return "400";

    return "";
}

std::string MsgProcessor::parse_request(HTTPRequest& req, std::string request)
{
    std::string responseCode = "";

    std::string method;
    std::string requestURI;
    std::string version;
    std::map<std::string, std::string> headers;
    std::string body;

    std::istringstream stream(request);
    std::string line;

    std::getline(stream, line);
    responseCode = parse_first_line(line, &method, &requestURI, &version);
    std::cout << "reponseConde = " << responseCode << std::endl;
    if (responseCode != "")
        // return (responseToString(HTTPResponse(responseCode)));
        return responseCode;
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
    req.setMethod(method);
    //return (HTTPRequest(method, requestURI, version, headers, body));

    return responseCode;
}