#include "HTTPServer.hpp"
#include <cerrno>
#include <cstring>

#include <fstream> // may be moved to another file
#include <sstream> // may be moved to another file

void	HTTPServer::_acceptNewConnection( fd_set *master, int *fdmax )
{
	int						newfd;		// newly accpet()ed socket descriptor
	struct sockaddr_storage remoteaddr;	// client address; struct large enough to hold both IPv4 and IPv6 structs
	socklen_t 				addrlen;

	addrlen = sizeof(remoteaddr);
	newfd = accept(_socket.getSocketID(), (struct sockaddr *)&remoteaddr, &addrlen);
	if (newfd == -1)
		std::cerr << "failed to accept incoming connection: " << strerror(errno) << std::endl;
	else
	{
		FD_SET(newfd, master); // add newfd to master set
		if (newfd > *fdmax) // keep track of the max
			*fdmax = newfd;
		std::cout << "Got a new connection!" << std::endl;
	}
}

void	HTTPServer::_closeAndClearSocket(int i, int nbytes, fd_set *master)
{
	if (nbytes == 0)
		std::cout << "select: socket " << i << " hung up" << std::endl;
	else
		std::cerr << "failed to receive data from socket " << i << ": " \
			<< strerror(errno) << std::endl;
	close(i);
	FD_CLR(i, master);
}

void	HTTPServer::_handleDataReceived(fd_set *master, int *nbytes, int fdmax, int i)
{
	int j;

	// this will become the handler function

	std::string	requestAsString(_dataBuffer);

	while	((*nbytes = recv(i, _dataBuffer, sizeof(_dataBuffer), 0)) > 0)
	{
		requestAsString.append(_dataBuffer, *nbytes);        
		if ((unsigned int) *nbytes < sizeof(_dataBuffer))
            break;
	}
	for (j = 0; (unsigned int) j < sizeof(_dataBuffer); j++)
		_dataBuffer[j] = 0;

	if (*nbytes == -1)
	{
		_closeAndClearSocket(i, *nbytes, master);
		return;
	}


	HTTPRequest	request(parse_request(std::string(requestAsString)));

    std::cout << "method = " << request.getMethod() << std::endl;
    std::cout << "requestURI = " << request.getRequestURI() << std::endl;
    std::cout << "version = " << request.getHTTPVersion() << std::endl;
    std::map<std::string, std::string>::iterator it;
    std::map<std::string, std::string> headers = request.getHeaders();
    for (it = headers.begin(); it != headers.end(); ++it)
        std::cout << it->first << ": " << it->second << std::endl;
    std::cout << "body = " << request.getBody() << std::endl;


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


	// responseAsString.append(indexAsString);
	int bytesSent = send(i, responseAsString.c_str(), strlen(responseAsString.c_str()), 0);
	if (bytesSent == -1)
		std::cerr << "error sending data: " << strerror(errno) << std::endl;

	}
}

int	HTTPServer::start()
{
	fd_set	master;		// master file descriptor list
	fd_set	read_fds;	// temp file descriptor list for select()
	int		fdmax;		// maximum file descriptor number

	//char	buf[256]; // buffer for client data
	int		nbytes;

	int	i;

	if (listen(_socket.getSocketID(), _backLog) == -1)
	{
		std::cerr << "Socket failed to listen: " << strerror(errno) << std::endl;
		return(1);
	}

	FD_ZERO(&master);
	FD_ZERO(&read_fds);
	FD_SET(_socket.getSocketID(), &master);
	fdmax = _socket.getSocketID();

	while (true)
	{
		read_fds = master;
		if (select(fdmax + 1, &read_fds, NULL, NULL, NULL) == -1)
		{
			std::cerr << "select: " << strerror(errno) << std::endl;
			return (2);
		}

		// run through the existing connections looking for data to read
		for (i = 0; i <= fdmax; i++)
		{
			if (FD_ISSET(i, &read_fds)) // file descriptor i ready to read data from
			{
				if (i == _socket.getSocketID()) // 'i' corresponds to a new connection incoming
					_acceptNewConnection(&master, &fdmax);
				else // 'i' corresponds to an existing connection
				{
					if	((nbytes = recv(i, _dataBuffer, sizeof(_dataBuffer), 0)) <= 0) // error or connection closed
						_closeAndClearSocket(i, nbytes, &master);
					else // got some data from a client
						_handleDataReceived(&master, &nbytes, fdmax, i);
				}
			}
		}
	}

	return (0);
}