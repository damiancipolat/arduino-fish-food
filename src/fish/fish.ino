#include "lib.h"
#include "clock.h"

//Components pins.
int RED =12;
int BLUE =11;
int BUZZER =10;
int BUTTON_PIN=9;

//State variables.
int buttonState;
int foodLock=0;

//Define times;
clock_time current_time;
clock_time FOOD_START = createTime(9,0,0);
clock_time FOOD_END = createTime(12,0,00);
clock_time SLEEP_START = createTime(23,0,0);
clock_time SLEEP_END = createTime(8,0,0);

void setup(){    
  //Define digital pins.
  pinMode(RED,OUTPUT);
  pinMode(BLUE,OUTPUT);
  Serial.begin(9600);
  pinMode(BUZZER, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);   
  setupClock();
}

void foodRequiredMode(){
  //Show no food led.
  turnOnLed(RED);
  turnOffLed(BLUE);

  //If food time.
  if (inTime(current_time,FOOD_START,FOOD_END)){    
    Serial.println("Alimentar los peces!!");

    //If the button is pressed.
    if (buttonState){
      foodLock=1;
      okSound(BUZZER);
    }

    //Active alarm.
    alarm(BUZZER,RED,BLUE);    
  }
}

void foodReadyMode(){
 //Show food led.
  turnOnLed(BLUE);
  turnOffLed(RED);

  //Go to leep mode.
  if (inTime(current_time,SLEEP_START,SLEEP_END)){
    Serial.println("Pasando a modo Sleep!!");
    
    //Set to inactive.
    foodLock=2;

    //Beep.
    beepSound(BUZZER);
    
    //Desactive leds.
    turnOffLed(RED);
    turnOffLed(BLUE);    
  }
}

void sleepMode(){
  //Go to leep mode.
  if (!inTime(current_time,SLEEP_START,SLEEP_END)){
    Serial.println("Desactivando sleep...");
        
    //Set to inactive.
    foodLock=0;

    //Beep.
    beepSound(BUZZER);
    
    //Desactive leds.
    turnOnLed(RED);
    turnOffLed(BLUE);    
  }
}

void loop() {
  
  //Save the current time.
  current_time = read_ds1307();
  print_time(current_time);

  //Save the push button status;
  buttonState = !digitalRead(BUTTON_PIN);
  Serial.println(buttonState);

  //If the clock is activated.
  if (current_time.active){

   Serial.println("> Mode:"+String(foodLock));

    //Main logic.
    switch (foodLock) {
      case 0:
        foodRequiredMode();
        break;
      case 1:
        foodReadyMode();
        break;
      case 2:
        sleepMode();
        break;
    }

  }
  
}
