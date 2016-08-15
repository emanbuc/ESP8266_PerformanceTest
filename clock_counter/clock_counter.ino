/* ========= PRODUCT INFORMATION  =========== */
#define FW_REVISION 2
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

unsigned long startClockCounter0 =0;
unsigned long stopClockCounter0=0;
unsigned long startClockCounter1 =0;
unsigned long stopClockCounter1=0;
unsigned long startClockCounter2 =0;
unsigned long stopClockCounter2=0;
unsigned long startClockCounter3 =0;
unsigned long stopClockCounter3=0;
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
    startClockCounter0 = ESP.getCycleCount();
    delayMicroseconds(1);
    stopClockCounter0 = ESP.getCycleCount();

    startClockCounter1 = ESP.getCycleCount();
    delayMicroseconds(10);
    stopClockCounter1 = ESP.getCycleCount();

    startClockCounter2 = ESP.getCycleCount();
    delayMicroseconds(100);
    stopClockCounter2 = ESP.getCycleCount();

    startClockCounter3 = ESP.getCycleCount();
    delayMicroseconds(1000);
    stopClockCounter3 = ESP.getCycleCount();

    Serial.print("clock count 1uS : ");
    Serial.println(stopClockCounter0-startClockCounter0);
    
    Serial.print("clock count 10uS : ");
    Serial.println(stopClockCounter1-startClockCounter1);

    Serial.print("clock count 100uS  : ");
    Serial.println(stopClockCounter2-startClockCounter2);

    Serial.print("clock count 1000uS : ");
    Serial.println(stopClockCounter3-startClockCounter3);

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
