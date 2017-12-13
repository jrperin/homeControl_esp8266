#include <ESP8266WiFi.h>

uint8_t MAC_array[6];
char MAC_char[18]; // Exemplo: 00:19:B9:FB:E2:57

void setup() {
    Serial.begin(115200);
    Serial.println();

    WiFi.macAddress(MAC_array);
    for (int i = 0; i < sizeof(MAC_array); ++i){
      //Converte os campos de byte em hexa
      sprintf(MAC_char,"%s%02x:",MAC_char,MAC_array[i]);
    }
  
    Serial.println(MAC_char);
}

void loop() {
  
}
 
- See more at: http://www.esp8266.com/viewtopic.php?f=29&t=3587#sthash.3qnFXfs1.dpuf
