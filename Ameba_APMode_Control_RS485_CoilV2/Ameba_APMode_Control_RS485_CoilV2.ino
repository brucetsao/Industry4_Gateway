#include <SoftwareSerial.h>
#include <String.h>

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

#include <WiFi.h>

char ssid[] = "Ameba";  //Set the AP's SSID
char pass[] = "12345678";     //Set the AP's password
char channel[] = "11";         //Set the AP's channel
int status = WL_IDLE_STATUS;     // the Wifi radio's status

int keyIndex = 0;                 // your network key Index number (needed only for WEP)
IPAddress  Meip ,Megateway ,Mesubnet ;
String MacAddress ;
uint8_t MacData[6];

WiFiServer server(80);


void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);

  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    while (true);
  }
  String fv = WiFi.firmwareVersion();
  if (fv != "1.1.0") {
    Serial.println("Please upgrade the firmware");
  }

  // attempt to start AP:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to start AP with SSID: ");
    Serial.println(ssid);
    status = WiFi.apbegin(ssid, pass, channel);
    delay(10000);
  }

  //AP MODE already started:
  Serial.println("AP mode already started");
  Serial.println();
    server.begin();    
  printWifiData();
  printCurrentNet();
}

void loop() {
 WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    Serial.println("new client");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");

            client.println("Content-type:text/html");
            client.println();

           client.print("<title>Ameba AP Mode Control Relay</title>");
            client.println();
                          client.print("<html>");
                          client.println();
                          client.print("<body>");
                          client.println();
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
                          client.print("<a href='/A' target='_self'>Open</a>") ;
                          client.print("/") ; 
                          client.print("<a href='/B' target='_self'>Close</a>") ;
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
                          client.print("<a href='/C' target='_self'>Open</a>") ;
                          client.print("/") ; 
                          client.print("<a href='/D' target='_self'>Close</a>") ;
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
                          client.print("<a href='/E' target='_self'>Open</a>") ;
                          client.print("/") ; 
                          client.print("<a href='/F' target='_self'>Close</a>") ;
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
                          client.print("<a href='/G' target='_self'>Open</a>") ;
                          client.print("/") ; 
                          client.print("<a href='/H' target='_self'>Close</a>") ;
                          client.print("</p>");
//----------control code end                               
                          client.print("</body>");
                          client.println();
                          client.print("</html>");
                          client.println();

            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

        // Check to see if the client request was "GET /HN or "GET /LN":
        if (currentLine.endsWith("/A")) 
        {
              RelayMode[1] = true ;  
              RelayControl(1,RelayMode[1]);               
        }
        if (currentLine.endsWith("/B")) 
        {
              RelayMode[1] = false ;  
              RelayControl(1,RelayMode[1]);               
        }
        //-----------------
        if (currentLine.endsWith("/C")) 
        {
              RelayMode[2] = true ;  
              RelayControl(2,RelayMode[2]);               
        }
        if (currentLine.endsWith("/D")) 
        {
              RelayMode[2] = false ;  
              RelayControl(2,RelayMode[2]);               
        }
        //-----------------
        if (currentLine.endsWith("/E")) 
        {
              RelayMode[3] = true ;  
              RelayControl(3,RelayMode[3]);               
        }
        if (currentLine.endsWith("/F")) 
        {
              RelayMode[3] = false ;  
              RelayControl(3,RelayMode[3]);               
        }
        //-----------------
        if (currentLine.endsWith("/G")) 
        {
              RelayMode[4] = true ;  
              RelayControl(4,RelayMode[4]);               
        }
        if (currentLine.endsWith("/H")) 
        {
              RelayMode[4] = false ;  
              RelayControl(4,RelayMode[4]);               
        }
        //-----------------
      }
    }
    // close the connection:
    client.stop();
    Serial.println("client disonnected");
  }
}


void RelayControl(int relaynnp, boolean  RM)
{
      if (RM)
      {
          TurnOnRelay(relaynnp) ;
      }
      else
      {
          TurnOffRelay(relaynnp) ;
      }
      
     

}
void TurnOnRelay(int relayno)
{
    for(int i = 0 ; i <8; i++)
        {
          mySerial.write(cmd[(relayno-1)][i]) ;
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


void ShowMac()
{
  
     Serial.print("MAC:");
     Serial.print(MacAddress);
     Serial.print("\n");

}




String GetWifiMac()
{
   String tt ;
    String t1,t2,t3,t4,t5,t6 ;
    WiFi.status();    //this method must be used for get MAC
  WiFi.macAddress(MacData);
  
  Serial.print("Mac:");
   Serial.print(MacData[0],HEX) ;
   Serial.print("/");
   Serial.print(MacData[1],HEX) ;
   Serial.print("/");
   Serial.print(MacData[2],HEX) ;
   Serial.print("/");
   Serial.print(MacData[3],HEX) ;
   Serial.print("/");
   Serial.print(MacData[4],HEX) ;
   Serial.print("/");
   Serial.print(MacData[5],HEX) ;
   Serial.print("~");
   
   t1 = print2HEX((int)MacData[0]);
   t2 = print2HEX((int)MacData[1]);
   t3 = print2HEX((int)MacData[2]);
   t4 = print2HEX((int)MacData[3]);
   t5 = print2HEX((int)MacData[4]);
   t6 = print2HEX((int)MacData[5]);
 tt = (t1+t2+t3+t4+t5+t6) ;
Serial.print(tt);
Serial.print("\n");
  
  return tt ;
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




void ShowInternetStatus()
{
    
        if (WiFi.status())
          {
               Meip = WiFi.localIP();
               Serial.print("Get IP is:");
               Serial.print(Meip);
               Serial.print("\n");
              
          }
          else
          {
                       Serial.print("DisConnected:");
                       Serial.print("\n");
          }

}

void initializeWiFi() {
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);
  //   status = WiFi.begin(ssid);

    // wait 10 seconds for connection:
    delay(10000);
  }
  Serial.print("\n Success to connect AP:") ;
  Serial.print(ssid) ;
  Serial.print("\n") ;
  
}

void printWifiData() {
  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print your subnet mask:
  IPAddress subnet = WiFi.subnetMask();
  Serial.print("NetMask: ");
  Serial.println(subnet);

  // print your gateway address:
  IPAddress gateway = WiFi.gatewayIP();
  Serial.print("Gateway: ");
  Serial.println(gateway);
  Serial.println();
}

void printCurrentNet() {
  // print the SSID of the AP:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print the MAC address of AP:
  byte bssid[6];
  WiFi.BSSID(bssid);
  Serial.print("BSSID: ");
  Serial.print(bssid[0], HEX);
  Serial.print(":");
  Serial.print(bssid[1], HEX);
  Serial.print(":");
  Serial.print(bssid[2], HEX);
  Serial.print(":");
  Serial.print(bssid[3], HEX);
  Serial.print(":");
  Serial.print(bssid[4], HEX);
  Serial.print(":");
  Serial.println(bssid[5], HEX);

  // print the encryption type:
  byte encryption = WiFi.encryptionType();
  Serial.print("Encryption Type:");
  Serial.println(encryption, HEX);
  Serial.println();
}



