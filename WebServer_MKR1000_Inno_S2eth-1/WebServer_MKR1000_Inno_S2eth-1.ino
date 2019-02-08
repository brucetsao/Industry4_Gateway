#include <WiFi101.h>
#include "arduino_secrets.h" 
#include <SPI.h>
#include <String.h>
boolean  RelayMode[4]= { false,false,false,false} ;


///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;            // your network key Index number (needed only for WEP)
int status = WL_IDLE_STATUS;

IPAddress deviceip(192,168,88,177);
IPAddress  RelayDevice(192,168,88,152) ;
int  RelayDevicePort = 502 ;
//------------------IP DataEthernetClient

uint8_t TurnOn[4][8] = { 
                          {0x01,0x05,0x00,0x00,0xFF,0x00,0x8C,0x3A} ,
                          {0x01,0x05,0x00,0x01,0xFF,0x00,0xDD,0xFA} ,
                          {0x01,0x05,0x00,0x02,0xFF,0x00,0x2D,0xFA} ,
                          {0x01,0x05,0x00,0x03,0xFF,0x00,0x7C,0x3A} ,
                          } ;
    
uint8_t TurnOff[4][8] = { 
                          {0x01,0x05,0x00,0x00,0x00,0x00,0xCD,0xCA} ,
                          {0x01,0x05,0x00,0x01,0x00,0x00,0x9C,0x0A} ,
                          {0x01,0x05,0x00,0x02,0x00,0x00,0x6C,0x0A} ,
                          {0x01,0x05,0x00,0x03,0x00,0x00,0x3D,0xCA}
                          } ;

 // Please update IP address according to your local network
String MacData ;
WiFiServer server(80);
 String currentLine = "";                // make a String to hold incoming data from the client
  WiFiClient client;
WiFiClient client1;
              
void setup() {
   Serial.begin(9600);
     Serial.println("MKR1000 Ethernet to Modbus Gateway Start") ;
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
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(1000);
  }
    server.begin();  
  Serial.println("Connected to wifi");
  printWiFiStatus();
MacData = GetMacAddress() ;
}

void loop() {
  // if you get a connection, report back via serial:
      {// this codeblock process Web Server
       client = server.available();   // listen for incoming clients
              
                if (client)
                {                             // if you get a client,
                  Serial.println("new client");           // print a message out the serial port
                  currentLine = "";                // make a String to hold incoming data from the client
                  Serial.println("clear content");           // print a message out the serial port
                  while (client.connected()) 
                  {            // loop while the client's connected
                    if (client.available()) 
                    {             // if there's bytes to read from the client,
                      char c = client.read();             // read a byte, then
                      Serial.write(c);                    // print it out the serial monitor
                   //   Serial.print("@") ;
                      if (c == '\n') 
                      {                    // if the byte is a newline character
                        // Serial.print("~") ;
                        // if the current line is blank, you got two newline characters in a row.
                        // that's the end of the client HTTP request, so send a response:
                        if (currentLine.length() == 0) 
                        {
                          // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
                          // and a content-type so the client knows what's coming, then a blank line:
                          client.println("HTTP/1.1 200 OK");
              
                          client.println("Content-type:text/html");
                          client.println();
              
                         client.print("<title>WebServer Control Modbus TCP Relay</title>");
                          client.println();
                                        client.print("<html>");
                                        client.println();
               //                         client.print("<body>");
               //                         client.println();
               //----------control code start--------------------
                                        // the content of the HTTP response follows the header:
                                        client.print("<p>Relay 1") ; 
                                        if (RelayMode[0])
                                            {
                                                client.print("(ON)") ; 
                                            }
                                              else
                                            {
                                                client.print("(OFF)") ; 
                                            }
                                              
                                        client.print(":") ; 
                                        client.print("<a href='/1A'>Open</a>") ;
                                        client.print("/") ; 
                                        client.print("<a href='/1B'>Close</a>") ;
                                        client.print("</p>");
                                        client.print("<p>Relay 2") ; 
                                        if (RelayMode[1])
                                            {
                                                client.print("(ON)") ; 
                                            }
                                              else
                                            {
                                                client.print("(OFF)") ; 
                                            }
                                              
                                        client.print(":") ; 
                                        client.print("<a href='/2A'>Open</a>") ;
                                        client.print("/") ; 
                                        client.print("<a href='/2B'>Close</a>") ;
                                        client.print("</p>");
                                        client.print("<p>Relay 3") ; 
                                        if (RelayMode[2])
                                            {
                                                client.print("(ON)") ; 
                                            }
                                              else
                                            {
                                                client.print("(OFF)") ; 
                                            }
                                              
                                        client.print(":") ; 
                                        client.print("<a href='/3A'>Open</a>") ;
                                        client.print("/") ; 
                                        client.print("<a href='/3B'>Close</a>") ;
                                        client.print("</p>");
                                        client.print("<p>Relay 4") ; 
                                        if (RelayMode[3])
                                            {
                                                client.print("(ON)") ; 
                                            }
                                              else
                                            {
                                                client.print("(OFF)") ; 
                                            }
                                              
                                        client.print(":") ; 
                                        client.print("<a href='/4A'>Open</a>") ;
                                        client.print("/") ; 
                                        client.print("<a href='/4B'>Close</a>") ;
                                        client.print("</p>");
              //----------control code end                               
                   //                     client.print("</body>");
                    //                    client.println();
                                        client.print("</html>");
                                        client.println();
              
                          // The HTTP response ends with another blank line:
                          client.println();
                          // break out of the while loop:
                          break;
                        }     // end of if (currentLine.length() == 0) 
                        else 
                        {    // if you got a newline, then clear currentLine:
                              // here new line happen
                              // so check string is GET Command
                               CheckConnectString() ;
                              currentLine = "";
                               // Serial.println("get new line so empty String") ;
                        }   // end of if (currentLine.length() == 0) (for else)
                      }     // end of  if (c == '\n') 
                      else if (c != '\r') 
                      {  // if you got anything else but a carriage return character,
                        currentLine += c;      // add it to the end of the currentLine
                      }     // end of  if (c == '\n') 
                  // close the connection:
                         
              
                    }   // end of if (client.available()) 
                      // inner while loop
                  }     // end of while (client.connected()) 
                        
                    //  Serial.println("'while end'");  
              
                  client.stop();
                  Serial.println("client disonnected");
                }   //end of   if (client)
                // bottome line of loop()
      }   //  END OF webserver codeblock



  delay(1000);
}

