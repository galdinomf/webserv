#include "HTTPServer.hpp"
#include <cerrno>
#include <cstring>

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

void	HTTPServer::_handleDataReceived(fd_set *master, int nbytes, int fdmax, int i)
{
	int j;

	// this will become the handler function
		//send to everyone!
	for (j = 0; j <= fdmax; j++)
	{
		if (FD_ISSET(j, master))
		{
			if (j != _socket.getSocketID() && j != i)
				if (send(j, _dataBuffer, nbytes, 0) == -1)
					std::cerr << "error sendinfg data: " << strerror(errno) << std::endl;
		}
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
		std::cout << "strncmp(buf, exit, 4) = " << strncmp(_dataBuffer, "exit", 4) << std::endl;
		if (strncmp(_dataBuffer, "exit", 4) == 0)
			break;
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
						_handleDataReceived(&master, nbytes, fdmax, i);
				}
			}
		}
	}

	return (0);
}