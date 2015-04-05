//
//  TcpSocket.cpp
//  Socket_Project
//
//  Created by Fabien on 12/05/2014.
//  Copyright (c) 2014 ___EFREI-GENET-BOURGEAUX-LE_VAN___. All rights reserved.
//

#include "TcpSocket.h"

TcpSocket::TcpSocket() : Socket()
{}

TcpSocket::~TcpSocket() {
    close(_sock);
}

void TcpSocket::create()
{
    _sock = socket (AF_INET,SOCK_STREAM, 0 );
}

bool TcpSocket::bind ( const int port )
{
    _addr.sin_family = AF_INET;
    _addr.sin_addr.s_addr = htonl(INADDR_ANY);
    _addr.sin_port = htons (port);
    
    if(::bind ( _sock,( struct sockaddr * ) &_addr, sizeof ( _addr ) ) == -1){
        perror("bind() error ");
        return false;
    }
    
    return true;
}

bool TcpSocket::listen() const
{
    if(::listen ( _sock, MAXCONNECTIONS ) == -1){
        perror("listen() error ");
        return false;
    }
    
    //setsockopt(_sock, SOL_SOCK, SO_NOSIGPIPE, (void *)&i, sizeof(i));
    return true;
}

bool TcpSocket::accept ( TcpSocket& recv ) const
{
    int addr_length = sizeof (_addr );
    recv._sock = ::accept ( _sock, ( sockaddr * ) &_addr, ( socklen_t * ) &addr_length );
    
    if ( recv._sock <= 0 )
        return false;
    else
        return true;
}

bool TcpSocket::connect ( const std::string& host, const int port )
{
    _addr.sin_family = AF_INET;
    _addr.sin_port = htons ( port );
    //_addr.sin_addr = *(IN_ADDR *) host.c_str();
    inet_pton ( AF_INET, host.c_str(), &_addr.sin_addr );
    
    if(::connect ( _sock, ( sockaddr * ) &_addr, sizeof ( _addr )) == 0)
        return true;
    
    return false;
}

bool TcpSocket::send (const string& s) const
{
    int r = ::send ( _sock, s.c_str(), s.size(), 0 );
    if(r == 0){
        perror("send () error (deconnexion) ");
        return false;
    }
    else if(r < 0) {
        perror("send () error : ");
        return false;
    }
    
    return true;
}

bool TcpSocket::recv (string& s) const
{
    char buf [ MAXRECV + 1 ];
    memset ( buf, 0, MAXRECV + 1 );
    if(::recv ( _sock, buf, MAXRECV, 0 ) <= 0 ){
        perror("Erreur de reception() error ");
        return false;
    }
    s.clear();
    s = buf;
    
    return true;
}

bool TcpSocket::sendFile(string const &fileName){
/*    if(!isConnected())
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
*/
}

bool TcpSocket::readFile() {
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

bool TcpSocket::isConnected() {
    int error = 0;
    socklen_t len = sizeof (error);
    if(getsockopt (_sock, SOL_SOCKET, SO_ERROR, &error, &len ) == 0)
        return true;
    return false;
}
