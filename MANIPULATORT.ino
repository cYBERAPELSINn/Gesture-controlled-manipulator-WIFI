#include <ESP8266WiFi.h>
#include <espnow.h>
#include "Wire.h"
#include <MPU6050_light.h>

int anglX;
int anglY;
int anglZ;
int anglG;
uint8_t broadcastAddress[] = {0x2C, 0xF4, 0x32, 0x53, 0xC3, 0x7B};

#define BOARD_ID 1

typedef struct struct_message {
int id;
int x;
int y;
int z;
int g;
} struct_message;

struct_message myData;

unsigned long lastTime = 0;
unsigned long timerDelay = 50;
MPU6050 mpu(Wire);
unsigned long timer = 0;
int buttonPin = D6;

void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
Serial.print("\r\nСтатус Отправки Последнего Пакета: ");
if (sendStatus == 0){ Serial.println("Сообщение доставлено"); }
else{ Serial.println("Сообщение НЕ доставлено"); }
}

void setup() {
pinMode(buttonPin, INPUT_PULLUP);
Serial.begin(9600);
WiFi.mode(WIFI_STA);
WiFi.disconnect();
Wire.begin();
byte status = mpu.begin();
Serial.print(F("MPU6050 status: "));
Serial.println(status);
while(status!=0){ }
  Serial.println(F("Calculating offsets, do not move MPU6050"));
  delay(1000);
  mpu.calcOffsets();
  Serial.println("Done!\n");
  
  if (esp_now_init() != 0) {
    Serial.println("Ошибка инициализации ESP-NOW");
    return;
  } 
  
  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);  
  esp_now_register_send_cb(OnDataSent);                                   
  esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);     
}

void loop() {
  int buttonValue = digitalRead(buttonPin);
  if (buttonValue == LOW){
    anglG=180;
  } else {
    anglG=0;
  }

  mpu.update();
  if((millis()-timer)>5){ // обновить данные каждые 5 мс
    Serial.print("X = ");
    anglX= (mpu.getAngleX());
    Serial.print(anglX);
    Serial.print("Y = ");
    anglY=(mpu.getAngleY());
    Serial.print(anglY);
    Serial.print("Z = ");
    anglZ=(mpu.getAngleZ());
    Serial.print(anglZ);
    Serial.print("G = ");
    Serial.print(anglG);
    Serial.println();
  }

  if ((millis() - lastTime) > timerDelay) {                              
    myData.id = BOARD_ID;
    myData.x = anglX;                                                     
    myData.y = anglY;
    myData.z=anglZ; 
    myData.g=anglG;                                                      
    esp_now_send(0, (uint8_t *) &myData, sizeof(myData));                
    lastTime = millis();
  }
}
