#include<iostream>
#include<cstdlib>
#include<cstring>
#include<sys/socket.h>
#include<netdb.h>

int callSocket(int sockType, int family, int flags, char *port, 
                struct addrinfo **ai)
{
    struct addrinfo hints;
    struct addrinfo *p;
    int rv;
    int socketID;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = family;
    hints.ai_socktype = sockType;
    hints.ai_flags = flags;

    if ((rv = getaddrinfo(NULL, port, &hints, ai)) != 0)
    {
        std::cerr << "callSocket: " << gai_strerror(rv) << std::endl;
        exit(1);
    }

    for (p = *ai; p != NULL; p = p->ai_next)
    {
        socketID = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (socketID >= 0)
            return (socketID);
    }

    return (-1);
}