// Libraries (servo and Ultrasonic Sensor)
#include <Servo.h>
#include "SR04.h"

// Initialize servo, servo position, pin and interval time (between servo movements) as well as servo state (direction)
enum DIRECTION { UP, DOWN, STOP};
Servo myservo;
int position = 0;
#define SERVO_PIN 12
int servoIntervalTime = 60;
int servoStartStateTime;
DIRECTION servoDirection = UP;
DIRECTION servoDirectionBeforeStop;

// Initialize sensor instance, sensor pins and distance variable
#define TRIG_PIN 9
#define ECHO_PIN 10
SR04 sr04 = SR04(ECHO_PIN,TRIG_PIN);
int sensorIntervalTime = 800;
int sensorStartStateTime;
long currentDistance;

// Initialize RGB pins
#define RED_PIN 4
#define GREEN_PIN 3

void setup() {
  // Initialize pins and RGB color as green
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  digitalWrite(GREEN_PIN, HIGH);
  digitalWrite(RED_PIN, LOW);
  myservo.attach(SERVO_PIN);

  // Start timer for both intervals
  servoStartStateTime = sensorStartStateTime = millis();
  Serial.begin(9600);
}

void loop() {
  unsigned long currentTime = millis();
  unsigned long servoElapsed = currentTime - servoStartStateTime;
  unsigned long sensorElapsed = currentTime - sensorStartStateTime;

  // When it's time for the servo to make a move
  if(servoElapsed >= servoIntervalTime) {
    // Case 1, we are moving "up": if not at the limit, we move up by 1 position, else we change direction
    if(servoDirection == UP){
      if(position < 180)
        position++;
      else {
        servoDirection = DOWN;
        position--;
      }
      myservo.write(position);
      servoStartStateTime = currentTime;
    }

    // Case 2, we are moving "down": if not at the limit, we move down by 1 position, else we change direction
    if(servoDirection == DOWN){
      if(position > 0)
        position--;
      else {
        servoDirection = UP;
        position++;
      }
      myservo.write(position);
      servoStartStateTime = currentTime;
    }
  }

  // If it's time to read and display a distance from the sensor
  if(sensorElapsed >= sensorIntervalTime) {
    currentDistance = sr04.Distance();

    // If the distance we read is small (object is close), servo stops, RGB becomes red
    if(currentDistance <= 10) {
      servoDirectionBeforeStop = servoDirection;
      servoDirection = STOP;
      digitalWrite(RED_PIN, HIGH);
      digitalWrite(GREEN_PIN, LOW);
    }

    // When the object is no longer too close, servo picks back up, RGB goes green once more
    if(servoDirection == STOP && currentDistance > 10) {
      servoDirection = servoDirectionBeforeStop;
      digitalWrite(RED_PIN, LOW);
      digitalWrite(GREEN_PIN, HIGH);
      servoStartStateTime = currentTime;
    }

    Serial.print(currentDistance);
    Serial.println("cm");
    sensorStartStateTime = currentTime;
  }
}
