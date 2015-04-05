//
//  SocketServer.h
//  Socket_Project
//
//  Created by Fabien on 07/05/2014.
//  Copyright (c) 2014 ___EFREI-GENET-BOURGEAUX-LE_VAN___. All rights reserved.
//

#ifndef __Socket_Project__TcpSocketServer__
#define __Socket_Project__TcpSocketServer__

#include <iostream>
#include "TcpSocket.h"

class TcpSocketServer: public TcpSocket {

private:
    
    
public :
    TcpSocketServer ( int bindPort );
    TcpSocketServer();
    
    virtual ~TcpSocketServer();
    
    bool sendMsg(const string& s);
    bool recvMsg(string& s);
    
    bool readFile();
};

#endif /* defined(__Socket_Project__TcpSocketServer__) */
