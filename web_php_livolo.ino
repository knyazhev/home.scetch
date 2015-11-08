#include <livolo.h>
#include <SPI.h>
#include <Ethernet.h>
//#1: 0, #2: 96, #3: 120, #4: 24, #5: 80, #6: 48, #7: 108, #8: 12, #9: 72; #10: 40, #OFF: 106


Livolo livolo(8);
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192,168,0,177);
EthernetServer server(80);


unsigned long time;
unsigned long updateTime;
unsigned long passTime;

boolean isLedOn = false;
void switchON (q){
livolo.sendButton(8500, q);
}

void setup() {
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
}

void loop(){
 // delay(100);
//time=millis();
//passTime=time-updateTime;
//updateTime=time;
//Serial.println(time);
//Serial.println(passTime);

  EthernetClient client = server.available();

  if(client){

    String request;

    boolean currentLineIsBlank = true;
    boolean requestLineReceived = false;

    while(client.connected()){
      if (client.available()) {
        char c = client.read();

        if(c == '\n' && currentLineIsBlank) { 
          // substract path from a request line
          request = request.substring( 
                      request.indexOf(' ') + 2, 
                      request.lastIndexOf(' '));
          if(request=="/"){
            break;
          }else if(request=="1"){
            Serial.println(request);
            livolo.sendButton (8500, 0);
          }else if(request=="2"){
            Serial.println(request);
            livolo.sendButton (8500,96);
          }else if(request=="3"){
            Serial.println(request);
            livolo.sendButton (8500,120);
          }else if(request=="4"){
            Serial.println(request);
            livolo.sendButton (8500,24);
          }else if(request=="5"){
            Serial.println(request);
            livolo.sendButton (8500,80);
            }else if(request=="6"){
            Serial.println(request);
            livolo.sendButton (8500,80);
          }else if(request=="7"){
            Serial.println(request);
            livolo.sendButton (8500,106);
            delay(10);
            livolo.sendButton (8500,106);
            delay(10);
            livolo.sendButton (8500,106);
          }else if(request=="8"){
            Serial.println(request);
            livolo.sendButton (8500,0);
            delay(5);
            livolo.sendButton (8500, 96);
            delay(5);
            livolo.sendButton (8500, 120);
            delay(5);
            livolo.sendButton (8500, 24);
            delay(5);
            livolo.sendButton (8500, 80);
          }else if(request=="9"){
            Serial.println(request);
            livolo.sendButton (8500,106);
            delay(10);
            livolo.sendButton (8500,106);
            delay(10);
            livolo.sendButton (8500,0);
            livolo.sendButton (8500, 96);
            livolo.sendButton (8500, 80);
          }break; 
        }
        if (c == '\n') {
          currentLineIsBlank = true;
          if(!requestLineReceived){
            requestLineReceived = true;
          }
        } 
        else if (c != '\r') {
          if(!requestLineReceived) {
            request += c;
          }
          currentLineIsBlank = false;
        }
      }
    }
   // delay(1000);
    client.stop();
  }  
}






