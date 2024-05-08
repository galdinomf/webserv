//This file contains the methods related to processing DELETE requests

#include "MsgProcessor.hpp"

std::string MsgProcessor::deleteRequestedFile(std::string requestURI, Configs& conf)
{
    std::string filePath = conf.rootDir;
    filePath.append(std::string(requestURI));

    if (std::remove(filePath.c_str()) != 0)
        switch (errno)
        {
            case ENOENT: return responseToString(buildNotFoundResponse()); // file not found
            case EACCES: return responseToString(buildForbiddenResponse()); // permission denied
                default: return responseToString(buildInternalErrorResponse()); // internal error
        }
    return responseToString(buildNoContentResponse());
}

std::string MsgProcessor::workOnDELETEMethod(HTTPRequest& req, Configs& conf)
{
    std::string requestURI = req.getRequestURI();
    unsigned int i = requestURI.find("?");
    if (i != std::string::npos)
        requestURI = requestURI.substr(0, i);
    if (false) // (!conf.methodAllowedForRoute(requestURI, "DELETE")) MOCK
        return responseToString(buildForbiddenResponse());
    if (requestURI.c_str()[strlen(requestURI.c_str()) - 1] == '/')
        //return workOnDirectoryRequest(requestURI, conf);
        return "";
    else
        return deleteRequestedFile(requestURI, conf);
}