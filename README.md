# Gravando programas no ESP8266

## Preparando o ambiente

##### Instalar arduino IDE 1.6.8 do site do arduino:

[https://www.arduino.cc/en/Main/Software] (https://www.arduino.cc/en/Main/Software)

##### Adicione uma nova origem no gerenciados de placas da IDE do arduino.

1. Menu: Arquivo > Preferências > Configurações
 1. No campo URLs adicionais de gerenciadores de placas adicione:
    * http://arduino.esp8266.com/stable/package_esp8266com_index.json
    * Múltiplas URLs podem ser adicionadas separando-as por vígulas.

2. Menu: Ferramentas > Placa > Gerenciador de Placas
 1. No campo de busca coloque esp8266 e instale o gerenciador referente à placa.



## Preparando o Hardware



Gravar o programa no ESP8266

O programa de exemplo do próprio arduino ocasionava o erro abaixo:

 ets Jan  8 2013,rst cause:4, boot mode:(3,3)

wdt reset
load 0x4010f000, len 1384, room 16 
tail 8
chksum 0x2d
csum 0x2d
v09f0c112
~ld

Usando outros programas funcionou normalmente.



## Extras

1. Site do fabricante:

 > http://bbs.espressif.com/index.php



2. Imagem SDK para atualização (_versão atual no momento_):
 
 > http://bbs.espressif.com/download/file.php?id=1469



3. Guia Linux de como atualizar o firmware do ESP8266 pelo NodeMCU:
 
 > Link do guia: http://www.whatimade.today/flashing-the-nodemcu-firmware-on-the-esp8266-linux-guide/

 > Baixar o esptool: https://github.com/themadinventor/esptool
 
 > **Command de atualização do firmware no esp8266:**
 
 > ./esptool.py -p /dev/ttyUSB0 write_flash 0x000000 v0.9.5.2\ AT\ Firmware.bin


4. Links interessantes:
  
  > http://www.whatimade.today/esp8266-easiest-way-to-program-so-far/

  > http://blog.thethings.io/connect-esp8266-to-the-internet-at-thethings-io/
  
  > iot eclipse mosquito (mqtt broker)
  > * http://mosquitto.org/download/
