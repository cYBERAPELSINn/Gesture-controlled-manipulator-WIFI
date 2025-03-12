#include <ESP8266WiFi.h>
#include <espnow.h>
#include <MPU6050_light.h>
#include "Wire.h"
#include <Servo.h>

Servo servoX;
Servo servoY;
Servo servoZ;
Servo servoG;
int x;
int y;
int z;
int g;
int servox;
int servoy;
int servoz;
int servog;

typedef struct struct_message {
    int id;
    int x;
    int y;
    int z;
    int g;
} struct_message;

struct_message myData;
struct_message board1;
struct_message board2;
struct_message boardsStruct[2] = {board1, board2};

void OnDataRecv(uint8_t * mac_addr, uint8_t *incomingData, uint8_t len) {
  char macStr[18];
  memcpy(&myData, incomingData, sizeof(myData));
  boardsStruct[myData.id-1].x = myData.x;
  boardsStruct[myData.id-1].y = myData.y;
  boardsStruct[myData.id-1].z = myData.z;
  boardsStruct[myData.id-1].g = myData.g;
}
 
void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  servoX.attach(13,500,2400);
  servoY.attach(14,500,2400); 
  servoZ.attach(12,500,2400);
  servoG.attach(16,500,2400);
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  esp_now_register_recv_cb(OnDataRecv);
}

void loop(){
  int board1X = boardsStruct[0].x;
  int board1Y = boardsStruct[0].y;
  int board1Z = boardsStruct[0].z;
  int board1G = boardsStruct[0].g;
  Serial.print("Угол Х");Serial.println(board1X);
  Serial.print("Угол У");Serial.print(board1Y);
  Serial.print("Угол Z");Serial.print(board1Z);
  Serial.print("Угол G");Serial.print(board1G);
  Serial.println();

  servox = map(board1X, -90, 90, 20, 160); 
  servoy = map(board1Y, -90, 90, 40, 140); 
  servoz = map(board1Z, -90, 90, 70, 110);
  servoX.write(servox);
  servoY.write(servoy);
  servoZ.write(servoz);
  servoG.write(board1G);
