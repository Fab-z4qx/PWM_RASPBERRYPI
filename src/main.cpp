
#include "main.h"

long int getNanoTime()
{
   timespec t;
   clock_gettime( CLOCK_REALTIME, &t );
   return t.tv_nsec;
}

int main( void )
{
     //volatile unsigned *gpio;
   volatile unsigned *gpio = setup_io();

   INP_GPIO( 8 );
   OUT_GPIO( 8 );

   while( true )
   {
      GPIO_SET = 1 << 8;
      usleep( 100 );
      GPIO_CLR = 1 << 8;
      usleep( 100 );
   }

return 0;
}

