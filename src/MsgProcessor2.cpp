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
    std::cout << "requestURI = " << requestURI << std::endl;
    if (requestURI.c_str()[strlen(requestURI.c_str()) - 1] == '/')
    {
        // code related to directory being requested
        return getRequestedFile("/index.html", conf);
    }
    else
        return getRequestedFile(requestURI, conf);
}