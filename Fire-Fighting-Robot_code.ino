#include <AFMotor.h>
#include <Servo.h>

Servo servo;
String msg;
#define pump 13
#define ir 2
#define digi_left A0
#define digi_mid A1
#define digi_right A2
#define anlg_left A3
#define anlg_mid A4
#define anlg_right A5
int digi_left_val, digi_mid_val, digi_right_val;
int anlg_left_val, anlg_mid_val, anlg_right_val;
int ir_val;
int i;
 
AF_DCMotor motor2(2); 
AF_DCMotor motor3(3); 
 
void setup() {
Serial.begin(9600);

servo.attach(9);

pinMode(A0,INPUT);
pinMode(A1,INPUT);
pinMode(A2,INPUT);
pinMode(A3,INPUT);
pinMode(A4,INPUT);
pinMode(A5,INPUT);
pinMode(ir,INPUT_PULLUP);
pinMode(pump, OUTPUT);

motor2.setSpeed(80); 
motor3.setSpeed(80); 

digitalWrite(pump, LOW); 
}
 
void loop() {

    ir_val = digitalRead(ir);
    digi_left_val = digitalRead(digi_left);
    digi_mid_val = digitalRead(digi_mid);
    digi_right_val = digitalRead(digi_right);
    anlg_left_val = analogRead(anlg_left);
    anlg_mid_val = analogRead(anlg_mid);
    anlg_right_val = analogRead(anlg_right);
  
  while(digi_left_val == 1 || digi_mid_val ==1 || digi_right_val == 1){
   Serial.print(digi_left_val);
   Serial.print(digi_mid_val);
   Serial.println(digi_right_val);
   digi_left_val = digitalRead(digi_left);
   digi_mid_val = digitalRead(digi_mid);
   digi_right_val = digitalRead(digi_right);
   anlg_left_val = analogRead(anlg_left);
   anlg_mid_val = analogRead(anlg_mid);
   anlg_right_val = analogRead(anlg_right);

   motor2.run(RELEASE); 
   motor3.run(RELEASE); 

   digitalWrite(pump, HIGH);
   for(i = 0; i <= 180; i++){
     servo.write(i);
     delay(10);
   }
   for(i = 180; i >= 0; i--){
     servo.write(i);
     delay(10);
   }
  }
    digitalWrite(pump, LOW);
  while(digi_left_val == 0 && digi_mid_val ==0 && digi_right_val == 0){

    if(ir_val == 1)
    {
      Serial.print(digi_left_val);
      Serial.print(digi_mid_val);
      Serial.print(digi_right_val);
      Serial.print(" || ir = ");
      Serial.println(ir_val);
      motor2.run(FORWARD); 
      motor3.run(FORWARD);
      ir_val = digitalRead(ir);
      digi_left_val = digitalRead(digi_left);
      digi_mid_val = digitalRead(digi_mid);
      digi_right_val = digitalRead(digi_right);
      anlg_left_val = analogRead(anlg_left);
      anlg_mid_val = analogRead(anlg_mid);
      anlg_right_val = analogRead(anlg_right);
  
    }

    if(ir_val == 0)
    {
      Serial.print(digi_left_val);
      Serial.print(digi_mid_val);
      Serial.print(digi_right_val);
      Serial.print(" || ir = ");
      Serial.println(ir_val);
      motor2.run(FORWARD); 
      motor3.run(BACKWARD);
      delay(1000);
      ir_val = digitalRead(ir);
      digi_left_val = digitalRead(digi_left);
      digi_mid_val = digitalRead(digi_mid);
      digi_right_val = digitalRead(digi_right);
      anlg_left_val = analogRead(anlg_left);
      anlg_mid_val = analogRead(anlg_mid);
      anlg_right_val = analogRead(anlg_right);
    }
  }
}
