// this sample program is for AOSONG AHT30 Humidity sensor   by okinawanwinds 20241203
// datasheet https://eleparts.co.kr/data/goods_attach/202306/good-pdf-12751003-1.pdf

#include "Wire.h"
#define I2C_DEV_ADDR 0x38

void setup() {
  Serial.begin(115200);
  Wire.begin(21,22);  // for ESP32; other arduino uses A4, A5
  delay(1000);
}

void loop() {
  Wire.beginTransmission( I2C_DEV_ADDR);
  Wire.write(0xAC);
  Wire.write(0x33);
  Wire.write(0x00);  
  Wire.endTransmission();
  delay(80);  
  Wire.beginTransmission( I2C_DEV_ADDR);
  Wire.write(0x71);
  uint8_t bytesReceived = Wire.requestFrom(I2C_DEV_ADDR, 7, true);
  if (Wire.available()==7) { 
    uint8_t rd[bytesReceived];
    Wire.readBytes(rd, bytesReceived);
    double Ondo = ( (rd[3]&0x0F)*65536 + rd[4]*256 + rd[5] ) *200.0 / pow(2,20) -50;
    double humi = ( rd[1]*4096+rd[2]*16+(rd[3]>>4) )  *100.0 / pow(2,20);
    Serial.printf("Ondo %5.2fc    Humi %5.2f%% \n", Ondo, humi);
  }
  delay(1000);
}
