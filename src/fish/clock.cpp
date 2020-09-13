#include <Arduino.h>
#include <Wire.h>
#include "clock.h"

void setupClock(){
  pinMode(A4, OUTPUT);
  digitalWrite(A4, HIGH);
  pinMode(A5, OUTPUT);
  digitalWrite(A5, LOW);
  Wire.begin();
}

clock_time read_ds1307(){

  //Recibimos el byte del registro 0x00 y lo convertimos a binario
  clock_time newTime;
    
  //Iniciar el intercambio de información con el DS1307 (0xD0)
  Wire.beginTransmission(0x68);

  //Escribir la dirección del segundero
  Wire.write(0x00);

  //Si la escritura se llevo a cabo el metodo endTransmission retorna 0
  if (Wire.endTransmission() != 0){
    newTime.active = false;
    return newTime;
  }

  //Si el DS1307 esta presente, comenzar la lectura de 8 bytes
  Wire.requestFrom(0x68, 8);

  //Read and fill the data.
  newTime.second = bcd2bin(Wire.read());
  newTime.minute = bcd2bin(Wire.read());
  newTime.hour = bcd2bin(Wire.read());
  newTime.wday = bcd2bin(Wire.read());
  newTime.day = bcd2bin(Wire.read());
  newTime.month = bcd2bin(Wire.read());
  newTime.year = bcd2bin(Wire.read());
  newTime.active = 1;

  //Recibir los datos del registro de control en la dirección 0x07
  uint8_t ctrl = Wire.read();

  //Return the time typedef.
  return newTime;
}

uint8_t bcd2bin(uint8_t bcd){
  return (bcd / 16 * 10) + (bcd % 16);
}

void print_time(clock_time timeParam){
  Serial.print("Fecha: ");
  Serial.print(timeParam.day);
  Serial.print('/');
  Serial.print(timeParam.month);
  Serial.print('/');
  Serial.print(timeParam.year);
  Serial.print("  Hora: ");
  Serial.print(timeParam.hour);
  Serial.print(':');
  Serial.print(timeParam.minute);
  Serial.print(':');
  Serial.print(timeParam.second);
  Serial.print(" clock-active:");
  Serial.print(timeParam.active);
  Serial.println();
}

clock_time createTime(int hs, int min, int sec){
  clock_time tmp;
  
  tmp.hour=hs;
  tmp.minute=min;
  tmp.second=sec;
  
  return tmp;

}

int convertTime(int hour, int minutes){
  return hour*60+minutes;
}

boolean inTime(clock_time nowTime, clock_time startTime, clock_time endTime){
  //Convert time to minutes.
  int start = convertTime(startTime.hour,startTime.minute);
  int end = convertTime(endTime.hour,endTime.minute);
  int now = convertTime(nowTime.hour,nowTime.minute);

  //Check if is in the middle.
  if (start<=end)
    return ((now >= start)&&(now < end));
  else
    return ((now >= start)||(now < end));
}
