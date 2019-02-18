  
////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Header Library
#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Define SSID, PASSWORD & PORT
const char *ssid = "hello"; const char *password = "hello1234";
ESP8266WebServer server(80);

////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Get responce from Page and Code for Forward/Reverse/Left/Right Motion
void handleRoot() {response();}

  void up() {digitalWrite(15,LOW);
              digitalWrite(12,LOW);
              digitalWrite(13,HIGH);
              digitalWrite(14,HIGH);
              response();}//UP
                
  void down() {digitalWrite(15,HIGH);
              digitalWrite(12,HIGH);
              digitalWrite(13,LOW);
              digitalWrite(14,LOW);
              response();}//Down
              
  void right() {digitalWrite(14,HIGH); 
              digitalWrite(12,LOW);
              digitalWrite(15,HIGH);
              digitalWrite(13,LOW);
              response();}//Right
              
  void left() {digitalWrite(14,LOW); 
              digitalWrite(12,HIGH);
              digitalWrite(15,LOW);
              digitalWrite(13,HIGH);
              response();}//LEFT
 
  void OFF(){
  digitalWrite(13,LOW); 
  digitalWrite(15,LOW); 
  digitalWrite(14,LOW); 
  digitalWrite(12,LOW); 
  response();}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Code to generate HTML Page
     const String HtmlHtml = "<html><head>"
     "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\" /> <style>h2 {  color:  #FF0000 ; }</style></head><body bgcolor=\"black\">";
     const String HtmlHtmlClose = "</body></html>";
     const String HtmlButtons = 
        "<center><button onmouseover=\"window.location.assign('http://192.168.4.1/up')\" onmouseover=\"window.location.assign('http://192.168.4.1/')\" style=\"margin:20% 3% 3% 3%; display: block; height:10%; width: 30%;\"><h2>Up</h2></button></center></a><br>"
        "<div><button onmouseover=\"window.location.assign('http://192.168.4.1/left')\" onmouseover=\"window.location.assign('http://192.168.4.1/')\" style=\"align-content: center; height:10%; width: 30%;\"><h2>Left</h2></button>"
        "<button onmouseover=\"window.location.assign('http://192.168.4.1/OFF')\" onmouseover=\"window.location.assign('http://192.168.4.1/')\" style=\"margin-left:3%; align-content: center; height:10%; width: 30%;\"><h2>Break</h2></button></a>"
        "<button onmouseover=\"window.location.assign('http://192.168.4.1/right')\" onmouseover=\"window.location.assign('http://192.168.4.1/')\" style=\"margin-left:3%; align-content: center; height:10%; width: 30%;\"><h2>Right</h2></button></a></div>"
        "<center><button onmouseover=\"window.location.assign('http://192.168.4.1/down')\" onmouseover=\"window.location.assign('http://192.168.4.1/')\" style=\"margin-top:9%; display: block; align-content: center; height:10%; width: 30%;\"><h2>Down</h2></center></button></a>";
////////////////////////////////////////////////////////////////////////////////////////////////////////////
//HTML Responce from URL
void response(){
  String htmlRes = HtmlHtml ;
  htmlRes += HtmlButtons;
  htmlRes += HtmlHtmlClose;
  server.send(200, "text/html", htmlRes);
  delay(100);
}   
////////////////////////////////////////////////////////////////////////////////////////////////////////////
void setup() {
    delay(1000);
////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Define Pins as Output Pins
    pinMode(13, OUTPUT);
    pinMode(15, OUTPUT);
    pinMode(14, OUTPUT);
    pinMode(12, OUTPUT);
//////////////////////////////////////////////////////////////////////////////////////////////////////////// 
    digitalWrite(13,LOW); 
    digitalWrite(15,LOW); 
    digitalWrite(14,LOW); 
    digitalWrite(12,LOW); 
    Serial.begin(9600);
////////////////////////////////////////////////////////////////////////////////////////////////////////////
//To create WiFi Access Point
    WiFi.softAP(ssid, password);
    IPAddress apip = WiFi.softAPIP();
    Serial.print("visit: \n");
    Serial.println(apip);
////////////////////////////////////////////////////////////////////////////////////////////////////////////  
//Action triggered by Page
    server.on("/", handleRoot);
    server.on("/OFF", OFF);
    server.on("/up", up);
    server.on("/down", down);
    server.on("/right", right);
    server.on("/left", left);
    server.begin();
    Serial.println("HTTP server beginned");
////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
void loop() {
  server.handleClient();
  }
