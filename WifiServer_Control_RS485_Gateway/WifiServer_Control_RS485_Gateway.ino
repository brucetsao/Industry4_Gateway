#include <SPI.h>
#include <WiFi101.h>

#include "arduino_secrets.h" 
///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;                 // your network key Index number (needed only for WEP)

int status = WL_IDLE_STATUS;
WiFiServer server(80);
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
 String currentLine = "";                // make a String to hold incoming data from the client
//WiFiClient myclient;

IPAddress gatewayip = IPAddress(192, 168, 88, 152) ;
int gatewayport = 502 ;

void setup() {
  Serial.begin(9600);      // initialize serial communication
  Serial.println("RS485 Gateway Test Start .....") ;

  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    while (true);       // don't continue
  }
  
  // attempt to connect to WiFi network:
  while ( status != WL_CONNECTED)
  {
    WiFi.config(IPAddress(192, 168, 88, 200)) ;
    Serial.print("Attempting to connect to Network named: ");
    Serial.println(ssid);                   // print the network name (SSID);

    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);
    // wait 10 seconds for connection:
    delay(4000);
  }
  server.begin();                           // start the web server on port 80
  printWiFiStatus();                        // you're connected now, so print out the status

      
      

}

void loop() {
 WiFiClient client = server.available();   // listen for incoming clients

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

           client.print("<title>Ameba AP Mode Control Relay</title>");
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
                          client.print("<a href='/A'>Open</a>") ;
                          client.print("/") ; 
                          client.print("<a href='/B'>Close</a>") ;
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
                          client.print("<a href='/C'>Open</a>") ;
                          client.print("/") ; 
                          client.print("<a href='/D'>Close</a>") ;
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
                          client.print("<a href='/E'>Open</a>") ;
                          client.print("/") ; 
                          client.print("<a href='/F'>Close</a>") ;
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
                          client.print("<a href='/G'>Open</a>") ;
                          client.print("/") ; 
                          client.print("<a href='/H'>Close</a>") ;
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
}   //end of loop()

void CheckConnectString()
{

        if (currentLine.startsWith("GET /A")) 
        {
              RelayMode[0] = true ;  
              RelayControl(1,RelayMode[0]);               
        }
        if (currentLine.startsWith("GET /B")) 
        {
              RelayMode[0] = false ;  
              RelayControl(1,RelayMode[0]);               
        }
        //-----------------
        if (currentLine.startsWith("GET /C")) 
        {
              RelayMode[1] = true ;  
              RelayControl(2,RelayMode[1]);               
        }
        if (currentLine.startsWith("GET /D")) 
        {
              RelayMode[1] = false ;  
              RelayControl(2,RelayMode[1]);               
        }
        //-----------------
        if (currentLine.startsWith("GET /E")) 
        {
              RelayMode[2] = true ;  
              RelayControl(3,RelayMode[2]);               
        }
        if (currentLine.startsWith("GET /F")) 
        {
              RelayMode[2] = false ;  
              RelayControl(3,RelayMode[2]);               
        }
        //-----------------
        if (currentLine.startsWith("GET /G")) 
        {
              RelayMode[3] = true ;  
              RelayControl(4,RelayMode[3]);               
        }
        if (currentLine.startsWith("GET /H")) 
        {
              RelayMode[3] = false ;  
              RelayControl(4,RelayMode[3]);               
        }
        //-----------------
}
void RelayControl(int relaynnp, boolean  RM)
{
      
      if (RM)
      {
        Serial.print("Open ");
        Serial.print(relaynnp);
        Serial.print("\n");
          TurnOnRelay(relaynnp-1) ;
      }
      else
      {
        Serial.print("Close ");
        Serial.print(relaynnp);
        Serial.print("\n");

          TurnOffRelay(relaynnp-1) ;
      }
      
     

}
void TurnOnRelay(int relayno )
{
   WiFiClient myclient ;
  if (myclient.connect(gatewayip, gatewayport))
      {
          Serial.println("RS485 Gateway Access and Connected successful") ;
          myclient.write(&TurnOn[relayno][0],sizeof(TurnOn[relayno])) ;
         // myclient.write(0x0a) ; 
          myclient.stop() ; 

      }
      else
      {
          Serial.print("Connect to :") ;
          Serial.print(gatewayip) ;
          Serial.print("/ Port:") ;
          Serial.print(gatewayport) ;  
          Serial.print(" Fail \n") ;                  
      }
      /*
    for(int i = 0 ; i <8; i++)
        {
          myclient.write(cmd[(relayno-1)*2][i]) ;
        }
        Serial.print("\nRelay :(") ;
        Serial.print(relayno) ;
        Serial.print(") \n\n") ;
        if (myclient.available() >0)
          {
            while (myclient.available() >0)
                {
                  Serial.print(myclient.read() , HEX) ;
                } 
                
          }
    */
}


void TurnOffRelay(int relayno)
{
     WiFiClient myclient ;
  if (myclient.connect(gatewayip, gatewayport))
      {
          Serial.println("RS485 Gateway Access and Connected successful") ;
          myclient.write(&TurnOff[relayno][0],sizeof(TurnOff[relayno])) ;
        //  myclient.write(0x0a) ; 
          myclient.stop() ; 

      }
      else
      {
          Serial.print("Connect to :") ;
          Serial.print(gatewayip) ;
          Serial.print("/ Port:") ;
          Serial.print(gatewayport) ;  
          Serial.print(" Fail \n") ;                  
      }
      /*
    for(int i = 0 ; i <8; i++)
        {
          myclient.write(cmd[(relayno-1)*2+1][i]) ;
        }
        Serial.print("Relay :(") ;
        Serial.print(relayno) ;
        Serial.print(") \n") ;
        if (myclient.available() >0)
          {
            while (myclient.available() >0)
                {
                  Serial.print(myclient.read() , HEX) ;
                } 
                
          }
    */
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
  // print where to go in a browser:
  Serial.print("To see this page in action, open a browser to http://");
  Serial.println(ip);
}

//---------Speed----------
