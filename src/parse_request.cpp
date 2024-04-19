#include "MsgProcessor.hpp"
#include <sstream>

void    add_map_entry(std::string & line, std::map<std::string, std::string>* headers)
{
    std::size_t pos = 0;
    if ((pos = line.find(": ")) != std::string::npos)
        (*headers)[line.substr(0, pos)] = line.substr(pos + 2, line.size());
}

bool    methodIsImplemented(std::string method)
{
    std::vector<std::string> methods;
    std::vector<std::string>::iterator it;

    it = std::find(methods.begin(), methods.end(), method);
    methods.push_back("GET");
//     methods.push_back("POST");
//     methods.push_back("DELETE");
    return (it != methods.end());
}

std::string    parse_first_line(std::string & line, std::string* method, std::string* requestURI, std::string* version)
{
    std::string lastElement;
    std::istringstream stream(line);
    int uriSize;


    if (line.substr((strlen(line.c_str()) - 1), 1) != "\r")
        return MsgProcessor::responseToString(MsgProcessor::buildBadRequestResponse());
    stream >> *method >> *requestURI >> *version >> lastElement;
    
    if (!methodIsImplemented(*method))
    {
        if (*method == "")
            return MsgProcessor::responseToString(MsgProcessor::buildBadRequestResponse());
        else
            return MsgProcessor::responseToString(MsgProcessor::buildNotImplementedResponse());
    }

    uriSize = strlen(requestURI->c_str());
    if ((uriSize < 1) || (requestURI->c_str()[0] != '/'))
        return MsgProcessor::responseToString(MsgProcessor::buildBadRequestResponse());
    if (uriSize > 8000)
        return MsgProcessor::responseToString(MsgProcessor::buildRequestURITooLongResponse());

    if ((*requestURI == "") || (*version == "") || (lastElement != ""))
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