#include <Arduino.h>

//This command active a led.
void turnOnLed(int led){
  digitalWrite(led,HIGH);
}

//This command desactive a led.
void turnOffLed(int led){
  digitalWrite(led,LOW);
}

//This sound is emited when the alarm is activated.
void alarm(int buzzer, int led1, int led2){
  //Turn ON leds.
  turnOnLed(led1);
  turnOnLed(led2);

  //Turn ON buzzer.
  tone(buzzer, 1000);
  delay(180);
  
  //Turn OFF buzzer.  
  noTone(buzzer);
  
  //Turn OFF leds.  
  turnOffLed(led1);
  turnOffLed(led2);  
  delay(180);
}

//This sound is emited, when the button is pressed.
void okSound(int buzzer){
  tone(buzzer, 500);
  delay(100);
  noTone(buzzer);
  delay(100);
  tone(buzzer, 500);
  delay(100);
  noTone(buzzer);
}

//BEEP sound.
void beepSound(int buzzer){
  tone(buzzer, 200);
  delay(500);
  noTone(buzzer);
}

//Time functions.
String make_time(int hour,int minute){
  String mn;
  String hs;

  if (minute<10)
    mn = "0"+String(minute);
  else
    mn = String(minute);

  if (hour<10)
    hs = "0"+String(hour);
  else
    hs = String(hour);

  return String(hs)+String(mn);
}
