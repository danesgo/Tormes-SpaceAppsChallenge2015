#include <Wire.h>
#include <DHT22.h>
#include <SFE_BMP180.h>
#include <stdio.h>
#include <RTClib.h>
#include <SFE_BMP180.h>

#define MPU6050 0B1101000 
#define A_R 0b11111111111111
#define DHT22_PIN 7
#define ALTITUDE 1655.0
 
int16_t Ax,Ay,Az,Gx,Gy,Gz,Tm;
float Temp, Humd;
int sensor1Pin = A0;
int sensor2Pin = A1;
int sensor1Value = 0;
int sensor2Value = 0;
  char status;
  double T,P,p0,a;


DHT22 myDHT22(DHT22_PIN);
SFE_BMP180 pressure;
RTC_DS1307 RTC;

void setup()
{
  Wire.begin();
  Wire.beginTransmission(MPU6050);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  
  DHT22_ERROR_t errorCode;
  delay(2000);
  
  pressure.begin();
  
  Serial.begin(9600);
  Serial1.begin(9600);
}

void loop()
{ 
  DHT22_ERROR_t errorCode;
  
  errorCode = myDHT22.readData();

  Temp=myDHT22.getTemperatureC();
  Humd=myDHT22.getHumidity();
  
  sensor1Value = analogRead(sensor1Pin);
  sensor2Value = analogRead(sensor2Pin);

  status = pressure.startTemperature();
  status = pressure.getTemperature(T);
  status = pressure.startPressure(3);
  status = pressure.getPressure(P,T);

  DateTime now = RTC.now();
  
  delay(10);    
    
  Wire.beginTransmission(MPU6050);
  Wire.write(0B111011);
  Wire.endTransmission(false); 
  
  Wire.requestFrom(MPU6050,14,true);
  
  Ax=Wire.read()<<8|Wire.read();
  Ay=Wire.read()<<8|Wire.read();
  Az=Wire.read()<<8|Wire.read();
  Tm=Wire.read()<<8|Wire.read();
  Gx=Wire.read()<<8|Wire.read();
  Gy=Wire.read()<<8|Wire.read();
  Gz=Wire.read()<<8|Wire.read();

  Serial.println(String(Ax)+":"+String(Ay)+":"+String(Az)+":"+String(Gx)+":"+String(Gy)+":"+String(Gz)+":"+String(Tm)+":"+String(Temp)+":"+String(T)+":"+String(Humd)+":"+String(sensor1Value)+":"+String(sensor2Value)+":"+String(P)+":F");  
  Serial1.println(String(Ax)+":"+String(Ay)+":"+String(Az)+":"+String(Gx)+":"+String(Gy)+":"+String(Gz)+":"+String(Tm)+":"+String(Temp)+":"+String(T)+":"+String(Humd)+":"+String(sensor1Value)+":"+String(sensor2Value)+":"+String(P)+":F"); 

  delay(10);
}
