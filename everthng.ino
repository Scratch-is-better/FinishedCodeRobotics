#include <Servo.h>

// line sensor
const int line = 8;

// motor control pins
const int in1 = 4;
const int in2 = 6;
const int ena = 5;

// ultrasonic pins
const int trigPin = 2;
const int echoPin = 11;

const int led = 12;

// potentiometer input for controlling servo
const int pot = A0;

Servo MyServo;

//
const int buzzer = 9;
const int button = 3;

int freq_array[] = {300, 120, 800, 300}; 

void stopSound()
{
    if(digitalRead(button) == LOW)
    {
        // TODO: mutex to protect simultaneous control from main loop 
        noTone(buzzer);   
    }
}

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
    attachInterrupt(digitalPinToInterrupt(button), stopSound, CHANGE);
}

void buzz()
{
    if(digitalRead(button) == HIGH)
    {
        for(int freq: freq_array)
        {  
            tone(buzzer, freq);
            // TODO: move this code to a timer interrupt so as to not hold up main loop
            delay(400);
            noTone(buzzer);
            
            if(digitalRead(button) == LOW)
                break;   
        } 
    }
}

void servo()
{
    int input = analogRead(pot);
    
    input = map(input, 0, 1023 ,0, 180);
    
    Serial.println(input);
    MyServo.write(input);
}

long microsecondsToCentimetres(long microseconds)
{
    return microseconds / 29 / 2;
}

void sonic()
{    
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(5);
    digitalWrite(trigPin, LOW);
    
    long duration = pulseIn(echoPin, HIGH);
    
    long cm = microsecondsToCentimetres(duration);
    
    if (cm <= 330) {
        digitalWrite(led, HIGH);
        delay(cm + 50);
        digitalWrite(led, LOW);
        delay(cm + 50);  
    }
    else (cm > 330)
    {
        digitalWrite(led, LOW);
    }
}

void moto()
{
    int s1 = digitalRead(line);
    if(s1 == HIGH) {
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
        analogWrite(ena, 150);
    }
    else {
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
        analogWrite(ena, 300);
    }
    
    Serial.println(s1);
    delay(100);
}


void loop()
{
    sonic();
    servo();
    buzz();
    moto();
}

