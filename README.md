# programLoader_esp8266
Como subir programas para o módulo wifi esp8266

Instalar arduino IDE 1.6.8 do site do arduino.
https://www.arduino.cc/en/Main/Software

Adicione uma nova origem no gerenciados de placas da IDE do arduino.

Menu: Arquivo > Preferências > Configurações
No campo URLs adicionais de gerenciadores de placas adicione:
http://arduino.esp8266.com/stable/package_esp8266com_index.json
Múltiplas URLs podem ser adicionadas separando-as por vígulas.

Menu: Ferramentas > Placa > Gerenciador de Placas
No campo de busca coloque esp8266 e instale o gerenciador referente à placa.

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

Para fazer o update do Firmware do ESP8266 (não necessário):

Update do firmware do ESP-01:
http://www.whatimade.today/flashing-the-nodemcu-firmware-on-the-esp8266-linux-guide/

Download esptool:
https://github.com/themadinventor/esptool

Execute:
./esptool.py -p /dev/ttyUSB0 write_flash 0x000000 v0.9.5.2\ AT\ Firmware.bin


