//This file contains the methods related to processing DELETE requests

#include "MsgProcessor.hpp"

bool    hasWritePermission(const char* path)
{
    struct stat fileStat;
    if (stat(path, &fileStat) == 0)
        return ((fileStat.st_mode & S_IWUSR) != 0);
    return false;
}

std::string MsgProcessor::deleteRequestedFile(std::string requestURI, Configs& conf)
{
    std::string filePath = conf.rootDir;
    filePath.append(std::string(requestURI));

    if (!hasWritePermission(filePath.c_str()))
            return responseToString(buildForbiddenResponse()); // permission denied

    if (unlink(filePath.c_str()) != 0)
        switch (errno)
        {
            case ENOENT: return responseToString(buildNotFoundResponse()); // file not found
            case EACCES: return responseToString(buildForbiddenResponse()); // permission denied
            case EISDIR: return responseToString(buildConflictResponse()); // not a file but a directory
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
        return workOnDeleteDirectory(requestURI, conf);
    else
        return deleteRequestedFile(requestURI, conf);
}

std::string MsgProcessor::workOnDeleteDirectory(std::string& requestURI, Configs& conf)
{
    std::string filePath = conf.rootDir;
    filePath.append(std::string(requestURI));

    if (!hasWritePermission(filePath.c_str()))
        return responseToString(buildForbiddenResponse()); // permission denied
    if (rmdir(filePath.c_str()) == 0)
        return responseToString(buildNoContentResponse()); // deletion success
    else
        return responseToString(buildInternalErrorResponse()); // internal error
}