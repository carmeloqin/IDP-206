#define TIMEOUT_MILLIS 100000000000
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield();

Adafruit_DCMotor *leftMotor = AFMS.getMotor(3);  //left motor on port 1
Adafruit_DCMotor *rightMotor = AFMS.getMotor(4); //right motor on port 2

//Sensor Connection - changed temp. because behind wheel
const int left_sensor_pin = A1;
const int right_sensor_pin = A0;

int sensor_state_left;
int sensor_state_right;

int IR_high = 150;
 
void setup()
{
    Serial.begin(9600);
    AFMS.begin();
    // Set the speed to start, from 0 (off) to 255 (max speed)
    leftMotor->setSpeed(0);
    leftMotor->run(FORWARD);
    // turn on motor
    leftMotor->run(RELEASE);

    rightMotor->setSpeed(0);
    rightMotor->run(FORWARD);
    rightMotor->run(RELEASE);
}

void run_motor(int LEFT, int RIGHT)
{
    // In software video and powerpoint, http://www-h.eng.cam.ac.uk/help/tpl/IDP/softwaretalk.html
    // IT says to compare motor speed with previous, and if its the same, don't update the motors.
    // TODO
    
    leftMotor->setSpeed(LEFT);
    leftMotor->run(BACKWARD);
    rightMotor->setSpeed(RIGHT);
    rightMotor->run(BACKWARD);
    delay(10);
}

inline void line_follow_basic()
{
    // Blindly follows the line until some time limit is reached.
    unsigned long start_time = millis();

    //while (millis() - start_time < TIMEOUT_MILLIS)
    while (1)
    {

        // assumes for the moment that the sensors are ahead of the wheels.
        sensor_state_left = analogRead(left_sensor_pin);
        sensor_state_right = analogRead(right_sensor_pin);
        int touchline;
        if (sensor_state_left > IR_high && sensor_state_right < IR_high)
        {
            run_motor(0, 255);
            Serial.println(1);
        }
        else if (sensor_state_left < IR_high && sensor_state_right > IR_high)
        {
            run_motor(255, 0);
            Serial.println(0);
        }
        else
        {
            run_motor(255,255);
            Serial.println(10);
        }
    }
}

void loop()
{
    uint8_t i;

    line_follow_basic();
}
