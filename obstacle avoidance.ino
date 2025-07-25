#include <Servo.h>          //Servo motor library. This is standard library
#include <NewPing.h>        //Ultrasonic sensor function library. You must install this library
#include <SoftwareSerial.h>
//our L298N control pins
const int LeftMotorForward = 2;
const int LeftMotorBackward = 3;
const int LeftMotorEnable = 12;
const int RightMotorForward = 4;
const int RightMotorBackward = 5;
const int RightMotorEnable = 13;


// Pin numbers for the bluetooth module
const int bluetoothTx = 1;
const int bluetoothRx = 0;

// Create a software serial object for the bluetooth module
SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);

//sensor pins
#define trig_pin A1 //analog input 1
#define echo_pin A2 //analog input 2

#define maximum_distance 250
boolean goesForward = false;
int distance = 150;

NewPing sonar(trig_pin, echo_pin, maximum_distance); //sensor function
Servo servo_motor; //our servo name


void setup(){

  Serial.begin(9600);

  // Begin the software serial communication with the bluetooth module
  bluetooth.begin(9600);

  pinMode(RightMotorForward, OUTPUT);
  pinMode(LeftMotorForward, OUTPUT);
  pinMode(LeftMotorBackward, OUTPUT);
  pinMode(RightMotorBackward, OUTPUT);
  pinMode(LeftMotorEnable, OUTPUT);
  pinMode(RightMotorEnable, OUTPUT);
  servo_motor.attach(8); //our servo pin

  servo_motor.write(135);
  delay(2000);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
}

void loop(){
  //p1();
  p2();
}

void p1(){

  int distanceRight = 0;
  int distanceLeft = 0;
  delay(50);

  if (distance <= 20){
    moveStop();
    delay(300);
    moveBackward();
    delay(400);
    moveStop();
    delay(300);
    distanceRight = lookRight();
    delay(300);
    distanceLeft = lookLeft();
    delay(300);

    if (distance >= distanceLeft){
      turnRight();
      moveStop();
    }
    else{
      turnLeft();
      moveStop();
    }
  }
  else{
    moveForward(); 
  }
    distance = readPing();

}

int lookRight(){  
  servo_motor.write(70);
  delay(500);
  int distance = readPing();
  delay(100);
  servo_motor.write(135);
  return distance;
}

int lookLeft(){
  servo_motor.write(175);
  delay(500);
  int distance = readPing();
  delay(100);
  servo_motor.write(135);
  return distance;
  delay(100);
}

int readPing(){
  delay(70);
  int cm = sonar.ping_cm();
  if (cm==0){
    cm=250;
  }
  return cm;
}

void p2() {
  // Check if there is any data available from the bluetooth module
  if (bluetooth.available()) {
    // Read the incoming byte from the bluetooth module
    char command = bluetooth.read();

    // Control the robot based on the received command
    switch (command) {
      case 'F': // Move forward
        moveForward();
        break;
      case 'B': // Move backward
        moveBackward();
        break;
      case 'L': // Turn left
        turnLeft();
        break;
      case 'R': // Turn right
        turnRight();
        break;
      case 'S': // Stop
        moveStop();
        break;
    }
  }
}
 


void moveStop(){
  
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(LeftMotorEnable, 0);

  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorEnable, 0);
}

void moveForward(){

  if(!goesForward){

    Serial.println("==moveForward==");

    goesForward=true;
    
    digitalWrite(LeftMotorForward, HIGH);
    digitalWrite(RightMotorForward, HIGH);
    digitalWrite(LeftMotorEnable, 225);
  
    digitalWrite(LeftMotorBackward, LOW);
    digitalWrite(RightMotorBackward, LOW); 
    digitalWrite(RightMotorEnable, 225);
  }
}

void moveBackward(){

  goesForward=false;

  Serial.println("==moveBackward==");

  digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(RightMotorBackward, HIGH);
  digitalWrite(LeftMotorEnable, 50);
  
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(RightMotorEnable, 50);
}

void turnRight(){

  Serial.println("==turnRight==");

  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorBackward, HIGH);
  digitalWrite(RightMotorEnable, 100);

  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(LeftMotorEnable, 50);
  delay(500);
  
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorForward, HIGH);
  digitalWrite(RightMotorEnable, 100);
  
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorEnable, 50);
 
  
  
}

void turnLeft(){

  Serial.println("==turnLeft==");

  digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(RightMotorForward, HIGH);
  digitalWrite(RightMotorEnable, 100);
  
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorEnable, 50);

  delay(500);
  
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorForward, HIGH);
  digitalWrite(RightMotorEnable, 100);
  
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorEnable, 50);
}

