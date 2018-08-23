//Проект веб сервера IOT
//Код для ESP8266
//Автор - Kot0111
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

MDNSResponder mdns;
String instring;

//Настройки Wi-Fi
const char* ssid = "SSID";
const char* password = "Password";

byte arduino_mac[] = { 0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0xED };
IPAddress ip(192,168,1,35);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

ESP8266WebServer server(80);

  int rel_act = 0;
  int SERVO_ACT = 0;

void setup(void){


  delay(100);
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  WiFi.config(ip, gateway, subnet);


  // Ожидание подключения
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  
  if (mdns.begin("esp8266", WiFi.localIP())) {
  }
  

  server.on("/", [](){
    server.send(200, "text/html", webPage());
  });

//Описание элементов управления
//+++++++++++++++++++++++ START  Relay-1 ++++++++++++++++++++

  server.on("/socket1On", [](){
    rel_act = 1;
    Serial.println("turn1On");
    server.send(200, "text/html", webPage());
    delay(100);
    
  });
  server.on("/socket1Off", [](){
    rel_act = 0;
 Serial.println("turn1Off");
    server.send(200, "text/html", webPage());
    delay(100);
      });
   //+++++++++++++++++++++++ END  Relay-1 ++++++++++++++++++++ 

     //+++++++++++++++++++++++ START  temp-1 ++++++++++++++++++++

server.on("/temp", [](){
    server.send(200, "text/html", webPage());
    delay(100);
}    
  );
     //+++++++++++++++++++++++ END  temp-1 ++++++++++++++++++++ 

      //+++++++++++++++++++++++ START  Servo-1 ++++++++++++++++++++
  server.on("/", [](){
    server.send(200, "text/html", webPage());
  });
  server.on("/servo1On", [](){
    SERVO_ACT = 1;
    Serial.println("Servo180");
    server.send(200, "text/html", webPage());
    delay(100);
    
  });
  server.on("/servo1Off", [](){
    SERVO_ACT = 0;
 Serial.println("Servo0");
    server.send(200, "text/html", webPage());
    delay(100);
      });
   //+++++++++++++++++++++++ END  Servo-1 ++++++++++++++++++++ 
    
    

  server.begin();
}
 
void loop(void){
  server.handleClient();
} 
//Описание веб страницы
String webPage()
{
  String web; 
  web += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"/> <meta charset=\"utf-8\"><title>ESP 8266</title><style>button{color:red;padding: 10px 27px;}</style></head>";
  web += "<h1 style=\"text-align: center;font-family: Open sans;font-weight: 100;font-size: 20px;\">ESP8266 Web Server</h1><div>";
  
  //++++++++++ Relay-1  +++++++++++++
  web += "<p style=\"text-align: center;margin-top: 0px;margin-bottom: 5px;\">----Relay----</p>";
  if (rel_act == 1)
  {
    web += "<div style=\"text-align: center;width: 98px;color:white ;padding: 10px 30px;background-color: #43a209;margin: 0 auto;\">ON</div>";
  }
  else 
  {
    web += "<div style=\"text-align: center;width: 98px;color:white ;padding: 10px 30px;background-color: #ec1212;margin: 0 auto;\">OFF</div>";
  }
  web += "<div style=\"text-align: center;margin: 5px 0px;\"> <a href=\"socket1On\"><button>ON</button></a>&nbsp;<a href=\"socket1Off\"><button>OFF</button></a></div>";
  // ++++++++ Relay-1 +++++++++++++
  
  // ========Temp-1=============
   Serial.println("tempUpd");
    while (Serial.available() ==0){}
    if (Serial.available() > 0){
     instring = Serial.readStringUntil('\n');
     }
  web += "<div style=\"text-align:center;margin-top: 20px;\"><a href=\"temp\"><button style=\"width:158px;\">Temp: " +instring+ "</button></a></div>";
  // ========Temp-1=============

  //++++++++++ Servo-1  +++++++++++++
  web += "<p style=\"text-align: center;margin-top: 0px;margin-bottom: 5px;\">----Lock----</p>";
  if (SERVO_ACT == 1)
  {
    web += "<div style=\"text-align: center;width: 98px;color:white ;padding: 10px 30px;background-color: #43a209;margin: 0 auto;\">Open</div>";
  }
  else 
  {
    web += "<div style=\"text-align: center;width: 98px;color:white ;padding: 10px 30px;background-color: #ec1212;margin: 0 auto;\">Close</div>";
  }
  web += "<div style=\"text-align: center;margin: 5px 0px;\"> <a href=\"servo1On\"><button>Open</button></a>&nbsp;<a href=\"servo1Off\"><button>Close</button></a></div>";
  // ++++++++ Servo-1 +++++++++++++
 
  
  // ========REFRESH=============
  web += "<div style=\"text-align:center;margin-top: 20px;\"><a href=\"/\"><button style=\"width:158px;\">REFRESH</button></a></div>";
  // ========REFRESH=============
  
  
  web += "</div>";
  return(web);
}
