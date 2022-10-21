#include <Servo.h>

int motor = 30;
int motor2 = 31;

const int trigPin = 9;
const int echoPin = 10;

Servo neck;

void setup() {
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    pinMode(motor, OUTPUT);
    Serial.begin(9600);
    neck.attach(8);
}

void loop() {
    int speed = 150;




    if (getDistance() >= 5) {
        analogWrite(motor, speed);
        analogWrite(motor2, speed);
    } else {
        neck.write(270);
        if (getDistance() > 5) {
            // turn left
        } else {
            neck.write(90);
            if (getDistance() > 5) {
                //turn right
            } else {
                //turn around
            }
        }
    }

}

float getDistance() {
    float duration, distance;
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = (duration * .0343) / 2;
    delay(100);
    return distance;
}

/* turn neck to the left if less than 5 cm turn left then go forward. 
if not turn neck to the right if less than 5 turn right then go forward
else turn around then go forward. */ 
