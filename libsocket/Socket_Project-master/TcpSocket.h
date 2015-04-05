//
//  TcpSocket.h
//  Socket_Project
//
//  Created by Fabien on 12/05/2014.
//  Copyright (c) 2014 ___EFREI-GENET-BOURGEAUX-LE_VAN___. All rights reserved.
//

#ifndef __Socket_Project__TcpSocket__
#define __Socket_Project__TcpSocket__

#include <iostream>
#include <fstream> 
#include "Socket.h"

class TcpSocket : public Socket {
    
private :
    // int _sock;
    // sockaddr_in _addr;
    
public :
    TcpSocket();
    virtual ~TcpSocket();
    
    // Server initialization
    void create();
    bool bind ( const int port );
    bool listen() const;
    bool accept ( TcpSocket& ) const;
    
    // Client initialization
    bool connect ( const std::string& host, const int port );
    
    // Data Transimission
    bool send ( const std::string& ) const;
    bool recv ( std::string& ) const;
    
    bool sendFile(string const &fileName);
    bool readFile();
    
    bool isConnected();
    
    string getClientAddr() { string s(inet_ntoa(_addr.sin_addr));  return s; }
};


#endif /* defined(__Socket_Project__TcpSocket__) */
