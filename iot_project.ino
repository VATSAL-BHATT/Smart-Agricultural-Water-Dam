#include <Servo.h>

Servo servo_10;

int TRIG = 5;
int ECHO = 4;
int RELAY = 12;   // Relay pin
int soilMoisture=A0;
int Relay2=8;

long duration;
float distance;
float waterLevel;
float percentage;

void setup() {
  Serial.begin(9600);

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(RELAY, OUTPUT);
  pinMode(soilMoisture,INPUT);
  pinMode(Relay2, OUTPUT);
  digitalWrite(Relay2, HIGH);

  digitalWrite(RELAY, HIGH); // Relay OFF (active LOW module usually)

}

void loop() {
  int soilData=analogRead(soilMoisture);
  // Ultrasonic trigger
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  duration = pulseIn(ECHO, HIGH);

  distance = duration * 0.034 / 2;

  waterLevel = 18 - distance;

  if (waterLevel < 0) waterLevel = 0;
  if (waterLevel > 18) waterLevel = 18;

  percentage = (waterLevel / 18) * 100;

  // Display
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  Serial.print("Water Level: ");
  Serial.print(waterLevel);
  Serial.println(" cm");

  Serial.print("Filled: ");
  Serial.print(percentage);
  Serial.println(" %");

  // Pump Control Logic
  if (percentage >= 75) {
    digitalWrite(RELAY, LOW);   
    Serial.println("Pump ON");
  } 
  else if (percentage < 65) {
    digitalWrite(RELAY, HIGH); 
    Serial.println("Pump OFF");
  }

  Serial.println("------------------");

  Serial.println(soilData);
  if(soilData>=700)
  {
    digitalWrite(Relay2, LOW);   
    Serial.println("Pump OFF");
  }
  else
  {
    digitalWrite(Relay2, HIGH);   
    Serial.println("Pump ON");
  }

}