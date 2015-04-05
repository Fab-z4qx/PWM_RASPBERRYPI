//
//  UdpSocket.cpp
//  Socket_Project
//
//  Created by Fabien on 12/05/2014.
//  Copyright (c) 2014 ___EFREI-GENET-BOURGEAUX-LE_VAN___. All rights reserved.
//

#include "UdpSocket.h"

//
//  Socket.cpp
//  Socket_Project
//
//  Created by Fabien on 07/05/2014.
//  Copyright (c) 2014 ___EFREI-GENET-BOURGEAUX-LE_VAN___. All rights reserved.
//

#include "UdpSocket.h"

UdpSocket::UdpSocket() : Socket() {
    create();
}

UdpSocket::~UdpSocket() {
    close(_sock);
}

void UdpSocket::create()
{
    _sock = socket(AF_INET, SOCK_DGRAM, 0);
    if(_sock == INVALID_SOCKET){
        perror("socket()");
        exit(errno);
    }
    
    
}

bool UdpSocket::bind(int port){
    
    bzero(&_addr,sizeof(_addr));
    _addr.sin_family = AF_INET;
    _addr.sin_addr.s_addr = htonl(INADDR_ANY);
    _addr.sin_port = htons (port);
    
    if(::bind(_sock, (struct sockaddr *)&_addr, sizeof(_addr) ) == SOCKET_ERROR) {
        cout << "ERROR bind" << endl;
        perror("bind() error ");
        return false;
    }
    return true;
}

bool UdpSocket::recv(string& msg) {
    
    char buf [ MAXRECV + 1 ];
    memset ( buf, 0, MAXRECV + 1 );

    socklen_t addrLen = sizeof(_clientAddr);
    size_t n;
    if ((n = recvfrom(_sock,(void *)buf,sizeof(buf)-1,0,(sockaddr*)&_clientAddr,(socklen_t *) &addrLen)) == 0){
        return false;
    }
    
    msg.clear();
    msg = buf;
    return true;
}

bool UdpSocket::send(const string& msg, const std::string& host, const int port) {
    
    bzero(&_addr,sizeof(_addr));
    _addr.sin_family = AF_INET;
    _addr.sin_addr.s_addr = inet_addr(host.c_str());
    _addr.sin_port = htons(port);
    
    if(sendto(_sock, msg.c_str(), msg.size(), 0, (SOCKADDR *)&_addr, sizeof(_addr)) == SOCKET_ERROR){
        perror("Error to send your UDP message");
        return false;
    }
    
    return true;
}






