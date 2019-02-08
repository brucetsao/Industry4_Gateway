#include <SoftwareSerial.h>

unsigned char cmd[8][8] ={ {0x01,0x05,0x00,0x00,0xFF,0x00,0x8C,0x3A},
                      {0x01,0x05,0x00,0x00,0x00,0x00,0xCD,0xCA},
                      {0x01,0x05,0x00,0x01,0xFF,0x00,0xDD,0xFA},
                      {0x01,0x05,0x00,0x01,0x00,0x00,0x9C,0x0A},
                      {0x01,0x05,0x00,0x02,0xFF,0x00,0x2D,0xFA},
                      {0x01,0x05,0x00,0x02,0x00,0x00,0x6C,0x0A},
                      {0x01,0x05,0x00,0x03,0xFF,0x00,0x7C,0x3A},
                      {0x01,0x05,0x00,0x03,0x00,0x00,0x3D,0xCA} } ;
                          

boolean  RelayMode[4]= { false,false,false,false} ;
/*
Relay0 On:  01-05-00-00-FF-00-8C-3A
Relay0 Off: 01-05-00-00-00-00-CD-CA
Relay1 On:  01-05-00-01-FF-00-DD-FA
Relay1 Off: 01-05-00-01-00-00-9C-0A
Relay2 On:  01-05-00-02-FF-00-2D-FA
Relay2 Off: 01-05-00-02-00-00-6C-0A
Relay3 On:  01-05-00-03-FF-00-7C-3A
Relay3 Off: 01-05-00-03-00-00-3D-CA
 */
SoftwareSerial mySerial(0, 1); // RX, TX

void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600) ;
    mySerial.begin(9600) ;
    Serial.println("RS485 Test Start .....") ;
    
}

void loop() {
  // put your main code here, to run repeatedly:
    for(int i = 1 ; i <5; i++)
        {
            RelayControl(i,true) ;
             delay(10000) ;
            RelayControl(i,false) ;
             delay(10000) ;
             
        }
      
       
}

void RelayControl(int relaynnp, boolean  RM)
{
      
      if (RM)
      {
        Serial.print("Open ");
        Serial.print(relaynnp);
        Serial.print("\n");
          TurnOnRelay(relaynnp) ;
      }
      else
      {
        Serial.print("Close ");
        Serial.print(relaynnp);
        Serial.print("\n");

          TurnOffRelay(relaynnp) ;
      }
      
     

}
void TurnOnRelay(int relayno)
{
    for(int i = 0 ; i <8; i++)
        {
          mySerial.write(cmd[(relayno-1)][i]) ;
        }
        Serial.print("\nRelay :(") ;
        Serial.print(relayno) ;
        Serial.print(") \n\n") ;
        if (mySerial.available() >0)
          {
            while (mySerial.available() >0)
                {
                  Serial.print(mySerial.read() , HEX) ;
                } 
                
          }
    
}


void TurnOffRelay(int relayno)
{
    for(int i = 0 ; i <8; i++)
        {
          mySerial.write(cmd[(relayno-1)+1][i]) ;
        }
        Serial.print("Relay :(") ;
        Serial.print(relayno) ;
        Serial.print(") \n") ;
        if (mySerial.available() >0)
          {
            while (mySerial.available() >0)
                {
                  Serial.print(mySerial.read() , HEX) ;
                } 
                
          }
    
}

