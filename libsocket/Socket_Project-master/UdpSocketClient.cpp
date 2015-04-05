//
//  UdpSocketClient.cpp
//  Socket_Project
//
//  Created by Fabien on 20/05/2014.
//  Copyright (c) 2014 ___EFREI-GENET-BOURGEAUX-LE_VAN___. All rights reserved.
//

#include "UdpSocketClient.h"

UdpSocketClient::UdpSocketClient() : UdpSocket() {
    
}

UdpSocketClient::~UdpSocketClient(){}

bool UdpSocketClient::sendMsg(const string& s, const string& host, const int port){
    if(UdpSocket::send(s,host,port))
        return true;
    
    return false;
}

bool UdpSocketClient::recvMsg(string& s){
    if(UdpSocket::recv(s))
        return true;
    
    return false;
}