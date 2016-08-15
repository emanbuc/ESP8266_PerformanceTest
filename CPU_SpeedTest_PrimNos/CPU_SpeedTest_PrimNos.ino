/*
  Based on:
  
  PrimeNos: by Nick Gammon
  ESP8266 Arduino port m. ray burnette
*/

extern "C" {
#include "user_interface.h"
}

#include <ESP8266WiFi.h>                                    // for the low power function
//#include <Streaming.h>
#define BOARD_LED_PIN  2
#define FREQUENCY     80                                    // valid 80, 160

// just add more primes to the prime table for larger search
// byte data type to save memory - use a larger datatype with prime table entries above 255 :)
byte primes[]= { 
    2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101,
    102, 107, 109, 113, 127, 131,  137 , 139, 149, 151, 157, 163, 167, 173,  179, 181, 191, 193, 197, 
    199, 211, 223, 227, 229, 233, 239, 241, 251 };

// if you change the datatype of primes array to int, change next line to 
// "const int TopPrimeIndex = (sizeof(primes)/2) - 1;"

const unsigned int  TopPrimeIndex = sizeof(primes) - 1;      
const unsigned long TopPrimeSquared = (long)primes[TopPrimeIndex] * (long)primes[TopPrimeIndex];
int primeFlag;
unsigned long t = 0;


void setup()                   
{
    
  WiFi.forceSleepBegin();                                   // turn off ESP8266 RF
  delay(1);                                                 // give RF section time to shutdown
  // yield();                                               // generally same as delay(1) but inconsistent
  //system_update_cpu_freq(FREQUENCY);                      //Override IDE CPU Frequency settings

  pinMode(BOARD_LED_PIN, OUTPUT);
  Serial.begin(115200);

  Serial.println(" --------------------- ");
  Serial.println("Prime Number Generator by Nick Gammon\r\n");
  Serial.println("ESP8266 port by Ray Burnette\r\n\r\n");
  Serial.print("Number of primes in prime table = ");
  Serial.println(TopPrimeIndex);
  Serial.print("Last prime in table =  ");
  Serial.println((unsigned int)primes[TopPrimeIndex]);
  Serial.print("Calculating primes through ");
  Serial.println(TopPrimeSquared);
  Serial.println("Starting uS timer now... ");
  t = micros();
}


void loop()
{
    for (long x = 1; x < TopPrimeSquared; x+=2)             // skips even numbers, including 2, which is prime, but it makes algorithm tad faster
      {
            for (long j=0; j < TopPrimeIndex; j++){
            primeFlag = true;

            if (x == primes[j]) break;

            if (x % primes[j] == 0){                        // if the test number modolo (next number from prime table) == 0 
                primeFlag = false;                          //  then test number is not prime, bailout and check the next number
                break;
            }
            delay(0);
        }
        if (primeFlag == true)                              // found a prime
        {
            digitalWrite(BOARD_LED_PIN,!digitalRead(BOARD_LED_PIN));
            yield();
            //Serial.println(x);
        }
      }
    unsigned long endtTime = micros()-t;
    Serial.print("Timer uS: ");
    Serial.println(endtTime);
    Serial.println("Test terminated.  Press Reset to rerun.");    
    for(;;) yield() ;                                       // infinite loop with yield to prevent WDT
}
