//
//  SocketClient.cpp
//  Socket_Project
//
//  Created by Fabien on 07/05/2014.
//  Copyright (c) 2014 ___EFREI-GENET-BOURGEAUX-LE_VAN___. All rights reserved.
//

#include "TcpSocketClient.h"

TcpSocketClient::TcpSocketClient(const string& adresse, int port) : TcpSocket() {
    TcpSocket::create();
    if(!TcpSocket::connect(adresse,port)){
        cout << "Impossible de se connecter / Unable to connect" << endl;
        exit(EXIT_FAILURE);
    }
}


bool TcpSocketClient::sendMsg(const string& s){
    if(!TcpSocket::send(s)){
        cout << "Impossible d'envoyer le message / Uable to send message" << endl;
        return false;
    }
    return true;
}


bool TcpSocketClient::recvMsg(string& s){
    if(!TcpSocket::recv(s))
        return false;
    return true;
}

bool TcpSocketClient::sendFile(const string &fileName) {
    if(!TcpSocket::sendFile(fileName))
        return false;
    return false;
}