#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <Servo.h>
#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>
#include <SoftwareSerial.h>

SoftwareSerial EspSerial(8, 9); // RX, TX

#define ESP_SSID "G3_2944"
#define ESP_PASS "1q2w3e4r"
char auth[] = "14f620c6c7ac472e82f44bba939e5789";

ESP8266 wifi(&EspSerial);

Servo servo;
int currentStage = 0;
int nextStage;

void setup()
{
  Serial.begin(9600);     // Set console baud rate
  servo.attach(11);
  servo.write(0);
  delay(1000);
  EspSerial.begin(9600);  // Set ESP8266 baud rate
  delay(10);
  Blynk.begin(auth, wifi, ESP_SSID, ESP_PASS);
}

void loop() {
  Blynk.run();
}

BLYNK_WRITE(V0)
{
  Serial.println(param.asInt());
  
  nextStage = param.asInt();
  
  if (nextStage > 55){
    nextStage = 55;
  }

  // flower move up
  if (currentStage <= nextStage){
    for (int i = currentStage; i < nextStage; i++){
      servo.write(i); 
      delay(15);
    }
    currentStage = nextStage;
  } 
  // flower move down
  else {
      for (int i = currentStage ; i >= nextStage; i--){
      servo.write(i); 
      delay(0);
    }
    currentStage = nextStage;
  }
}
