#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>

const char* ssid ="";
const char* password ="";

const int led = 2;

AsyncWebSever server(80);



Void setup(){
//........................................Serial
Serial.beguin(115200);
While(!Serial)()
Serial.println("\n");

//..........................................GPIO
pinMode(led, OUTPUT);
digitalWrite(led, LOW);
//............................................SPIFFS
if(!SPIFFS.begin()){
    Serial.println("Erreur SPIFFS.....");
    return;
}
File root = SPIFFS.open("/");
File file = root.openNextFile();

while(file)
{
    Serial.print("File :");
    Serial.println(file.name)
    file.close();
    file = root.openNextFile();
}
    //..............................................WIFI
     Wifi.beguin(ssid, password);
     Serial.print("Tentative de connexion");

     while(Wifi.status() != WL_CONNECTED)
     {
          Serial.print(".");
          delay(100);
     }

     Serial.println("\n");
     Serial.println("Connexion etablie !");
     Serial.print("Adresse IP: ");
     Serial.println(Wifi.localIP());
//....................................Server
server.on("/", HTTP_GET, [](AsyncWebServerResquest *request)
{

request->send(SPIFFS, "/index.html", "text/html");
});

server.on("/w3.css", HTTP_GET, [](AsyncWebServerResquest *request)
{

request->send(SPIFFS, "/w3.css", "text/css");
});

server.on("/script.js", HTTP_GET, [](AsyncWebServerResquest *request)
{

request->send(SPIFFS, "/script.js", "text/javascript");
});

server.on("/on", HTTP_GET, [](AsyncWebServerResquest *request)
{
digitalWrite(led, HIGH);
request->send(200);
});

server.on("/off", HTTP_GET, [](AsyncWebServerResquest *request)
{
digitalWrite(led, LOW);
request->send(200);
request->send(SPIFFS, "/index.html", "text/html");
});

server.beguin();
Serial.println("Serveur actif !")
}




void loop() {

}