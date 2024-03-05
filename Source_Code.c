#define BLYNK_TEMPLATE_ID "TMPL3_DBf0lHH"
#define BLYNK_TEMPLATE_NAME "Water level Controller"
#define BLYNK_AUTH_TOKEN "Xx_iRRFJrEPzsm6uobi_nBXX3tzg9VgO"
#include <WiFi.h>
#include<WiFiClient.h>
#include<BlynkSimpleEsp32.h>
#define PIN_TRIG 26
#define PIN_ECHO 25
#define LOWLED 18
#define MIDLED 19
#define HIGHLED 21
#define MOTOR 27
char auth[]=BLYNK_AUTH_TOKEN;
char ssid[]= "OPPO-F19";
char pass[]= "@Bosearivu14";
unsigned int level = 0;
BlynkTimer timer;
BLYNK_WRITE(V3)
{
  int pinValue=param.asInt();
  digitalWrite(MOTOR,pinValue);
  Blynk.virtualWrite(V3,pinValue);
}
void setup() {
  pinMode(LOWLED, OUTPUT);
  pinMode(MIDLED, OUTPUT);
  pinMode (HIGHLED, OUTPUT);
  pinMode (MOTOR, OUTPUT); 
  digitalWrite(LOWLED, HIGH);
  digitalWrite(MIDLED, HIGH);
  digitalWrite(HIGHLED, HIGH);
  digitalWrite(MOTOR, LOW);
  Serial.begin(115200);
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
  Serial.print("Connecting to WiFi");
  WiFi.begin("Wokwi-GUEST","",6);
  while(WiFi.status() != WL_CONNECTED){
    delay(1000);
    Serial.print(".");
  }
  Serial.println("Connected");
  Blynk.begin(auth,"","");
}
void loop() {
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);
  int duration =pulseIn(PIN_ECHO, HIGH);
  Serial.print("Distance in CM: ");
  Serial.println(duration/58);
  Serial.print("Distance in inches: ");
  Serial.println(duration/148);
  int level=duration / 58;
  Blynk.virtualWrite(V4,level);
  if(level < 100) {
  digitalWrite(LOWLED, LOW);
  digitalWrite(MOTOR, HIGH);
  digitalWrite(HIGHLED, HIGH);
  digitalWrite(MIDLED, HIGH);
  Blynk.virtualWrite(V0,HIGH);
  Blynk.virtualWrite(V1,LOW);
  Blynk.virtualWrite(V2,LOW);
  Blynk.virtualWrite(V3,HIGH);
  }
  else if ((level >= 200) && (level <400)){
  digitalWrite(LOWLED, HIGH);
  digitalWrite(HIGHLED, HIGH);
  digitalWrite(MIDLED, LOW);
   Blynk.virtualWrite(V0,LOW);
  Blynk.virtualWrite(V1,HIGH);
   Blynk.virtualWrite(V2,LOW);
  }
  else if (level >= 400){
  digitalWrite(HIGHLED, LOW);
  digitalWrite(MIDLED, HIGH);
  digitalWrite(LOWLED, HIGH);
  digitalWrite(MOTOR,LOW);
  Blynk.virtualWrite(V0,LOW);
  Blynk.virtualWrite(V1,LOW);
  Blynk.virtualWrite(V2,HIGH);
   Blynk.virtualWrite(V3,LOW);
  }
  delay(1000);
  Blynk.run();
  }
