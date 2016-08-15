/* ========= PRODUCT INFORMATION  =========== */
#define FW_REVISION 3
#define FW_NAME "Clock Counter Test"
/* -------------------- */

#define TOTAL_LOOP 1000
#define FREQUENCY 160

#include <ESP8266WiFi.h> 

// Expose Espressif SDK functionality - wrapped in ifdef so that it still
// compiles on other platforms
#ifdef ESP8266
extern "C" {
#include "user_interface.h"
}
#endif

unsigned long startClockCounter1us =0;
unsigned long stopClockCounter1us=0;

unsigned long startClockCounter2us =0;
unsigned long stopClockCounter2us=0;

unsigned long startClockCounter5us =0;
unsigned long stopClockCounter5us=0;

unsigned long startClockCounter10us =0;
unsigned long stopClockCounter10us=0;

unsigned long startClockCounter30us =0;
unsigned long stopClockCounter30us =0;

unsigned long startClockCounter100us =0;
unsigned long stopClockCounter100us=0;

unsigned long loopClockCounterStart=0;
unsigned long loopClockCounterStop=0;
unsigned long loopCounter=0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); 
  delay(20);
  Serial.println("---- SERIAL TEST -----");
  Serial.print("FW Name: ");
  Serial.println(FW_NAME);
  Serial.print("FW Revision: ");
  Serial.println(FW_REVISION);
  Serial.println("-----------------------");

  WiFi.forceSleepBegin();                                   // turn off ESP8266 RF
  delay(1);                                                 // give RF section time to shutdown                                              // generally same as delay(1) but inconsistent
  system_update_cpu_freq(FREQUENCY); 

}

void loop() {
  if(loopCounter==0)
    loopClockCounterStart = ESP.getCycleCount();
    
  if(loopCounter<TOTAL_LOOP){
    loopCounter++;
  }else{
    if(loopCounter==TOTAL_LOOP){
    loopClockCounterStop = ESP.getCycleCount();
    
    startClockCounter1us = ESP.getCycleCount();
    delayMicroseconds(1);
    stopClockCounter1us = ESP.getCycleCount();
    Serial.print("clock count 1uS : ");
    Serial.println(stopClockCounter1us-startClockCounter1us);

    startClockCounter2us = ESP.getCycleCount();
    delayMicroseconds(2);
    stopClockCounter2us = ESP.getCycleCount();
    Serial.print("clock count 2uS : ");
    Serial.println(stopClockCounter2us-startClockCounter2us);

     startClockCounter5us = ESP.getCycleCount();
    delayMicroseconds(5);
    stopClockCounter5us = ESP.getCycleCount();
    Serial.print("clock count 5uS : ");
    Serial.println(stopClockCounter5us-startClockCounter5us);

    startClockCounter10us = ESP.getCycleCount();
    delayMicroseconds(10);
    stopClockCounter10us = ESP.getCycleCount();
    Serial.print("clock count 10uS : ");
    Serial.println(stopClockCounter10us-startClockCounter10us);

    startClockCounter30us = ESP.getCycleCount();
    delayMicroseconds(30);
    stopClockCounter30us = ESP.getCycleCount();
    Serial.print("clock count 30uS : ");
    Serial.println(stopClockCounter30us-startClockCounter30us);

    startClockCounter100us = ESP.getCycleCount();
    delayMicroseconds(100);
    stopClockCounter100us = ESP.getCycleCount();
    Serial.print("clock count 100us : ");
    Serial.println(stopClockCounter100us-startClockCounter100us);

    unsigned long totalcycles = loopClockCounterStop-loopClockCounterStart;
    double cyclePerLoop = totalcycles/(double)TOTAL_LOOP;
    Serial.print("total Loop : ");
    Serial.println(TOTAL_LOOP);
    Serial.print("total clock counter : ");
    Serial.println(totalcycles);

    Serial.print("clock cycle per loop : ");
    Serial.println(cyclePerLoop);
    Serial.println("Test terminated.  Press Reset to return.");
    loopCounter++;
   }else{
    yield();
    delay(10);
   }
    
  }
        
  
  

}
