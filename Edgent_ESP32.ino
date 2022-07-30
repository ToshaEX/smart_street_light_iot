
// Fill-in information from your Blynk Template here
#define BLYNK_TEMPLATE_ID "TMPLLYG-1xaT"
#define BLYNK_DEVICE_NAME "Quickstart Template"

#define BLYNK_FIRMWARE_VERSION        "0.1.0"

#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG

#define APP_DEBUG
#define DEEP_SLEEP_TIME 15
// Uncomment your board, or configure a custom board in Settings.h
//#define USE_WROVER_BOARD
//#define USE_TTGO_T7
//#define USE_ESP32C3_DEV_MODULE
//#define USE_ESP32S2_DEV_KIT

#include "BlynkEdgent.h"

int emergencyOn=0;
int led1=21,led2=19,led3=18,led4=22,led5=23;
int ir1=12,ir2=13,ir3=14,ir4=27,ir5=26;
int isOn1=0,isOn2=0,isOn3=0,isOn4=0,isOn5=0;
int  irVal1,irVal2,irVal3,irVal4,irVal5;
int ldr=39;//vn
void objectDetect();

BLYNK_WRITE(V0){
  int pinValue=param.asInt();
  emergencyOn=pinValue;
  lightOn(led1,pinValue,isOn1);
  lightOn(led2,pinValue,isOn2);
  lightOn(led3,pinValue,isOn3);
  lightOn(led4,pinValue,isOn4);
  lightOn(led5,pinValue,isOn5);
 }
 
 BLYNK_WRITE(V1){
  int pinValue=param.asInt();
  isOn1=pinValue;
  digitalWrite(led1,pinValue);//led1
 }
 BLYNK_WRITE(V2){
  int pinValue=param.asInt();
  isOn2=pinValue;
  digitalWrite(led2,pinValue);//led2
 }
 BLYNK_WRITE(V3){
  int pinValue=param.asInt();
  isOn3=pinValue;
  digitalWrite(led3,pinValue);//led3
 }
 BLYNK_WRITE(V4){
  int pinValue=param.asInt();
  isOn4=pinValue;
  digitalWrite(led4,pinValue);//led4
 }
 BLYNK_WRITE(V5){
  int pinValue=param.asInt();
  isOn5=pinValue;
  digitalWrite(led5,pinValue);//led5
 }
 
void setup()
{
  pinMode(led1,OUTPUT);//LED1
  pinMode(led2,OUTPUT);//LED2
  pinMode(led3,OUTPUT);//LED3
  pinMode(led4,OUTPUT);//LED4
  pinMode(led5,OUTPUT);//LED5

  pinMode(ir1,INPUT);//IR1
  pinMode(ir2,INPUT);//IR2
  pinMode(ir3,INPUT);//IR3
  pinMode(ir4,INPUT);//IR4
  pinMode(ir5,INPUT);//IR5

  pinMode(ldr,INPUT);//LDR
  
  Serial.begin(115200);
  delay(100);

  BlynkEdgent.begin();
}

void loop() {
  BlynkEdgent.run();
  if(!emergencyOn){
  int ldrVal=analogRead(ldr);
    //Serial.print("ldr:");
    //Serial.println(ldrVal);
    if(ldrVal<150){
      systemOn();
      Serial.println("System On......");   
     }else{
      Serial.println("System Off... LDR value High");
      }
  }else{Serial.println("Emergency On...");}
}

void systemOn(){
  readingIrs();
  objectDetect(irVal1,led1,isOn1);
  objectDetect(irVal2,led2,isOn2);
  objectDetect(irVal3,led3,isOn3);
  objectDetect(irVal4,led4,isOn4);
  objectDetect(irVal5,led5,isOn5);
  
}
void readingIrs(){
  irVal1=digitalRead(ir1);
  irVal2=digitalRead(ir2);
  irVal3=digitalRead(ir3);
  irVal4=digitalRead(ir4);
  irVal5=digitalRead(ir5);
 }
 
void lightOn(int led,int pinVal,int isOn){
  if(!isOn){
    digitalWrite(led,pinVal);
    }
  }
  
void objectDetect(int irVal,int led,int isOn){
  if(!isOn){
     if(!irVal){
        digitalWrite(led,HIGH);
        delay(300);  
     }else{
      digitalWrite(led,LOW);    
     }
  }
}
