//
//  UdpSocket.h
//  Socket_Project
//
//  Created by Fabien on 12/05/2014.
//  Copyright (c) 2014 ___EFREI-GENET-BOURGEAUX-LE_VAN___. All rights reserved.
//

#ifndef __Socket_Project__UdpSocket__
#define __Socket_Project__UdpSocket__

#include "Socket.h"

class UdpSocket : public Socket {
    
private :
    sockaddr_in _clientAddr;
    
public :
    UdpSocket();
    virtual ~UdpSocket();
    
    // socket initialization
    void create();
    
    bool bind(int port);
    
    bool send (const string& s, const string& host, const int port) ;
    bool recv (string& buffer) ;
    
    string getClientAddr() { string s(inet_ntoa(_clientAddr.sin_addr));  return s; }
    
    
};

#endif /* defined(__Socket_Project__UdpSocket__) */
