
#include <ESP32Servo.h>
#include <WiFi.h>

#define BLYNK_TEMPLATE_ID "TMPL67ZzW31P1"
#define BLYNK_TEMPLATE_NAME "Smart Parking"
#define BLYNK_AUTH_TOKEN "cWUq7lfc6NuLCK6yUCxlAhN1ojo1RcIZ"

#include <BlynkSimpleEsp32.h>

#define WIFI_SSID "Wifi_Username"
#define WIFI_PASSWORD "Wifi_Password"

char ssid[] = WIFI_SSID;
char pass[] = WIFI_PASSWORD;
char auth[] = BLYNK_AUTH_TOKEN;
 #define SERVO_1_PIN 12
#define SERVO_2_PIN 15
Servo s1;
Servo s2;

void setup() 
{
  Serial.begin(115200);
 WiFi.begin( ssid, pass );
  while( WiFi.status() != WL_CONNECTED ) 
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println( "" );
  Serial.println( "WiFi connected.");
  Serial.println( "IP address: "   );
  Serial.println( WiFi.localIP());
  Blynk.begin(auth, ssid, pass);
  pinMode(4,INPUT); //gate
  pinMode(5,INPUT); //slot
  s1.attach(SERVO_1_PIN);
  pinMode(33,INPUT); //gate
  pinMode(19,INPUT); ///slot
  s1.attach(SERVO_1_PIN);
  s2.attach(SERVO_2_PIN);
  s1.write(90);
  s2.write(90);
}

void loop() 
{
  int count=0;
  Serial.print("sensor1:");
int val1=digitalRead(4); //gate
  Serial.println(val1);
    Serial.print("sensor2:");
  int val2=digitalRead(5); //slot
  Serial.println(val2);
  Serial.print("sensor11:");
int val3=digitalRead(33);
  Serial.println(val3);
    Serial.print("sensor12:");
  int val4=digitalRead(19);
  Serial.println(val4);
  if(val2==1)
  {
  if(digitalRead(4)==0)
  s1.write(0);
  delay(1000);
  s1.write(90);
  Blynk.virtualWrite(V2, "AVAILABLE");
  }
  else if(val2==0)
  {
  Blynk.virtualWrite(V2, "OCCUPIED");
  count++;
  s1.write(90);
  }

  Blynk.virtualWrite(V0, val2);

  if(val4==1)
  {
  if(digitalRead(33)==0)
  s2.write(0);
  delay(1000);
  s2.write(90);
  Blynk.virtualWrite(V3, "AVAILABLE");
  }
  else if(val4==0)
  {
  s2.write(90);
  Blynk.virtualWrite(V3, "OCCUPIED");
  count++;
  }


  Blynk.virtualWrite(V1, val4);

  Blynk.virtualWrite(V4,2-count);
}
