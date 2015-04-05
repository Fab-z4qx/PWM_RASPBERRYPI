//
//  UdpSocketServer.cpp
//  Socket_Project
//
//  Created by Fabien on 20/05/2014.
//  Copyright (c) 2014 ___EFREI-GENET-BOURGEAUX-LE_VAN___. All rights reserved.
//

#include "UdpSocketServer.h"

UdpSocketServer::UdpSocketServer(int bindPort) : UdpSocket() {
    bind(bindPort);
}

UdpSocketServer::~UdpSocketServer(){}

bool UdpSocketServer::sendMsg(const string& s, const string& host, const int port){
    if(UdpSocket::send(s, host, port))
        return true;
    
    return false;
}

bool UdpSocketServer::recvMsg(string& s){
    if(UdpSocket::recv(s))
        return true;
    
    return false;
}