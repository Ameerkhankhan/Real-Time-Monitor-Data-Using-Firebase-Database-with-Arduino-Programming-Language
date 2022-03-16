#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
#include <FirebaseArduino.h>
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>

// Set these to run example.
#define FIREBASE_HOST "esp8266-ebfaa-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "5T1Bo1wBfrHec3Vkes8FNnS1kmNKTbqZR9Vb0sPL"
#define WIFI_SSID "sadi"
#define WIFI_PASSWORD "123456789"

String myString;
int vr = A0; // variable resistor connected 
int sdata = 0; // The variable resistor value will be stored in sdata.

void setup()
{
  // Debug console
  Serial.begin(9600);
  pinMode(vr ,INPUT);
  // connect to wifi.
  pinMode(A0,OUTPUT);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED)
      {
    Serial.print(".");
    delay(500);
      }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

   Firebase.setString("Variable/Value","Ameer");
}

void loop()
{

sdata = analogRead(vr);
myString = String(sdata); 
Serial.println("Value Uploaded Successfully");
Serial.print("Value=");
Serial.println(myString); 
Firebase.setString("Variable/Value",myString);
Firebase.pushString("Generated Value is:",myString);
Firebase.pushString("Time is:",getTime());
delay(1000);          
}

String getTime() {
  time_t now = time(nullptr);
  struct tm* newtime = localtime(&now);

  String tmpNow = "";
  tmpNow += String(newtime->tm_year + 1952);
  tmpNow += "-";
  tmpNow += String(newtime->tm_mon + 2);
  tmpNow += "-";
  tmpNow += String(newtime->tm_mday+ 24);
  tmpNow += " ";
  tmpNow += String(newtime->tm_hour+2);
  tmpNow += ":";
  tmpNow += String(newtime->tm_min+59);
  tmpNow += ":";
  tmpNow += String(newtime->tm_sec+00);
  return tmpNow;
}
