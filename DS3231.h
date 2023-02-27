#include <DS3231.h>

// settings

int fadeTime = 1;

//Set time for alarm to begin
int setHour = 12; //set alarm hour
int setMin = 01; //set alarm minute

//Set clock to current time
int clockHour = 12;
int clockMin = 00;

//bcd table
int bcd[10] = {0b000000, 0b100000, 0b010000, 0b110000, 0b001000, 0b101000, 0b011000, 0b111000, 0b00010, 0b100100};
//                   [0,        1,        2,        3,        4,        5,        6,        7,       8,        9]
// pin ~3 PWM
int uled = 3;

//sets output pins for bcd output
int bcdOut0 = 13;
int bcdOut1 = 12;
int bcdOut2 = 11;
int bcdOut3 = 10;

//sets output control pins
int controlOut0 = 7;
int controlOut1 = 6;
int controlOut2 = 5;
int controlOut3 = 4;

//initializes four integers for time display
int hourTens;
int hourOnes;
int minuteTens;
int minuteOnes;

int maxBrightness = 255;

DS3231 rtc(SDA, SCL);
Time t;

void setup() {

  // sets our light as the output on pin ~ 9 which is PWM
  
  pinMode(uled, OUTPUT);
  digitalWrite(uled, LOW);

  // sets output pins for controling 7-segment display
  DDRB = B111110;

  pinMode(controlOut0, OUTPUT);
  digitalWrite(controlOut0, HIGH);
  pinMode(controlOut1, OUTPUT);
  digitalWrite(controlOut1, HIGH);
  pinMode(controlOut2, OUTPUT);
  digitalWrite(controlOut2, HIGH);
  pinMode(controlOut3, OUTPUT);
  digitalWrite(controlOut3, HIGH);
  
  // begins serial communication
  
  Serial.begin(9600);
  
  rtc.begin(); //initialize the rtc object
  rtc.setTime(clockHour,clockMin,0);
}

void loop() {
  // put your main code here, to run repeatedly:

  display();

  //prints time to serial monitor
//  Serial.print("SET: ");
//  Serial.print(setHour);
//  Serial.print(":");
//  Serial.print(setMin);
//  Serial.print(" NOW:");
//  Serial.print(t.hour, DEC);
//  Serial.print(":");
//  Serial.print(t.min, DEC);
//  
//  Serial.print(" CLOCK:");
//  Serial.println(rtc.getTimeStr());

  if (t.hour == setHour && t.min == setMin) {
      active();
      }
}

void active() {
  
//  Serial.println(" led turned on");

  // fade begin
  
  // the delay functions are to prevent the LED from becoming too bright 
  // in the early stages of the fadetime. 
  
  analogWrite(uled, 1);
  for(int x =0; x<(fadeTime * 60000)/50; x++){
    display();
    delay(1/7);
  }
  
  analogWrite(uled, 2);
  for(int x =0; x<(fadeTime * 60000)/50; x++){
    display();
    delay(1/7);
  }
  
  analogWrite(uled, 3);
  for(int x =0; x<(fadeTime * 60000)/50; x++){
    display();
    delay(1/7);
  }
  
  analogWrite(uled, 4);
  for(int x =0; x<(fadeTime * 60000)/50; x++){
    display();
    delay(1/7);
  }
  
  analogWrite(uled, 5);
  for(int x =0; x<(fadeTime * 60000)/50; x++){
    display();
    delay(1/7);
  }

  // for statement controls the speed 
  // at which the light should get brighter and brighter
  // depending on the fadetime.

  for (int i = 6; i <= 255; i++) {
    display();
    analogWrite(uled, i);
  }
    for(int x =0; x<(fadeTime * 60000)/306; x++){
      display();
      delay(1/7);
    }

    for(int x =0; x<(fadeTime * 60000)/5; x++){
      display();
      delay(1/7);
    }
    
    // shuts the light off. 
    analogWrite(uled, 0);
    loop();
  }

void display(){
  //pull time from rtc
  t=rtc.getTime();
  
  //break time into four bcd digits
  hourTens = bcd[t.hour/10];
  hourOnes = bcd[t.hour%10];
  minuteTens = bcd[t.min/10];
  minuteOnes = bcd[t.min%10];
  
  //sets register B data to time
  PORTB = hourTens;
  digitalWrite(controlOut0, LOW);
  delay(1);
  digitalWrite(controlOut0, HIGH);

  PORTB = hourOnes;
  digitalWrite(controlOut1, LOW);
  delay(1);
  digitalWrite(controlOut1, HIGH);

  PORTB = minuteTens;
  digitalWrite(controlOut2, LOW);
  delay(1);
  digitalWrite(controlOut2, HIGH);

  PORTB = minuteOnes;
  digitalWrite(controlOut3, LOW);
  delay(1);
  digitalWrite(controlOut3, HIGH);
  }
