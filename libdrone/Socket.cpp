//
//  Socket.cpp
//  Socket_Project
//
//  Created by Fabien on 07/05/2014.
//  Copyright (c) 2014 ___EFREI-GENET-BOURGEAUX-LE_VAN___. All rights reserved.
//

#include "Socket.h"

Socket::Socket() : _sock( -1 )
{
    
#ifdef WIN32
    WSADATA wsa;
    int err = WSAStartup(MAKEWORD(2, 2), &wsa);
    if(err < 0){
        puts("WSAStartup failed !");
        exit(EXIT_FAILURE);
    }
#endif
    
    memset (&_addr,0,sizeof (_addr));
}

Socket::~Socket() {
    close(_sock);
    
#ifdef WIN32
    WSACleanup();
#endif
}


string getHostByHostname(const string& hostName){
    
    struct hostent *hostinfo = NULL;
    
    hostinfo = gethostbyname(hostName.c_str());
    if (hostinfo == NULL){
        cout << "Unknow host" << hostName << endl;
        exit(EXIT_FAILURE);
    }
    
    return hostinfo->h_addr;
}

/*
void Socket::create()
{
    _sock = socket ( AF_INET,SOCK_STREAM, 0 );
}

bool Socket::bind ( const int port )
{
    _addr.sin_family = AF_INET;
    _addr.sin_addr.s_addr = htonl(INADDR_ANY);
    _addr.sin_port = htons (port);
    
    if(::bind ( _sock,( struct sockaddr * ) &_addr, sizeof ( _addr ) ) == -1)
        return false;
    
return true;
}

bool Socket::listen() const
{
    if(::listen ( _sock, MAXCONNECTIONS ) == -1)
        return false;
    
return true;
}

bool Socket::accept ( Socket& recv ) const
{
    int addr_length = sizeof (_addr );
    recv._sock = ::accept ( _sock, ( sockaddr * ) &_addr, ( socklen_t * ) &addr_length );
    
    if ( recv._sock <= 0 )
        return false;
    else
        return true;
}

bool Socket::connect ( const std::string host, const int port )
{
    _addr.sin_family = AF_INET;
    _addr.sin_port = htons ( port );
    
    inet_pton ( AF_INET, host.c_str(), &_addr.sin_addr );
    if(::connect ( _sock, ( sockaddr * ) &_addr, sizeof ( _addr )) == 0)
       return true;
    
return true;
}

bool Socket::send ( const string s ) const
{
    if(::send ( _sock, s.c_str(), s.size(), 0 ) < 0)
        return false;
    
    return true;
}

bool Socket::recv ( string& s ) const
{
    char buf [ MAXRECV + 1 ];
    memset ( buf, 0, MAXRECV + 1 );
    if(::recv ( _sock, buf, MAXRECV, 0 ) <= 0 ){
        std::cout << "Error de reception" << endl;
        return false;
    }
    s.clear();
    s = buf;
    
return true;
}

bool Socket::sendFile(string const &fileName){
    if(!isConnected())
        return false;
    
    char buffer[MAXSEND];
    ifstream file (fileName, ios::binary);
    
    //ifstream file (fileName, std::ifstream::in);
    file.seekg (0, file.end);
    long length = file.tellg();
    file.seekg (0, file.beg);
    
    if (file) {
        while (!file.eof()) {
            file.read(buffer, MAXSEND);
            //cout << buffer << endl;
            send(buffer);
            memset(buffer,0, sizeof(buffer));
        }
    }
    else
        cout << "Erreur d'ouverture" << endl;
    
    file.close();                                                // Close
    
return true;
}

bool Socket::readFile() {
    if(!isConnected())
        return false;
    
    //char buffer[MAXRECV];
    ofstream fichier("output.txt", ios::out | ios::trunc);//ouverture en écriture avec effacement du fichier ouvert
    
    bool status = true;
    if(fichier)
    {
        while (isConnected() && status) { //Tant qu'on est connecté et sans error de reception
            string buffer;
            status = recv(buffer);
            fichier << buffer;
        }
    }
    else
        cerr << "Impossible d'ouvrir le fichier !" << endl;
    
    fichier.close();
    return true;
}

bool Socket::isConnected() {
    int error = 0;
    socklen_t len = sizeof (error);
    if(getsockopt (_sock, SOL_SOCKET, SO_ERROR, &error, &len ) == 0)
        return true;
    return false;
}
 */

