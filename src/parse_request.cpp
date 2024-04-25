#include "MsgProcessor.hpp"
#include <sstream>

bool    methodIsImplemented(std::string method)
{
    std::vector<std::string> methods;
    std::vector<std::string>::iterator it;

    methods.push_back("GET");
    methods.push_back("POST");
//     methods.push_back("DELETE");

    it = std::find(methods.begin(), methods.end(), method);
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

    return "";
}

std::string parseAndAddHeaderEntry(std::string & line, std::map<std::string, std::string> * headers)
{
    std::string key;
    int i;

    if (line[line.size() - 1] != '\r')
        return MsgProcessor::responseToString(MsgProcessor::buildBadRequestResponse());

    for (i = 0; line[i] != ':'; i++)
    {
        if ((line[i] == ' ') || (line[i] == '\0'))
        return MsgProcessor::responseToString(MsgProcessor::buildBadRequestResponse());
    }

    key = line.substr(0, i);
    if ((*headers)[key] != "")
        return MsgProcessor::responseToString(MsgProcessor::buildBadRequestResponse());

    int start = line.find_first_not_of(" \t\r"); // Find the first non-whitespace character
    int end = line.find_last_not_of(" \t\r"); // Find the last non-whitespace character

    (*headers)[key] = line.substr(start, end - start + 1);
    return "";
}

std::string MsgProcessor::parse_request(HTTPRequest& req, std::string request)
{
    std::string responseCode = "";

    std::string method;
    std::string requestURI;
    std::string version;
    std::map<std::string, std::string> headers = req.getHeaders();
    std::string body;

    std::istringstream stream(request);
    std::string line;

    std::getline(stream, line);
    responseCode = parse_first_line(line, &method, &requestURI, &version);
    if (responseCode != "")
        return responseCode;
    while (std::getline(stream, line))
    {
        if (line == "\r")
            break;
        responseCode = parseAndAddHeaderEntry(line, &headers);
        if (responseCode != "")
            return responseCode;
    }

    if (headers["Host"] == "")
        return MsgProcessor::responseToString(MsgProcessor::buildBadRequestResponse());

    while (std::getline(stream, line))
    {
        if (line.empty())
            break;
        body.append(line);
        body.push_back('\n');
    }
    req.setMethod(method);
    req.setRequestURI(requestURI);
    req.setHTTPVersion("HTTP/1.1");
    req.setBody(body);

    return responseCode;
}