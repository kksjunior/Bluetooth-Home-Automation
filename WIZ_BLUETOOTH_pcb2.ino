//-------------------------------------------------------------------------------//
//                                                                               //
// Arduino code to operate 4 relays remotely using HC-05 Bluetooth module        //
// Code uses EEPROM to store the relay state                                     //
// Coded by Prasanth KS (w!z) (kksjunior)                                        //
// www.instructables.com/member/kksjunior                                        //
// www.hackster.io/kksjunior                                                     //
//-------------------------------------------------------------------------------//

#include <EEPROM.h>
#include <SoftwareSerial.h>
SoftwareSerial wizbt(11, 10); // RX & TX configured using software serial
int r1=2; // Pin for triggering relay 1
int r2=4; // Pin for triggering relay 2
int r3=6; // Pin for triggering relay 3
int r4=8; // Pin for triggering relay 4
int ad1=1; //address for storing relay 1 status in the EEPROM
int ad2=2; //address for storing relay 2 status in the EEPROM
int ad3=3; //address for storing relay 3 status in the EEPROM
int ad4=4; //address for storing relay 4 status in the EEPROM
byte h; //
byte i; //
byte j; //
byte k; // Variables to store relay condition   
int powerled=12; // connection to power led
int statusled=13; // LED indicating BT connection status
char BluetoothData; // For recieving BT input

void setup()
{
  wizbt.begin(9600);
  pinMode (r1,OUTPUT);
  pinMode (r2,OUTPUT);
  pinMode (r3,OUTPUT);;
  pinMode (r4,OUTPUT);
  pinMode (powerled,OUTPUT);
  pinMode (statusled,OUTPUT);
  digitalWrite(powerled,HIGH);
  h = EEPROM.read(ad1);
  i = EEPROM.read(ad2);
  j = EEPROM.read(ad3);
  k = EEPROM.read(ad4);

// Initialising the Relays according to their last status written in the EEPROM.

//---------------------------------------------------------------------------------------------------//
// RELAY - 1
    
     if(h==1)
      {
       digitalWrite(r1,HIGH);
      }
     else if(h==0)
      {
       digitalWrite(r1,LOW);
      }
// RELAY - 2
     if(i==1)
      {
       digitalWrite(r2,HIGH);
      }
     else if(i==0)
      {
       digitalWrite(r2,LOW);
      }
// RELAY - 3
     if(j==1)
      {
       digitalWrite(r3,HIGH);
      }
     else if(j==0)
      {
       digitalWrite(r3,LOW);
      }
// RELAY - 4
     if(k==1)
      {
       digitalWrite(r4,HIGH);
      }
     else if(k==0)
      {
       digitalWrite(r4,LOW);
      }
//---------------------------------------------------------------------------------------------------//

}

void loop() 
{
 if (wizbt.available())
  {
    digitalWrite(statusled,HIGH);
    delay(100);
    digitalWrite(statusled,LOW);
    BluetoothData=wizbt.read();
    
// RELAY - 1
    
     if(BluetoothData=='A')
      {
       digitalWrite(r1,HIGH);
       EEPROM.write(ad1,1);
      }
     else if(BluetoothData=='B')
      {
       digitalWrite(r1,LOW);
       EEPROM.write(ad1,0);
      }
// RELAY - 2
     else if(BluetoothData=='X')
      {
       digitalWrite(r2,HIGH);
       EEPROM.write(ad2,1);
      }
     else if(BluetoothData=='Y')
      {
       digitalWrite(r2,LOW);
       EEPROM.write(ad2,0);
      }
// RELAY - 3
     else if(BluetoothData=='P')
      {
       digitalWrite(r3,HIGH);
       EEPROM.write(ad3,1);
      }
     else if(BluetoothData=='Q')
      {
       digitalWrite(r3,LOW);
       EEPROM.write(ad3,0);
      }
// RELAY - 4
     else if(BluetoothData=='M')
      {
       digitalWrite(r4,HIGH);
       EEPROM.write(ad4,1);
      }
     else if(BluetoothData=='N')
      {
       digitalWrite(r4,LOW);
       EEPROM.write(ad4,0);
      }
// MASTER SWITCH
     else if(BluetoothData=='U')
      {
       digitalWrite(r1,HIGH);
       EEPROM.write(ad1,1);
       digitalWrite(r2,HIGH);
       EEPROM.write(ad2,1);
       digitalWrite(r3,HIGH);
       EEPROM.write(ad3,1);
       digitalWrite(r4,HIGH);
       EEPROM.write(ad4,1);
      }
     else if(BluetoothData=='V')
      {
       digitalWrite(r1,LOW);
       EEPROM.write(ad1,0);
       digitalWrite(r2,LOW);
       EEPROM.write(ad2,0);
       digitalWrite(r3,LOW);
       EEPROM.write(ad3,0);
       digitalWrite(r4,LOW);
       EEPROM.write(ad4,0);
      }
     else
     {
      for(int i=0;i<5;i++)
      {
        digitalWrite(statusled,HIGH);
        delay(100);
        digitalWrite(statusled,LOW);
      }
     }
  }
delay(100);
}
