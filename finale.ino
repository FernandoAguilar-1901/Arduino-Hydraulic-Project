#include <Servo.h>
int relaySignal = 9;
int waterLevel;
Servo servo_gate;
int Trigger = 2;
int Echo = 3;


void setup() { 
  Serial.begin(9600);
  pinMode(relaySignal, OUTPUT);
  digitalWrite(relaySignal, LOW);
  servo_gate.attach(11);
  pinMode(Trigger, OUTPUT);
  pinMode(Echo, INPUT);
  digitalWrite(Echo, LOW);
}

void loop() {
  waterLevel = analogRead(A0);
  digitalWrite(Trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trigger, LOW);
  long time;
  long distance;

  time = pulseIn(Echo, HIGH);
  distance = time/59;

  if(waterLevel == 0){
    digitalWrite(relaySignal, HIGH);
    servo_gate.write(90);
    delay(1500);
  } 
  
  if (waterLevel > 100 && distance < 35 ){
    digitalWrite(relaySignal, LOW);
    servo_gate.write(180);
    delay(500);
  }

  if (distance > 35 ) {
    delay(3000);
    servo_gate.write(90);
  }

  Serial.print("Nivel de agua: ");
  Serial.print(waterLevel);
  Serial.println();
  Serial.print("Distancia: ");
  Serial.print(distance);     
  Serial.print("cm");

  delay(200);

}
