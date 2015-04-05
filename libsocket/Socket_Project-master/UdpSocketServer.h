//
//  UdpSocketServer.h
//  Socket_Project
//
//  Created by Fabien on 20/05/2014.
//  Copyright (c) 2014 ___EFREI-GENET-BOURGEAUX-LE_VAN___. All rights reserved.
//

#ifndef __Socket_Project__UdpSocketServer__
#define __Socket_Project__UdpSocketServer__

#include <iostream>
#include "UdpSocket.h"

class UdpSocketServer : public UdpSocket {
private:
    
public:
    UdpSocketServer(int bindPort);
    
    virtual ~UdpSocketServer();
    
    bool sendMsg(const string& s, const string& host, const int port);
    bool recvMsg(string& s);
};


#endif /* defined(__Socket_Project__UdpSocketServer__) */
