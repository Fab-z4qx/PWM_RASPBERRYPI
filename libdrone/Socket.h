//
//  Socket.h
//  Socket_Project
//
//  Created by Fabien on 07/05/2014.
//  Copyright (c) 2014 ___EFREI-GENET-BOURGEAUX-LE_VAN___. All rights reserved.
//

#ifndef __Socket_Project__Socket__
#define __Socket_Project__Socket__

#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define closesocket(s) close(s)

#include <iostream>
#include <string>
#include <fstream>
#include <string.h>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <cerrno>

typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;

//#ifdef WIN32 /* Windows */

//#include <winsock2.h>

//#elif (__APPLE__ || __UNIX__ || __UNIX || UNIX) /* Mac */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h> /* close */
#include <netdb.h> /* gethostbyname */

#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define closesocket(s) close(s)

//#else
//#error not defined for this platform

//#endif

const int MAXHOSTNAME = 2000;
const int MAXCONNECTIONS = 50;
const int MAXRECV = 1638400;
const int MAXSEND = 1638400;

using namespace std;

class Socket {
    
protected :
    int _sock;
    sockaddr_in _addr;
    
public :
    Socket();
    virtual ~Socket();
    
    string getHostByHostname(const string& hostName);
    
    /*
    // Server initialization
    void create();
    bool bind ( const int port );
    bool listen() const;
    bool accept ( Socket& ) const;
    
    // Client initialization
    bool connect ( const std::string host, const int port );
    
    // Data Transimission
    bool send ( const std::string ) const;
    bool recv ( std::string& ) const;
    
    bool sendFile(string const &fileName);
    bool readFile();
    
    bool isConnected(); */
};

#endif /* defined(__Socket_Project__Socket__) */
