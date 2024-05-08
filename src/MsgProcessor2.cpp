//This file contains the methods related to processing GET requests

#include "MsgProcessor.hpp"

std::string MsgProcessor::getRequestedFile(std::string requestURI, Configs& conf)
{
    std::string filePath = conf.rootDir;
    filePath.append(std::string(requestURI));
    std::string fileContentsAsString;
    char buffer[256];
	std::ifstream file(filePath.c_str());
    int j;
    
	if (!file.is_open())
        return  responseToString(buildNotFoundResponse());
	else
		while (file.read(buffer, sizeof(buffer)))
	{
		fileContentsAsString.append(buffer, file.gcount()); // this ensures the exact number of bytes extracted are appended
		for (j = 0; (unsigned int) j < sizeof(buffer); j++)
			buffer[j] = 0;
	}
	fileContentsAsString.append(buffer, file.gcount()); // last call to read() reads some data before exiting the loop
        return  responseToString(buildOKResponse(fileContentsAsString));
}

std::string MsgProcessor::workOnGETMethod(HTTPRequest& req, Configs& conf)
{    
    std::string requestURI = req.getRequestURI();
    unsigned int i = requestURI.find("?");
    if (i != std::string::npos)
        requestURI = requestURI.substr(0, i);
    if (false) //(!conf.methodAllowedForRoute(requestURI, "GET")) MOCK
        return responseToString(buildForbiddenResponse());
    if (requestURI.c_str()[strlen(requestURI.c_str()) - 1] == '/')
        return workOnDirectoryRequest(requestURI, conf);
    else
        return getRequestedFile(requestURI, conf);
}

std::string MsgProcessor::workOnDirectoryRequest(std::string& requestURI, Configs& conf)
{
    std::string result;

    std::string filePath = conf.rootDir;
    filePath.append(std::string(requestURI));

    DIR* dir = opendir(filePath.c_str()); // returns a pointer to a directory stream
    if (dir == NULL) // directory could not be opened
        return  responseToString(buildNotFoundResponse());
    
    chdir(filePath.c_str());
    std::string defaultFileName = conf.getDefaultFileNameForDirectory(requestURI);
    bool        dirListingOn = conf.directoryListingEnabled(requestURI);

    if (defaultFileName != "")
        result = getRequestedFile(requestURI.append(defaultFileName), conf);
    else
    {
        if (dirListingOn)
            result = writeDirectoryListing(dir);
        else
            result =  responseToString(buildNotFoundResponse());
    }
    closedir(dir);
    return result;
}

std::string MsgProcessor::writeDirectoryListing(DIR* dir)
{
    std::stringstream html;
    html << "<!DOCTYPE html>\n";
    html << "<html>\n<head>";
    html << "<style>table{width: 100%;}</style>";
    html << "</head>\n<body>\n";
    html << "<table>";
    html << "<a href=\"../\"> ../</a>\n";

    struct dirent* entry;
    struct stat fileInfo;

    while((entry = readdir(dir)) != NULL)
    {
        if ((std::strcmp(entry->d_name, ".") != 0) && (std::strcmp(entry->d_name, "..") != 0))
        {
            html << "<tr>";
            html << "<td>";
            html << "<a href=\"" << entry->d_name; // << "\">" << entry->d_name;
            if (entry->d_type == DT_DIR)
            {
                html << "/\">" << entry->d_name << "/";
                html << "</td>";
                html << "</a>";
            }
            else if (entry->d_type == DT_REG)
            {
                html << "\">" << entry->d_name;
                if (stat(entry->d_name, &fileInfo))
                    continue;
                html << "</td>";
                html << "</a>";
                html << "<td>" << fileInfo.st_size << "</td>";
                html << "<td>" << ctime(&fileInfo.st_mtime) << "</td>";
            }
            html << "</tr>";
        }
    }
    html << "</table>";
    html << "</body>\n</html>";
    std::string htmlString = html.str();
        return  responseToString(buildOKResponse(htmlString));
}