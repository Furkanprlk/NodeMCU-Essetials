#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>


IPAddress gateway(192, 168, 1, 254);
IPAddress subnet(255, 255, 255, 0);

WiFiServer server(80);


void wifiStarting(int Mode, const char* ssid, const char* password, const char* APssid, const char* APpassword, IPAddress ip) {
  WiFi.config(ip, gateway, subnet);
  WiFi.softAPConfig(ip, gateway, subnet);

  if (Mode == 0) { //First Connection Mode ( Only AP Mode )


    Serial.println("WiFi Access Point Mode\n");
    Serial.println(WiFi.softAP(APssid, APpassword) ? "Ready!\n" : "Failed!\n");
    Serial.print("Access Point IP address = ");
    Serial.println(WiFi.softAPIP());


  } else if (Mode == 1) { //Standard Mode


    Serial.println("WiFi Station Mode");
    Serial.println("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    int wifiTime = 0;
    while (WiFi.status() != WL_CONNECTED) {
      delay(1000);
      Serial.print(".");
      if (wifiTime++ > 10)
        break;
    }
    if (wifiTime > 10) {
      Serial.println("\nWiFi Connection Failed.\n");
      Serial.println("WiFi Access Point Mode\n");
      Serial.println(WiFi.softAP(APssid, APpassword) ? "Ready!\n" : "Failed!\n");
      Serial.print("Access Point IP address = ");
      Serial.println(WiFi.softAPIP());
    } else {
      Serial.println("");
      Serial.println("WiFi connected.");
      Serial.print("IP: ");  Serial.println(WiFi.localIP());
    }


  }
}
