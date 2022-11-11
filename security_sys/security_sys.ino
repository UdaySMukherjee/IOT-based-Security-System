#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "aDSUVTToqqgHB9FMLQJLCApgo7DnWwEV";
char ssid[] = "Airtel-MyWiFi-AMF-311WW-110F";
char pass[] = "46c2c5a9";

BlynkTimer timer;

#define Buzzer D0
#define Relay1 D1
#define Relay2 D2
#define exhaust D3
#define Ldr D4
#define Gas A0
#define Flame D5


void setup() {
  Serial.begin(9600);
  pinMode(Relay1, OUTPUT);
  pinMode(Relay2, OUTPUT);
  pinMode(Buzzer, OUTPUT);
  pinMode(exhaust, OUTPUT);

  pinMode(Gas, INPUT);
  pinMode(Ldr, INPUT);
  pinMode(Flame, INPUT);
  
  digitalWrite(Relay1, LOW);
  digitalWrite(Relay2, HIGH);
  digitalWrite(Buzzer, LOW);
  digitalWrite(exhaust, LOW);
  
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, sensorData);
}

void sensorData(){
  int data1 = analogRead(Gas);
  Serial.println(data1);
  Blynk.virtualWrite(V0, data1);
  if(data1 > 650 ){
    Blynk.notify("Gas Leak Detected!");
    Blynk.email("udaysankar2003@gmail.com","Kitchen","Alert! Gas Leakage Detected");
    digitalWrite(exhaust, HIGH);
    digitalWrite(Buzzer, HIGH);
  }
  
  int data2 = digitalRead(Flame);
  if (data2== 0) {
      Blynk.notify("WARNING! A fire was detected");
      Blynk.email("udaysankar2003@gmail.com","Flame","WARNING! A fire was detected");
      digitalWrite(Relay2, LOW);
      digitalWrite(Relay1, HIGH);
      digitalWrite(Buzzer, HIGH);
    }

  int data3 = digitalRead(Ldr);
  if (data2==1) {
      //Blynk.notify("WARNING! Security Breached!! ");
      Blynk.email("udaysankar2003@gmail.com","Main Gate","WARNING! Security Breached!! ");
      digitalWrite(Buzzer, HIGH);
    }
}


void loop() {
  Blynk.run();
  timer.run();
}
