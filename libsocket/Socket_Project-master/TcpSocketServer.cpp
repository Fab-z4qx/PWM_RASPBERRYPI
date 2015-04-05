//
//  SocketServer.cpp
//  Socket_Project
//
//  Created by Fabien on 07/05/2014.
//  Copyright (c) 2014 ___EFREI-GENET-BOURGEAUX-LE_VAN___. All rights reserved.
//

#include "TcpSocketServer.h"

TcpSocketServer::TcpSocketServer(int bindPort) : TcpSocket(){
    TcpSocket::create();
    TcpSocket::bind(bindPort);
    TcpSocket::listen();
}

TcpSocketServer::TcpSocketServer() : TcpSocket() {}

TcpSocketServer::~TcpSocketServer() {}

bool TcpSocketServer::sendMsg(const string& s) {
    
    if(!TcpSocket::send(s)){
        cout << "ERROR TO SEND MESSAGE" << endl;
        return false;
    }
    
    return true;
}

bool TcpSocketServer::recvMsg(string& s){
    
    if(!TcpSocket::recv(s)){
        cout << "ERROR TO READ MESSAGE " << endl;
        return false;
    }

    return true;
}

bool TcpSocketServer::readFile() {
    if(TcpSocket::isConnected())
        return TcpSocket::readFile();
    
    return true;
}

