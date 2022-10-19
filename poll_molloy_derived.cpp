
/* 
Run: 
derek/chp06/GPIO/tests$ g++ test_syspoll.cpp GPIO.cpp -o test_syspoll -pthread

Reference: /chp06/GPIO/tests/test_syspoll.cpp
*/

#include<iostream>
#include<unistd.h> //for usleep
#include<chrono>
#include"GPIO.h"
using namespace exploringBB;
using namespace std;

int main(){
    struct timeval tv;
    int delay_us = 50;//50us

    // configure input and output
    GPIO outGPIO(44), inGPIO(45);
    inGPIO.setDirection(INPUT);    //ECHO is an input
    outGPIO.setDirection(OUTPUT);  //TRIGGER is an output
    //inGPIO.setEdgeType(FALLING);   //wait for falling edge
    cout<<"\nconfig done";

    // perform 100 measurements
    //for(int i=0;i<100;i++){
    int i=0;
    while(1)
    {
	cout<<endl<<"i "<<i++;
        std::chrono::high_resolution_clock::time_point start,end;
        long long delay_count=0.0;
        
        // trigger
        outGPIO.streamOpen();          //fast write, ready file
        usleep(10);
        outGPIO.streamWrite(LOW);      //turn the pin low

        // poll the echo pin to go high
        inGPIO.setEdgeType(RISING);   //wait for rising edge
        inGPIO.waitForEdge();          //will wait forever
        start = std::chrono::high_resolution_clock::now();

        // poll the echo pin to go low
        inGPIO.setEdgeType(FALLING);   //wait for falling edge
        inGPIO.waitForEdge();          //will wait forever
        end = std::chrono::high_resolution_clock::now();

        // calculate distance
        long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end-start).count();
        printf("\nDuration: %lld, dist:%f",microseconds,microseconds*0.034*0.5);

        usleep(1000*100);
    }
    cout<<endl<<"outta";
    // reset GPIO
    outGPIO.streamWrite(HIGH);     //button pressed, light LED
    outGPIO.streamClose();         //close the output stream
    return 0;
}

