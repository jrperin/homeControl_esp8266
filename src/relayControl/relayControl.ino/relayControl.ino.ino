#include "ESP8266WiFi.h"
#include <ESP8266mDNS.h>
//#include <WiFiClient.h>
#include <EEPROM.h>
#include <cstring>

MDNSResponder mdns;
WiFiServer server(80);

char* ssid = "relayControl";
String st;
byte relayStatus = 0;
byte ambiente = 1;

uint8_t MAC_array[6];
//char MAC_char[18];
//char MAC_char_ssid[12];
String mac_addr = "";
String mac_addr_clear = "";

 

/* GPIO0 = 0 ; GPIOTXD = 1 ; GPIO2 = 2 ; GPIORXD = 3 */
#define relayTest 2  //Test
#define relayProd 3  //Production


void setup() {
  Serial.begin(115200);
  EEPROM.begin(512);
  delay(10);
  Serial.println();
  Serial.println();
  Serial.println("Startup");

  pinMode(relayTest, OUTPUT);
  digitalWrite(relayTest, LOW);
  pinMode(relayProd, OUTPUT);
  digitalWrite(relayProd, LOW);

  WiFi.macAddress(MAC_array);

    Serial.println("MAC_array");
    for (int i = 0; i < sizeof(MAC_array); i++){
      Serial.print(MAC_array[i]);
      Serial.print(" => ");
      Serial.println(String(MAC_array[i], HEX));
    }
    Serial.println("MAC_array - fim");
    
    for (int i = 0; i < sizeof(MAC_array); i++){
      String strAux = "0" + String(MAC_array[i], HEX);
      strAux = strAux.substring(strAux.length() -2, strAux.length());
      mac_addr +=  strAux;
      mac_addr_clear += strAux;
      if (i < sizeof(MAC_array)-1){
           mac_addr += ":";
      }
    }

    String ssidFullName = "relayControl_" + mac_addr_clear;
    strcpy(ssid, ssidFullName.c_str());

    Serial.print("mac_addr: [");
    Serial.print(mac_addr);
    Serial.println("]");

    Serial.print("mac_addr_clear: [");
    Serial.print(mac_addr_clear);
    Serial.println("]");

    Serial.print("ssid: [");
    Serial.print(ssid);
    Serial.println("]");
    
  
  setupAP(); 
}

/*
 * Converting from Hex to Decimal:
 * NOTE: This function can handle a positive hex value from 0 - 65,535 (a four digit hex string).
 *       For larger/longer values, change "unsigned int" to "long" in both places.
 */
unsigned int hexToDec(String hexString) {
  
  unsigned int decValue = 0;
  int nextInt;
  
  for (int i = 0; i < hexString.length(); i++) {
    
    nextInt = int(hexString.charAt(i));
    if (nextInt >= 48 && nextInt <= 57) nextInt = map(nextInt, 48, 57, 0, 9);
    if (nextInt >= 65 && nextInt <= 70) nextInt = map(nextInt, 65, 70, 10, 15);
    if (nextInt >= 97 && nextInt <= 102) nextInt = map(nextInt, 97, 102, 10, 15);
    nextInt = constrain(nextInt, 0, 15);
    
    decValue = (decValue * 16) + nextInt;
  }
  
  return decValue;
}



void launchWeb(int webtype) {
          Serial.println("");
          Serial.println("WiFi connected");
          Serial.println(WiFi.localIP());
          Serial.println(WiFi.softAPIP());
          
          // Start the server
          server.begin();
          Serial.println("Server started");   
          int b = 20;
          int c = 0;
          while(b == 20) { 
             b = mdns1(webtype);
           }
}




void setupAP(void) {
  
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  WiFi.softAP(ssid);
  Serial.println("softap");
  Serial.println("");
  launchWeb(1);
  Serial.println("over");
  
}


