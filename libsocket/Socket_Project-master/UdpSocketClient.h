//
//  UdpSocketClient.h
//  Socket_Project
//
//  Created by Fabien on 20/05/2014.
//  Copyright (c) 2014 ___EFREI-GENET-BOURGEAUX-LE_VAN___. All rights reserved.
//

#ifndef __Socket_Project__UdpSocketClient__
#define __Socket_Project__UdpSocketClient__

#include <iostream>
#include "UdpSocket.h"

using namespace std;

class UdpSocketClient : public UdpSocket {
private:
    
public:
    UdpSocketClient();
    
    virtual ~UdpSocketClient();
    
    bool sendMsg(const string& s, const string& host, const int port);
    bool recvMsg(string& s);
};


#endif /* defined(__Socket_Project__UdpSocketClient__) */
