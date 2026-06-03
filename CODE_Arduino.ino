#include <Servo.h>

const int trigPin = 10;
const int echoPin = 11;
const int buzzerPin = 2;

long duration;
int distance;
Servo myServo;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
  myServo.attach(12);
}

void loop() {
  for (int i = 15; i <= 165; i++) {
    myServo.write(i);
    distance = calculateDistance();
    Serial.print(i);
    Serial.print(",");
    Serial.print(distance);
    Serial.print(".");

    if (distance < 20) {
      digitalWrite(buzzerPin, HIGH);
      delay(5);
      digitalWrite(buzzerPin, LOW);
      delay(150);  // ralenti quand obstacle
    } else {
      delay(30);   // vitesse normale
    }
  }

  for (int i = 165; i > 15; i--) {
    myServo.write(i);
    distance = calculateDistance();
    Serial.print(i);
    Serial.print(",");
    Serial.print(distance);
    Serial.print(".");

    if (distance < 20) {
      digitalWrite(buzzerPin, HIGH);
      delay(5);
      digitalWrite(buzzerPin, LOW);
      delay(150);  // ralenti quand obstacle
    } else {
      delay(30);   // vitesse normale
    }
  }
}

int calculateDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  return distance;
}