String getHtml(void){
  
  String s;
  String btStatus;
  String btSubmit;
  String btAmbiente;
  
  IPAddress ip = WiFi.softAPIP();
  String ipStr = String(ip[0]) + '.' + String(ip[1]) + '.' + String(ip[2]) + '.' + String(ip[3]);
  
  if (relayStatus == 0){
    btStatus    = "<input type='submit' style='color: gray; font-weight: 900; width: 160px; height: 80px; font-size: 2em' value='OFF'>";
    btSubmit    = "<input name='status' length=1 value='1' style='display: none'>";
  } else {
    btStatus    = "<input type='submit' style='color: limegreen; font-weight: 900; width: 160px; height: 80px; font-size: 2em' value='ON'>";
    btSubmit    = "<input name='status' length=1 value='0' style='display: none'>";
  }

  if (ambiente){
    btAmbiente  = "<input type='radio' name='ambiente' value='0'> teste <br>";
    btAmbiente += "<input type='radio' name='ambiente' value='1' checked='checked'> produção <br>";
  } else {
    btAmbiente  = "<input type='radio' name='ambiente' value='0' checked='checked'> teste <br>";
    btAmbiente += "<input type='radio' name='ambiente' value='1' > produção <br>";
  }

  s  = "HTTP/1.1 200 OK\r\nContent-Type: text/html \r\n\r\n";
  s += "<!DOCTYPE HTML> \r\n";
  s += "<html>";
  s += "<head>";
  s += "<meta charset='UTF-8'>";
  s += "<meta name='viewport' content='initial-scale=1, maximum-scale=1, user-scalable=no, width=device-width'>";
  s += "<style>"; 
  s += "body {font-family: Arial, Helvetica, sans-serif; font-size:large; text-align: center}";
  s += "</style>";
  s += "</head>";
  s += "<body>";
  s += "<h1> relayControl_ </h1>";
  s += "<h3>" + ipStr + "</h3>";
  s += "<h4>" + mac_addr + "</h4>";
  s += "<br>";
  s += "<form method='get' action='a'>";
  s += "<div style='width: 180px; margin:auto; text-align: left'>";
  s += btAmbiente;
  s += "</div>";
  s += "<br>";
  s += btStatus;
  s += btSubmit;
  s += "</form>";
  s += "</body>";
  s += "</html> \r\n\r\n";

  return s;

}


int mdns1(int webtype)
{
  // Check for any mDNS queries and send responses
  
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return(20);
  }
  
  Serial.println("");
  Serial.println("New client");

  // Wait for data from client to become available
  while(client.connected() && !client.available()){
    delay(1);
   }
  
  // Read the first line of HTTP request
  String req = client.readStringUntil('\r');
  

  // First line of HTTP request looks like "GET /path HTTP/1.1"
  // Retrieve the "/path" part by finding the spaces
  int addr_start = req.indexOf(' ');
  int addr_end = req.indexOf(' ', addr_start + 1);
  if (addr_start == -1 || addr_end == -1) {
    Serial.print("Invalid request: ");
    Serial.println(req);
    return(20);
   }
   
  req = req.substring(addr_start + 1, addr_end);
  Serial.print("Request: [");
  Serial.print(req);
  Serial.println("]");
  client.flush(); 
  
  String s ;
  
  
  if (req == "/") {
    Serial.println("entrou em '/'");    
    Serial.println("Sending 200");
    s = getHtml();
    
  } else if ( req.startsWith("/a?ambiente=") ) {
    Serial.println("entrou em /a?status=");
    // /a?ambiente=0&status=1

    ambiente    = req.substring(12,req.indexOf('&')).toInt();
    relayStatus = req.substring(req.lastIndexOf('=')+1).toInt();

    int relay = relayProd;
    if (!ambiente){
      relay = relayTest;
    }
    
    if (relayStatus){
      digitalWrite(relay, HIGH);
    } else {
      digitalWrite(relay, LOW);
    }
    
    Serial.print("relayStatus = ");
    Serial.println(relayStatus);
    Serial.println();
    s = getHtml();

  } else {
    Serial.println("Entrou no ELSE");
    s = "HTTP/1.1 404 Not Found\r\n\r\n";
    Serial.println("Sending 404");
  }

  Serial.println(s);
  Serial.println();
  client.print(s);
  
  Serial.println("Done with client");
  return(20);
}



void loop() {
  // put your main code here, to run repeatedly:

}
