//This file contains the methods related to processing POST requests
#include "MsgProcessor.hpp"
#include <time.h>

std::string MsgProcessor::workOnPOSTMethod(HTTPRequest& req, Configs& conf)
{
    std::string requestURI = req.getRequestURI();
    unsigned int i = requestURI.find("?");
    if (i != std::string::npos)
        requestURI = requestURI.substr(0, i);
    if (false) //(!conf.methodAllowedForRoute(requestURI, "POST")) MOCK
        return responseToString(buildForbiddenResponse());
    std::string path = conf.rootDir + requestURI + conf.uploadDir;

    std::string field = req.getHeaders()["Content-Disposition"];
    if (field == "")
    {
        time_t now = time(NULL);
        struct tm* hu = localtime(&now);
        std::string fileName(asctime(hu));
        path.append(fileName);
    }
    else
    {
        size_t beginPos = field.find("filename=");
        if (beginPos != std::string::npos)
        {
            beginPos += 10;
            size_t endPos = field.find('"', beginPos);
            if (endPos == std::string::npos)
                return  responseToString(buildBadRequestResponse());
            else
                path.append(field.substr(beginPos, endPos - beginPos));
        }
    }
    return uploadFile(req, path, requestURI);
}

std::string MsgProcessor::uploadFile(HTTPRequest& req, std::string& path, std::string& requestURI)
{
    std::ofstream   ofs;
    std::ifstream   ifs(path.c_str());
    std::string     content = req.getBody();

    if (ifs)
    {
        ifs.close();
        return responseToString(buildConflictResponse()); // file already exists
    }
    ofs.open(path.c_str(), std::ios::binary);
    if (!ofs.is_open())
        return responseToString(buildInternalErrorResponse()); // internal error
    ofs.write(content.c_str(), content.size());
    ofs.close();
    return responseToString(buildCreatedResponse(requestURI));
}