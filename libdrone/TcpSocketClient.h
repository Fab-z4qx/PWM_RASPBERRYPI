//
//  SocketClient.h
//  Socket_Project
//
//  Created by Fabien on 07/05/2014.
//  Copyright (c) 2014 ___EFREI-GENET-BOURGEAUX-LE_VAN___. All rights reserved.
//

#ifndef __Socket_Project__TcpSocketClient__
#define __Socket_Project__TcpSocketClient__

#include <iostream>
#include "TcpSocket.h"

using namespace std;

class TcpSocketClient : public TcpSocket {
    
public:
    TcpSocketClient(const string& adresse, int port);
    virtual ~TcpSocketClient() {};
    
    bool sendMsg(const string& s);
    bool recvMsg(string& s);
    
    bool sendFile(const string &fileName);
};

#endif /* defined(__Socket_Project__TcpSocketClient__) */