void CheckConnectString()
{
                  // Check to see if the client request was "GET /HN or "GET /LN":
       //     Serial.print("#") ;
       //     Serial.print("!");
       //     Serial.print(currentLine);

      //      Serial.print("!\n");
         //    Serial.println("Enter to Check Command");
         //  this is relay n control for nA  is relay n Turn on
         //  this is relay n control for nB  is relay n Turn off
        if (currentLine.startsWith("GET /1A")) 
        {
              Serial.println("1A") ;
              RelayMode[0] = true ;  
              TurnOnRelay(0);               
        }
        if (currentLine.startsWith("GET /1B")) 
        {
              Serial.println("1B") ;
              RelayMode[0] = false ;  
              TurnOffRelay(0);               
        }
         //  this is relay n control for nA  is relay n Turn on
         //  this is relay n control for nB  is relay n Turn off
        if (currentLine.startsWith("GET /2A")) 
        {
              Serial.println("2A") ;
              RelayMode[1] = true ;  
              TurnOnRelay(1);               
        }
        if (currentLine.startsWith("GET /2B")) 
        {
              Serial.println("2B") ;
              RelayMode[1] = false ;  
              TurnOffRelay(1);               
        }
         //  this is relay n control for nA  is relay n Turn on
         //  this is relay n control for nB  is relay n Turn off
        if (currentLine.startsWith("GET /3A")) 
        {
              Serial.println("3A") ;
              RelayMode[2] = true ;  
              TurnOnRelay(2);               
        }
        if (currentLine.startsWith("GET /3B")) 
        {
              Serial.println("3B") ;
              RelayMode[2] = false ;  
              TurnOffRelay(2);               
        }
         //  this is relay n control for nA  is relay n Turn on
         //  this is relay n control for nB  is relay n Turn off
        if (currentLine.startsWith("GET /4A")) 
        {
              Serial.println("4A") ;
              RelayMode[3] = true ;  
              TurnOnRelay(3);               
        }
        if (currentLine.startsWith("GET /4B")) 
        {
              Serial.println("4B") ;
              RelayMode[3] = false ;  
              TurnOffRelay(3);               
        }
        //-----------------
}
void TurnOnRelay(int no)
{
    if (client1.connect(RelayDevice, RelayDevicePort)) 
    {
       client1.write(&TurnOn[no][0],sizeof(TurnOn[no])) ;
      client1.write(0x0a) ;
      client1.stop() ;   
    }
      else
  {
      Serial.println("Turn On Fail Connect") ;
      }
}

void TurnOffRelay(int no)
{
    if (client1.connect(RelayDevice, RelayDevicePort)) 
    {
       client1.write(&TurnOff[no][0],sizeof(TurnOff[no])) ;
      client1.write(0x0a) ; 
      client1.stop() ;     
    }
      else
  {
      Serial.println("Turn Off Fail Connect") ;
      }

}


void printWiFiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

String GetMacAddress() {
  // the MAC address of your WiFi shield
  String Tmp = "" ;
  byte mac[6];
  
  // print your MAC address:
  WiFi.macAddress(mac);
  for (int i=0; i<6; i++)
    {
        Tmp.concat(print2HEX(mac[i])) ;
    }
    Tmp.toUpperCase() ;
  return Tmp ;
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
  return ttt ;
}


