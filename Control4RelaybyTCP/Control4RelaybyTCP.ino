/*
  Web Server

 A simple web server that shows the value of the analog input pins.
 using an Arduino Wiznet Ethernet shield.

 Circuit:
 * Ethernet shield attached to pins 10, 11, 12, 13
 * Analog inputs attached to pins A0 through A5 (optional)

 created 18 Dec 2009
 by David A. Mellis
 modified 9 Apr 2012
 by Tom Igoe
 modified 02 Sept 2015
 by Arturo Guadalupi

 */

#include <SPI.h>
#include <Ethernet.h>

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress IP(192, 168, 88, 166);
IPAddress RelayIP(192, 168, 88, 150);
uint16_t RelayPort = 6000 ;
char server[] = "192.168.88.150";    // name address for Google (using DNS)
// Initialize the Ethernet server library
// with the IP address and port you want to use
// (port 80 is default for HTTP):
EthernetClient client;

uint8_t cmd[2][12] = {  {0x00,0x21,0x00,0x00,0x00,0x06,0x01,0x05,0x00,0x00,0xFF,0x00} ,
                        {0x00,0x21,0x00,0x00,0x00,0x06,0x01,0x05,0x00,0x00,0x00,0x00} 
              };

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  Serial.println("Start Here") ;
  /*
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

*/
  // start the Ethernet connection and the server:
  Ethernet.begin(mac, IP);
 // Ethernet.begin(mac);

 PrintNetworkStatus() ;

  Serial.print("Board is at ");
  Serial.println(Ethernet.localIP());
}


void loop() {
    char key ;
  // listen for incoming clients
   if  (Serial.available() >0)
    {
        key = Serial.read() ;
          if (key == '1') 
                TurnOn(1) ;
          if (key == '2') 
                TurnOff(1) ;
             
    }
}

void TurnOn(int relaynumber)
  {
    int p=0 ;
       if (client.connect(RelayIP,RelayPort) )
            {
               if (client.available() >0)
                  {
                      Serial.print("R") ;
                      Serial.print(client.read() , HEX) ;
                      
                  }
                Serial.println("Turn on") ;
                     Serial.println("Before Write") ;
           //     for(int i=0 ; i <12; i++)
                  {

//                    client.write(cmd[0][0]) ; 
                    delayMicroseconds(50) ;
                    Serial.print(uint8_tArraytoString(&cmd[0][0],12) ) ;
                    client.write(&cmd[0][0],12) ;                     
                     delayMicroseconds(500) ;
                 }
                                  


                        Serial.println("After Write") ;
    while (client.available() >0)
        {
            Serial.print(":") ;
            Serial.print(print2HEX((int)client.read())) ;
            p++ ;
        }
      Serial.print("\n/") ;                  
      Serial.print(p) ;                  
      Serial.print("#\n") ;                  
                 client.stop() ;
            }

  }

void TurnOff(int relaynumber)
  {
    int p=0 ;
       if (client.connect(RelayIP,RelayPort) )
            {
               if (client.available() >0)
                  {
                      Serial.print("R") ;
                      Serial.print(client.read() , HEX) ;
                      
                  }
                Serial.println("Turn off") ;
                     Serial.println("Before Write") ;
           //     for(int i=0 ; i <12; i++)
                  {

//                    client.write(cmd[0][0]) ; 
                    delayMicroseconds(50) ;
                    Serial.print(uint8_tArraytoString(&cmd[1][0],12) ) ;
                    client.write(&cmd[1][0],12) ;                     
                     delayMicroseconds(500) ;
                 }
                                  


                        Serial.println("After Write") ;
    while (client.available() >0)
        {
            Serial.print(":") ;
            Serial.print(print2HEX((int)client.read())) ;
            p++ ;
        }
      Serial.print("\n/") ;                  
      Serial.print(p) ;                  
      Serial.print("#\n") ;                  
                 client.stop() ;
            }

  }

void PrintNetworkStatus()
{
    PrintMAC(&mac[0]) ;
    PrintIP() ;
    
}

void PrintIP()
{
      Serial.print("IP:") ;
    Serial.print(Ethernet.localIP()) ;
    Serial.println("") ;
}

void PrintMAC(byte *mc)
{
      Serial.print("MAC:") ;
    Serial.print(GetMAC(mc)) ;
    Serial.println("") ;
}

String GetMAC(byte *m)
{
      String tmp = "" ;
       for (int i = 0 ;  i < 6; i++)
          {
              tmp.concat( print2HEX( (int)*(m+i) )) ;
             if (i <5)
                tmp.concat("-") ;
          }
          tmp.toUpperCase() ;
      return  tmp ;
}


String  print2HEX(int number) {
  String ttt ;
  if (number >= 0 && number < 16)
  {
    ttt = String("0") + String(number,HEX);
  }
  else
  {
      ttt = String(number,HEX);
  }
  ttt.toUpperCase() ;
  return ttt ;
}

String uint8_tArraytoString(uint8_t *p, int len)
  {
      String tmp = "" ;
      for(int i = 0 ; i < len; i++)
          {
            tmp.concat(print2HEX( (int)*(p+i) ) ) ;
          }
      return tmp ;
  }

