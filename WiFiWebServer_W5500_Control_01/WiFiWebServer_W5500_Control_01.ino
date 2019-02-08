#include <SPI.h>
#include <Ethernet.h>
#if defined(WIZ550io_WITH_MACADDRESS) // Use assigned MAC address of WIZ550io
;
#else
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
#endif 


IPAddress deviceip(192,168,88,177);
IPAddress  RelayDevice(192,168,88,150) ;
int  RelayDevicePort = 6000 ;
//------------------IP DataEthernetClient
EthernetClient client;
uint8_t TurnOn[] =  {0x00, 0x21, 0x00, 0x00, 0x00, 0x06, 0x01, 0x05, 0x00, 0x00, 0xFF, 0x00}  ;
uint8_t TurnOff[] =  {0x00, 0x21, 0x00, 0x00, 0x00, 0x06, 0x01, 0x05, 0x00, 0x00, 0x00, 0x00}  ;
 // Please update IP address according to your local network
 
   
              
void setup() {
   Serial.begin(9600);
     Serial.println("W5500 Start") ;
 /*
  //Initialize serial and wait for port to open:
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // try to congifure using IP address instead of DHCP:
    Ethernet.begin(mac,deviceip);
  Serial.print("IP 位址：");
  Serial.println(Ethernet.localIP());

  }
  */
#if defined(WIZ550io_WITH_MACADDRESS)
  Ethernet.begin(deviceip);
#else
  Ethernet.begin(mac, deviceip);
#endif 
  Serial.print("IP 位址：");
  Serial.println(Ethernet.localIP());
  // you're connected now, so print out the status:
  Serial.println("Get IP") ;
}

void loop() {
  // if you get a connection, report back via serial:
  if (client.connect(RelayDevice, RelayDevicePort)) 
  {
    delay(20) ;
    Serial.println("connected to server");
    // Make a HTTP request:
    Serial.print("SEND(ON):(") ;
    Serial.print(sizeof(TurnOn)) ;
    Serial.print("):") ;
 ////   for (int i = 0 ; i < sizeof(TurnOn); i++)
     {
           client.write(&TurnOn[0],sizeof(TurnOn)) ;
 //    Serial.print(TurnOn[i],HEX) ;           
 //    Serial.print("/") ;
      }  
     Serial.print("@\n") ;      
   client.write(0x0a) ;

      delay(5000) ;
    Serial.print("SEND(OFF):(") ;
    Serial.print(sizeof(TurnOff)) ;
    Serial.print("):") ;      
 //   for (int i = 0 ; i < sizeof(TurnOff); i++)
 //     {
           client.write(&TurnOff[0],sizeof(TurnOff)) ;        
           //client.write(TurnOff[i]) ;
  //   Serial.print(TurnOn[i],HEX) ;           
   //  Serial.print("/") ;           
  //    }  
     Serial.print("@\n") ;      
   client.write(0x0a) ;      
      delay(5000) ;
      client.write(0x0a) ;
     client.stop() ;
  }
  else
  {
      Serial.println("Fail Connect") ;
      }

  delay(1000);#include <SPI.h>
#include <Ethernet.h>
#if defined(WIZ550io_WITH_MACADDRESS) // Use assigned MAC address of WIZ550io
;
#else
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
#endif 


IPAddress deviceip(192,168,88,177);
IPAddress  RelayDevice(192,168,88,150) ;
int  RelayDevicePort = 6000 ;
//------------------IP DataEthernetClient
EthernetClient client;
uint8_t TurnOn[] =  {0x00, 0x21, 0x00, 0x00, 0x00, 0x06, 0x01, 0x05, 0x00, 0x00, 0xFF, 0x00}  ;
uint8_t TurnOff[] =  {0x00, 0x21, 0x00, 0x00, 0x00, 0x06, 0x01, 0x05, 0x00, 0x00, 0x00, 0x00}  ;
 // Please update IP address according to your local network
 
   
              
void setup() {
   Serial.begin(9600);
     Serial.println("W5500 Start") ;
 /*
  //Initialize serial and wait for port to open:
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // try to congifure using IP address instead of DHCP:
    Ethernet.begin(mac,deviceip);
  Serial.print("IP 位址：");
  Serial.println(Ethernet.localIP());

  }
  */
#if defined(WIZ550io_WITH_MACADDRESS)
  Ethernet.begin(deviceip);
#else
  Ethernet.begin(mac, deviceip);
#endif 
  Serial.print("IP 位址：");
  Serial.println(Ethernet.localIP());
  // you're connected now, so print out the status:
  Serial.println("Get IP") ;
}

void loop() {
  // if you get a connection, report back via serial:
  if (client.connect(RelayDevice, RelayDevicePort)) 
  {
    delay(20) ;
    Serial.println("connected to server");
    // Make a HTTP request:
    Serial.print("SEND(ON):(") ;
    Serial.print(sizeof(TurnOn)) ;
    Serial.print("):") ;
 ////   for (int i = 0 ; i < sizeof(TurnOn); i++)
     {
           client.write(&TurnOn[0],sizeof(TurnOn)) ;
 //    Serial.print(TurnOn[i],HEX) ;           
 //    Serial.print("/") ;
      }  
     Serial.print("@\n") ;      
   client.write(0x0a) ;

      delay(5000) ;
    Serial.print("SEND(OFF):(") ;
    Serial.print(sizeof(TurnOff)) ;
    Serial.print("):") ;      
 //   for (int i = 0 ; i < sizeof(TurnOff); i++)
 //     {
           client.write(&TurnOff[0],sizeof(TurnOff)) ;        
           //client.write(TurnOff[i]) ;
  //   Serial.print(TurnOn[i],HEX) ;           
   //  Serial.print("/") ;           
  //    }  
     Serial.print("@\n") ;      
   client.write(0x0a) ;      
      delay(5000) ;
      client.write(0x0a) ;
     client.stop() ;
  }
  else
  {
      Serial.println("Fail Connect") ;
      }

  delay(1000);
}




}




