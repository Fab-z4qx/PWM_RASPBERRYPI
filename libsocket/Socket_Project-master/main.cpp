//
//  main.cpp
//  Socket_Project
//
//  Created by Fabien on 07/05/2014.
//  Copyright (c) 2014 ___EFREI-GENET. All rights reserved.
//

#include <iostream>
#include "main.h"

#define PORT 9999


void tcpServerTest() {
    
    TcpSocketServer s(9999);
    while ( true )
	{
        TcpSocketServer s2;
        s.accept ( s2 );
        
        while (s2.isConnected())
        {
            std::string data;
            s2.recv(data);
            cout << data << endl;
        }
	}
}

void tcpClientTest() {
    TcpSocketClient s("10.189.215.209", 9999);
    //s.sendFile("main.h");
    string mess;
    while(!(mess == "-1")) {
        cout << " : "; cin >> mess;
        s.send(mess);
    }
}

void tcpServerTestFile() {
    cout << "Mise en écoute" << endl;
    TcpSocketServer s(9999);
    
    bool status = true;
    while (status)
	{
        TcpSocketServer s2;
        s.accept ( s2 );
        status = s2.readFile();
	}
}

void udpServerTest(){
    UdpSocketServer s(9999);
    string buff;
    while(true) {
        s.recvMsg(buff);
        if(buff != "")
            cout << "Message : " << buff << endl;
    }
}

void udpClientTest() {
    UdpSocketClient s;
    string mess;
    while(!(mess == "-1")) {
        cout << " : "; cin >> mess;
    s.sendMsg(mess, "10.189.215.209", 9999);
    }
}
/* TESTT
void exerciceBServer() {
    double total_time=0.0;
    double start = clock(); //clock();
    string buff;
    
    UdpSocketServer s(3333);
    for(int i=0;i<1000;i++){
        buff.clear();
        s.recvMsg(buff);
        cout << "Message reçu : " << buff << endl;

        cout << "Envoi du message" << endl;
        s.sendMsg(buff,"127.0.0.1",3333);
    }
}

void exerciceBClient() {
    int size=1;
    //cout << "Witch size for your message [KB] : "; cin >> size; // 1KB
    string mess="";
    string buff;
    
    for (int i=0;i<size;i++){
        mess += "c";
    }
    
    UdpSocketClient s;
    for(int i=0;i<1000;i++)
    {
        s.sendMsg(mess, "127.0.0.1", 3333);
        cout << "Reception" << endl;
        
        s.recvMsg(buff);
        cout << "Message réçu" << buff << endl;
        buff.clear();
    }
}*/


void exerciceBServer() {
    double total_time=0.0;
    double start = 0; //clock();
    
    start = clock();
    for (int i=0;i<100;i++)
    {
    UdpSocketServer s(3333);
    string buff;
        s.recvMsg(buff);

    UdpSocketClient s2;
        total_time += (clock()-start);
        usleep(400);
        start = clock();
    s2.sendMsg(buff, s.getClientAddr() , 9999);
    }
    
    cout << "Temps Total/Total Time " << total_time/CLOCKS_PER_SEC << endl;
}


void exerciceBClient() {
    double total_time=0.0;
    double start = 0; //clock();
    
    int size;
    cout << "Which size for your message [KB] : "; cin >> size; // 1KB
    string mess="";
    
    for (int i=0;i<size;i++){
        mess += "c";
    }
    
    start = clock();
    for(int i=0;i<100;i++)
    {
    UdpSocketClient s;
    
        total_time += (clock()-start);
        usleep(400);
        start = clock();
        s.sendMsg(mess, "10.189.215.209", 3333);

    UdpSocketServer serv(9999);
    
    string buff;
    serv.recvMsg(buff);
        
    //if(buff != "")
        if(i%10 == 0)
            cout << "Message RCV : " << i << " / 100"  << endl;
    }
    cout << "Temps Total/Total time " << total_time/CLOCKS_PER_SEC << " s -> " << total_time/CLOCKS_PER_SEC*1000 << " ms " << endl;
    cout << "RTT = " << (total_time/CLOCKS_PER_SEC*1000)/100 << " ms" <<endl;

}

void exerciceCServer() {
    
    TcpSocketServer s(9999);
    TcpSocketServer s2;
    s.accept ( s2 );
    
    for(int i=0; i<100; i++)
    {
        string data;
        s2.recvMsg(data);
        //cout << data << endl;
        usleep(100);
        s2.sendMsg(data);
    }
    
}


void exerciceCClient() {
    TcpSocketClient s("10.189.215.209", 9999);
    
    double total_time=0.0;
    
    int size=0;
    cout << "Which size for your message [KB] : "; cin >> size; // 1KB
    string mess="";
    
    for (int i=0;i<size;i++){
        mess += "x";
    }

    double start = clock();
    for(int i =0; i<100;i++)
    {
        signal(SIGPIPE, SIG_IGN);
        usleep(100);
        s.sendMsg(mess);
        string data;
        s.recv(data);
        if(i%10 == 0)
            cout << "MESSAGE RECU(" << i << "/100) " << endl;
    }
    
    total_time = clock() - start;
    cout << "Temps Total/Total time " << total_time/CLOCKS_PER_SEC << " s -> " << total_time/CLOCKS_PER_SEC*1000 << " ms " << endl;
    cout << "RTT = " << (total_time/CLOCKS_PER_SEC*1000)/100 << " ms" <<endl;
    
}


int main(int argc, const char * argv[])
{
    signal(SIGPIPE, SIG_IGN);
    int choix =0;
    cout << "TCP Server = 1 " << endl;
    cout << "TCP Client = 2 " << endl;
    cout << "Udp Server = 3 " << endl;
    cout << "Udp Client = 4 " << endl;
    cout << "Exercice B Server (UDP) = 5 " << endl;
    cout << "Exercice B Client (UDP) = 6 " << endl;
    cout << "Exercice C Server (TCP) = 7" << endl;
    cout << "Exercice C Client (TCP) = 8" << endl;
    
    cout << "Quel Mode voulez vous choisir ? : "; cin >> choix;
    
    switch (choix) {
        case 1:
            tcpServerTest();
            break;
        case 2:
            tcpClientTest();
            break;
        case 3:
            udpServerTest();
            break;
        case 4:
            udpClientTest();
            break;
        case 5:
            exerciceBServer();
            break;
        case 6:
            exerciceBClient();
            break;
        case 7:
            exerciceCServer();
            break;
        case 8:
            exerciceCClient();
            break;

        default:
            cout << "ERROR UNKNOWN CHOOSE" << endl;
            break;
    }
}

