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
const std::string delimiter = ";";

void updatePwm(int channel, int value)
{
   int subcycle_time_us = SUBCYCLE_TIME_US_DEFAULT;   
   clear_channel_gpio(0, channel);
   init_channel(channel, subcycle_time_us);
   print_channel(channel);
   add_channel_pulse(channel,8,0, 100);
}

void parseString(std::string &data)
{
   size_t pos = 0;
   int i = 0;
   std::string token;
   while ((pos = data.find(delimiter)) != std::string::npos) 
   {
       token = data.substr(0, pos);
       std::cout << token << std::endl;
       data.erase(0, pos + delimiter.length());
       i++;
   }
   std::cout << data << std::endl;
   
   int channel;
   int value;
   switch(i)
   {
      case 1:
         channel = atoi(data.c_str());
      break;
      case 2:      
         value = atoi(data.c_str());
      break;
   }
   
   updatePwm(channel, value);
}

std::string encodeString(int channel, int value)
{
   string s;
   char channelstr[21], valuestr[21];
   sprintf(channelstr, "%d", channel);
   sprintf(valuestr, "%d", value);

   s = channelstr + delimiter + valuestr;

   return s; 
}

void initPwm()
{
    setup(PULSE_WIDTH_INCREMENT_GRANULARITY_US_DEFAULT, DELAY_VIA_PWM);
}

void tcpServerTest() 
{
    initPwm();    
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
	       parseString(data);
           }
	}
}

int main(int argc, const char * argv[])
{
    signal(SIGPIPE, SIG_IGN);
    tcpServerTest(); 
}

/*
int main(int argc, char **argv)
{
    // Very crude...
    if (argc == 2 && !strcmp(argv[1], "--pcm"))
        setup(PULSE_WIDTH_INCREMENT_GRANULARITY_US_DEFAULT, DELAY_VIA_PCM);
    else
        setup(PULSE_WIDTH_INCREMENT_GRANULARITY_US_DEFAULT, DELAY_VIA_PWM);
   

    setup(PULSE_WIDTH_INCREMENT_GRANULARITY_US_DEFAULT, DELAY_VIA_PWM);

    // Setup demo parameters
    int demo_timeout = 10 * 1000000;
    int gpio = 17;
    int channel = 0;
    int subcycle_time_us = SUBCYCLE_TIME_US_DEFAULT; //10ms;

    // Setup channel
    init_channel(channel, subcycle_time_us);
    print_channel(channel);

    // Use the channel for various pulse widths
   // add_channel_pulse(channel, gpio, 0, 50);
    //add_channel_pulse(channel, gpio, 100, 50);
    //add_channel_pulse(channel, gpio, 200, 50);
    //add_channel_pulse(channel, gpio, 300, 50);
    //usleep(demo_timeout);
        
    // Clear and start again
   // clear_channel_gpio(0, 17);
    add_channel_pulse(channel,8,0, 100);
    //add_channel_pulse(channel, gpio, 0, 50);
    //usleep(demo_timeout);

    while(1){
       ;
    }
    // All done
    shutdown();
    exit(0);
}
*/

