# Gravando programas no ESP8266

## Preparando o ambiente

#### Instalar arduino IDE 1.6.8 do site do arduino:

[https://www.arduino.cc/en/Main/Software](https://www.arduino.cc/en/Main/Software)

#### Adicione uma nova origem no gerenciados de placas da IDE do arduino.

1. Menu: Arquivo > Preferências > Configurações
 * No campo URLs adicionais de gerenciadores de placas adicione:
    * http://arduino.esp8266.com/stable/package_esp8266com_index.json
    * Múltiplas URLs podem ser adicionadas separando-as por vígulas.

2. Menu: Ferramentas > Placa > Gerenciador de Placas
 * No campo de busca coloque esp8266 e instale o gerenciador referente à placa.
 
#### Instalar Dependencias  

1. ESP8266WiFi  
 ```
   cd ~/arduino  
   cd hardware  
   mkdir esp8266com  
   cd esp8266com  
   git clone https://github.com/esp8266/Arduino.git esp8266  
   cd esp8266/tools  
   python get.py  
 ```
 * Reiniciar a IDE do Arduino  
   
2. pubsub 
  * Sketch -> Incluir Bibliotecas -> Gerenciar Bibliotecas... -> Digitar PubSub no campo de busca -> Install (PubSubClient by Nick O'Leary)
    
3. RemoteDebug
  * Sketch -> Incluir Bibliotecas -> Gerenciar Bibliotecas... -> Digitar remotedebug no campo de busca -> instalar (Joao Lopes / RemoteDebug)

#### Habilitar porta serial no Linux

  1. Abra o terminal e inclua o usuário nos grupos "tty" e "dialout", com os comandos:
```
  $ sudo usermod -a -G tty teu_usuario
  $ sudo usermod -a -G dialout teu_usuario
```
  2. Agora faça logout e em seguida, login novamente.

  3. Para verificar se os grupos foram incluídos, use o comando:
```
  $ groups
```


#### PL230HX

![PL2303HX - USB Conector](https://github.com/jrperin/homeControl_esp8266/blob/master/PL2303HX_USB_Dongle.jpg)

[Download Windows Driver](http://www.prolific.com.tw/US/ShowProduct.aspx?p_id=225&pcid=41)

__Problemas em reconhecer o módulo no desktop novo:__  
  
Na Bios alterar:  
> - USB legacy mode off  
> - XHCI hands-off - enable  

Alterar o arquivo:  
> * /etc/default/grub  
> Adicionar alinha:  
> GRUB_CMDLINE_LINUX="iommu=soft"  
  
Salvar e recriar o grup com:  
> * sudo update-grub.  
  
  
  
## CH340G - Protótipo
http://fobit.blogspot.com/2014/11/ch340g-in-eagle.html


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
  > * http://www.switchdoc.com/2016/02/tutorial-installing-and-testing-mosquitto-mqtt-on-raspberry-pi/
