const int line = 8;

const int in1 = 4;
const int in2 = 6;
const int ena = 5;
//
const int trigPin = 2;
const int echoPin = 11;
const int led = 12;
//
const int pot = A0;
#include <Servo.h>

Servo MyServo;
//
const int buzzer = 9;
const int button = 3;


void setup()
{
//line sensor
pinMode(line, INPUT);
pinMode(in1, OUTPUT);
pinMode(in2, OUTPUT);
pinMode(ena, OUTPUT);
//ultra sonic
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
pinMode(led, OUTPUT);
//servo
pinMode(pot, INPUT);
 MyServo.attach(10);
 //buzzer
  pinMode(buzzer, OUTPUT);
  pinMode(button, INPUT);
  Serial.begin(9600);
}

void buzz() {
   if(digitalRead(button) == HIGH){

    tone(buzzer, 20);
   delay(500);
    noTone(buzzer);
    tone(buzzer, 1500);
    delay(500);
    noTone(buzzer);
    tone(buzzer, 2000);
    delay(500);
    noTone(buzzer);
    tone(buzzer, 1000);
    delay(500);
    noTone(buzzer);
    tone(buzzer, 1500);
    delay(500);
    noTone(buzzer);

  } if(digitalRead(button) == LOW) {

     noTone(buzzer); 
  }
}

void servo(){
int input = analogRead(pot);

  input = map(input, 0, 1023 ,0, 180);

  Serial.println(input);
  MyServo.write(input);

}


void sonic(){

 long duration, cm;
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);

  
  cm = microsecondsToCentimetres(duration);
  
  
    if (cm <= 330){
digitalWrite(led, HIGH);
delay(cm + 50);
digitalWrite(led, LOW);
delay(cm + 50);  
}
  else (cm > 330)
  {
    digitalWrite(led, LOW);
  }
  


long microsecondsToCentimetres(long microseconds)
{
  return microseconds / 29 / 2;
}

}


  
  
