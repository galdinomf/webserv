#include "MsgProcessor.hpp"

std::string MsgProcessor::processRequest( std::string & msg )
{
    int j;


	HTTPRequest	request(parse_request(std::string(msg)));

    std::cout << "method = " << request.getMethod() << std::endl;
    std::cout << "requestURI = " << request.getRequestURI() << std::endl;
    std::cout << "version = " << request.getHTTPVersion() << std::endl;
    std::map<std::string, std::string>::iterator it;
    std::map<std::string, std::string> headers = request.getHeaders();
    for (it = headers.begin(); it != headers.end(); ++it)
        std::cout << it->first << ": " << it->second << std::endl;
    std::cout << "body = " << request.getBody() << std::endl;
	
    HTTPResponse	response("200");

    std::cout << "msg = " << msg << "(REMOVE ME!!)" << std::endl;
	// response with index.html
	std::string indexAsString = "<!DOCTYPE html>\n<html lang=\"en\">\n<head>\n<meta charset=\"UTF-8\">\n<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n<title>Webserv</title>\n</head>\n<body>\n<h1>Webserv</h1>\n<h3>Hello from our web server!</h3>\n</body>\n</html>";
	std::string responseAsString = "HTTP/1.1 200 OK\nContent-Type: text/html\nConnection: close\nContent-Length: ";
	std::string	fileContentsAsString = "";

	// responseAsString.append("259");
	char buffer[256];
	std::ifstream file("index.html");
	if (!file.is_open())
		std::cerr << "Error: could not open file" << std::endl;
	else
		while (file.read(buffer, sizeof(buffer)))
	{
		fileContentsAsString.append(buffer, file.gcount()); // this ensures the exact number of bytes extracted are appended
		for (j = 0; (unsigned int) j < sizeof(buffer); j++)
			buffer[j] = 0;
	}
	fileContentsAsString.append(buffer, file.gcount()); // last call to read() reads some data before exiting the loop
	
	std::ostringstream oss;
	oss << strlen(fileContentsAsString.c_str());
	std::string contentLength(oss.str());
	responseAsString.append(contentLength);
	responseAsString.append("\r\n\r\n");
	responseAsString.append(fileContentsAsString);
	std::cout << "responseAsString = " << responseAsString << std::endl;

    return responseAsString;
}