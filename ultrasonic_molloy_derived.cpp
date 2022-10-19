
/* 
Run: 
∼/exploringbb/chp06/GPIO$ g++ simple.cpp GPIO.cpp ‐o simple ‐pthread
∼/exploringbb/chp06/GPIO$ sudo ./simple
*/

#include<iostream>
#include<unistd.h> //for usleep
#include<chrono>
#include<sys/time.h>
#include"GPIO.h"
using namespace exploringBB;
using namespace std;

int main(){
   GPIO outGPIO(44), inGPIO(45);
   struct timeval tv;
   outGPIO.setDirection(OUTPUT);


   int delay_us = 50;//50us
   // Basic Input example
   inGPIO.setDirection(INPUT);
   while(1)
   {
        //double start, end;
        std::chrono::high_resolution_clock::time_point start,end;
        long long delay_count=0.0;

        // Trigger
        outGPIO.setValue(HIGH);
        usleep(10);
        outGPIO.setValue(LOW);

        // Poll for Echo pin to go HIGH
        while(inGPIO.getValue() == 0)
        {
                usleep(1000);
                start = std::chrono::high_resolution_clock::now();
        }
        while(inGPIO.getValue() == 1)
        {
                end = std::chrono::high_resolution_clock::now();
                usleep(delay_us);
                delay_count +=delay_us;
                //printf("\n!!getvalue==1");
        }
        // calculate distance
        long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end-start).count();
        printf("\nDuration: %lld, delay: %lld dist:%f",microseconds,delay_count,(microseconds+delay_count)*0.034*0.5);
        usleep(1000*100);
   }


   /*outGPIO.streamClose();*/

   return 0;
}
