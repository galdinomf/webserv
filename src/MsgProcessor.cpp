#include "MsgProcessor.hpp"

MsgProcessor::MsgProcessor(Configs& conf) : _serverConfigs(conf)
{

}

std::string MsgProcessor::workOnRequestAndGetResponse(HTTPRequest& req, Configs& conf)
{
	std::string method = req.getMethod();
	if (false) // replace with test for CGI request
	{
		// code related to incoming CGI request
	}
	else
	{
		if (method == "GET")
			return workOnGETMethod(req, conf);
		if (method == "DELETE")
			return workOnDELETEMethod(req, conf);
		if (method == "POST")
			return workOnPOSTMethod(req, conf);

	}
	return "";
}

std::string MsgProcessor::processRequest( std::string & msg )
{
    //int j;
	std::cout << "-------------- BEGIN OF MSG --------------" << std::endl;
std::cout << "msg = " << msg << std::endl;
	std::cout << "-------------- END OF MSG --------------" << std::endl;
	HTTPRequest	request;
	std::string	result = parse_request(request, msg);
	if (result != "")
		return result;
	/* Fazer 'parse_request' receber a mensagem e uma HTTPRequest vazia
	   por referência.
	   Fazer 'parse_request' retornar uma string. Essa string será vazia
	   caso o parsing não econtre problemas, e conterá a mensagem HTTP de
	   responsta caso haja um problema.
	   'parse_request' preencherá a HTTPRequest à medida que o parsing for
	   acontecendo.
	*/

	return workOnRequestAndGetResponse(request, _serverConfigs);

	//HTTPRequest	request(parse_request(std::string(msg)));

    // std::cout << "method = " << request.getMethod() << std::endl;
    // std::cout << "requestURI = " << request.getRequestURI() << std::endl;
    // std::cout << "version = " << request.getHTTPVersion() << std::endl;
    // std::map<std::string, std::string>::iterator it;
    // std::map<std::string, std::string> headers = request.getHeaders();
    // for (it = headers.begin(); it != headers.end(); ++it)
    //     std::cout << it->first << ": " << it->second << std::endl;
    // std::cout << "body = " << request.getBody() << std::endl;
	
    // HTTPResponse	response("200");

    // // std::cout << "msg = " << msg << "(REMOVE ME!!)" << std::endl;
	// // response with index.html
	// std::string indexAsString = "<!DOCTYPE html>\n<html lang=\"en\">\n<head>\n<meta charset=\"UTF-8\">\n<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n<title>Webserv</title>\n</head>\n<body>\n<h1>Webserv</h1>\n<h3>Hello from our web server!</h3>\n</body>\n</html>";
	// std::string responseAsString = "HTTP/1.1 200 OK\nContent-Type: text/html\nConnection: close\nContent-Length: ";
	// std::string	fileContentsAsString = "";

	// // responseAsString.append("259");
	// char buffer[256];
	// std::ifstream file("index.html");
	// if (!file.is_open())
	// 	std::cerr << "Error: could not open file" << std::endl;
	// else
	// 	while (file.read(buffer, sizeof(buffer)))
	// {
	// 	fileContentsAsString.append(buffer, file.gcount()); // this ensures the exact number of bytes extracted are appended
	// 	for (j = 0; (unsigned int) j < sizeof(buffer); j++)
	// 		buffer[j] = 0;
	// }
	// fileContentsAsString.append(buffer, file.gcount()); // last call to read() reads some data before exiting the loop
	
	// std::ostringstream oss;
	// oss << strlen(fileContentsAsString.c_str());
	// std::string contentLength(oss.str());
	// responseAsString.append(contentLength);
	// responseAsString.append("\r\n\r\n");
	// responseAsString.append(fileContentsAsString);
	// // std::cout << "responseAsString = " << responseAsString << std::endl;

    // return responseAsString;
}

std::string MsgProcessor::responseToString(HTTPResponse response)
{
    // build response's status line
    std::string responseAsString(response.getHTTPVersion());
    responseAsString.append(" ");
    responseAsString.append(response.getCode());
    responseAsString.append(" ");
    responseAsString.append(response.getText());
    responseAsString.append("\r\n");
    // append all headers
    std::map<std::string, std::string> m = response.getHeaders();
    std::map<std::string, std::string>::iterator it;
    for (it = m.begin(); it != m.end(); it++)
    {
        responseAsString.append(it->first);
        responseAsString.append(": ");
        responseAsString.append(it->second);
        responseAsString.append("\r\n");
    }
    //append body
    responseAsString.append("\r\n");
    responseAsString.append(response.getBody());

    return responseAsString;
}

HTTPResponse MsgProcessor::buildBadRequestResponse()
{
	HTTPResponse	response("400");
	std::map<std::string, std::string> m;

	m["Content-Type"] = "text/plain";
	m["Content-Length"] = "12";
	response.setBody("Bad request\n");
	response.setHeaders(m);

	// std::cout << "response.getBody() = " << response.getBody() << std::endl;
	return response;
}

