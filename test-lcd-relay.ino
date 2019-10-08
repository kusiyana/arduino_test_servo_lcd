// Test basic stuff on Elegoo:
// Script written by Hayden on 08/10/2019
// test script to turn on relay with infrared and adjust servo at the same time
// angle is displayed on LCD screen


#include <LiquidCrystal.h>
#include <Stepper.h>
#include "IRremote.h"
#include <Servo.h>

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
IRrecv irrecv(2);
Servo myservo;
decode_results results; 

int servo_input_pin = 3;

const int relay_input_pin = A0;
int starting_angle = 90;
int current_angle = starting_angle;
int angle_increment = 10;
int baudrate = 9600;

int servo_shift = 0;
void setup() {
  pinMode(relay_input_pin, OUTPUT);
  digitalWrite(relay_input_pin,HIGH); // Turns Relay Off
  Serial.begin(baudrate);
  myservo.attach(servo_input_pin);
  myservo.write(starting_angle);
  irrecv.enableIRIn(); 
  lcd.print("Initialise servo");
  
}

void loop() { 
 if (irrecv.decode(&results)){
       Serial.print("result = " + String(translateIR_servo()));
    if (translateIR_servo() == 1){
      digitalWrite(relay_input_pin,HIGH); // Turn Relay Off
      Serial.print("angle = " + String(current_angle));
      current_angle = current_angle + angle_increment;
    }
    else {
      digitalWrite(relay_input_pin,LOW); // Turns Relay On
      current_angle = current_angle - angle_increment;
    }
    myservo.write(current_angle);
    lcd.clear();
    lcd.print("Servo shift: " + String(current_angle));           
    delay(100);
    irrecv.resume();
  }  
}


int translateIR_servo(){
  int output = 0;
  switch(results.value){
  case 0xFFE01F: output = 1;    break;
  case 0xFF906F: output = 2;    break;
  default: 
    output = 0;
  }// End Case
  return(output); 
}

void translateIR(){
  switch(results.value){
  case 0xFFA25D: Serial.println("POWER"); break;
  case 0xFFE21D: Serial.println("FUNC/STOP"); break;
  case 0xFF629D: Serial.println("VOL+"); break;
  case 0xFF22DD: Serial.println("FAST BACK");    break;
  case 0xFF02FD: Serial.println("PAUSE");    break;
  case 0xFFC23D: Serial.println("FAST FORWARD");   break;
  case 0xFFE01F: Serial.println("DOWN");    break;
  case 0xFFA857: Serial.println("VOL-");    break;
  case 0xFF906F: Serial.println("UP");    break;
  case 0xFF9867: Serial.println("EQ");    break;
  case 0xFFB04F: Serial.println("ST/REPT");    break;
  case 0xFF6897: Serial.println("0");    break;
  case 0xFF30CF: Serial.println("1");    break;
  case 0xFF18E7: Serial.println("2");    break;
  case 0xFF7A85: Serial.println("3");    break;
  case 0xFF10EF: Serial.println("4");    break;
  case 0xFF38C7: Serial.println("5");    break;
  case 0xFF5AA5: Serial.println("6");    break;
  case 0xFF42BD: Serial.println("7");    break;
  case 0xFF4AB5: Serial.println("8");    break;
  case 0xFF52AD: Serial.println("9");    break;
  case 0xFFFFFFFF: Serial.println(" REPEAT");break;  
  default: 
    Serial.println(" other button   ");
  }// End Case
}
