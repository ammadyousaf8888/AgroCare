
#include <ESP8266WiFi.h>      
#include <FirebaseArduino.h>    
#include<SoftwareSerial.h>// firebase librar                                                            // dht11 temperature and humidity sensor library
#define FIREBASE_HOST "testing-dff61-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "jpr0k0ZotvIUYWHaCy0PanX7v4JSsbIrIL5p1u9E"
#define WIFI_SSID "T" //provide ssid (wifi name)
#define WIFI_PASSWORD "mmea2327" //wifi password
String p,h,t,sm,l;
void setup() {
// Open serial communications and wait for port to open:
Serial.begin(9600);
while (!Serial) {
; // wait for serial port to connect. Needed for native USB port only
}
 WiFi.begin(WIFI_SSID, WIFI_PASSWORD);    
  Serial.print("connecting");
   while (WiFi.status() != WL_CONNECTED) {
  Serial.print(".");
  delay(500);
  } 

  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST);
}
void loop() { // run over and over
  String p="";
if (Serial.available()) {
   p=Serial.readStringUntil('\n');

   Serial.println(p);

   int ind1 = p.indexOf(',');  //finds location of first ,
      h = p.substring(0, ind1);   //captures first data String
    int  ind2 = p.indexOf(',', ind1+1 );   //finds location of second ,
      t = p.substring(ind1+1, ind2);   //captures second data String
     int ind3 = p.indexOf(',', ind2+1 );
      sm = p.substring(ind2+1, ind3);
      l = p.substring(ind3+1);
    Serial.println(h);
        Serial.println(t);
        Serial.println(sm);   
        Serial.println(l);
   Firebase.setString("Temperature",t);
   Firebase.setString("Humidity",h);
   Firebase.setString("Soil Moisture",sm);
   Firebase.setString("Luminosity",l);
   if (Firebase.failed()) {
      Serial.print("setting /number failed:");
      Serial.println(Firebase.error());  
      return;
  }
   Serial.println("pushed: /logs/");
   delay(50000);
}
}