HTTPResponse MsgProcessor::buildNotImplementedResponse()
{
	HTTPResponse	response("501");
	std::map<std::string, std::string> m;

	m["Content-Type"] = "text/html";
	m["Content-Length"] = "211";
	m["Connection"] = "close";
	response.setBody("\
	<!DOCTYPE html>\
	<html>\
	<head>\
		<title>501 Not Implemented</title>\
	</head>\
	<body>\
		<h1>Not Implemented</h1>\
		<p>The server does not support the functionality required to fulfill the request.</p>\
	</body>\
	</html>\n");
	response.setHeaders(m);

	return response;
}

HTTPResponse MsgProcessor::buildRequestURITooLongResponse()
{
	HTTPResponse	response("414");
	std::map<std::string, std::string> m;

	m["Content-Type"] = "text/html";
	m["Content-Length"] = "213";
	m["Connection"] = "close";
	response.setBody("\
	<!DOCTYPE html>\
	<html>\
	<head>\
		<title>414 Request-URI Too Long</title>\
	</head>\
	<body>\
		<h1>Request-URI Too Long</h1>\
		<p>The requested URL's length exceeds the capacity limit for this server.</p>\
	</body>\
	</html>\n");
	response.setHeaders(m);

	return response;
}

HTTPResponse MsgProcessor::buildForbiddenResponse()
{
	HTTPResponse	response("403");
	std::map<std::string, std::string> m;

	m["Content-Type"] = "text/html";
	m["Content-Length"] = "164";
	m["Connection"] = "close";
	response.setBody("\
	<!DOCTYPE html>\
	<html>\
	<head>\
		<title>403 Forbidden</title>\
	</head>\
	<body>\
		<h1>Forbidden</h1>\
		<p>Access to the requested resource is denied.</p>\
	</body>\
	</html>\n");
	response.setHeaders(m);
	return response;
}

HTTPResponse MsgProcessor::buildNotFoundResponse()
{
	HTTPResponse	response("404");
	std::map<std::string, std::string> m;

	m["Content-Type"] = "text/html";
	m["Content-Length"] = "168";
	m["Connection"] = "close";
	response.setBody("\
	<!DOCTYPE html>\
	<html>\
	<head>\
		<title>404 Not Found</title>\
	</head>\
	<body>\
		<h1>Not Found</h1>\
		<p>The requested URL was not found on this server.</p>\
	</body>\
	</html>\n");
	response.setHeaders(m);
	return response;
}

HTTPResponse MsgProcessor::buildConflictResponse()
{
	HTTPResponse	response("409");
	std::map<std::string, std::string> m;

	m["Content-Type"] = "text/html";
	m["Content-Length"] = "168";
	m["Connection"] = "close";
	response.setBody("\
	<!DOCTYPE html>\
	<html>\
	<head>\
		<title>409 Conflict</title>\
	</head>\
	<body>\
		<h1>Conflict</h1>\
		<p>A conflict occurred while processing the request.</p>\
	</body>\
	</html>\n");
	response.setHeaders(m);
	return response;
}

HTTPResponse MsgProcessor::buildOKResponse( std::string& content)
{
	HTTPResponse	response("200");
	std::map<std::string, std::string> m;

	int bodyLength = content.size();
	std::stringstream ss;
	ss << bodyLength;

	m["Content-Type"] = "text/html";
	m["Connection"] = "close";
	m["Content-Length"] = ss.str();
	response.setBody(content);
	response.setHeaders(m);
	return response;
}

HTTPResponse MsgProcessor::buildCreatedResponse( std::string& location )
{
	HTTPResponse	response("201");
	// std::map<std::string, std::string> m;
location.c_str();
	// m["Connection"] = "close";
	// m["Location"] = location;
	// response.setHeaders(m);
	std::cout << "response.getBody()" << response.getBody() << std::endl;
	return response;
}

HTTPResponse MsgProcessor::buildNoContentResponse()
{
	HTTPResponse	response("204");
	std::map<std::string, std::string> m;

	return response;
}

HTTPResponse MsgProcessor::buildInternalErrorResponse()
{
	HTTPResponse	response("500");
	std::map<std::string, std::string> m;

	m["Content-Type"] = "text/html";
	m["Content-Length"] = "212";
	m["Connection"] = "close";
	response.setBody("\
	<!DOCTYPE html>\
	<html>\
	<head>\
		<title>500 Internal Server Error</title>\
	</head>\
	<body>\
		<h1>Internal Server Error</h1>\
		<p>An unexpected error occurred on the server. Please try again later.</p>\
	</body>\
	</html>\n");
	response.setHeaders(m);
	return response;
}