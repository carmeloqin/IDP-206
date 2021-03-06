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

int sensor_state;

int IR_high = 100;
 
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

bool line_white(char sensor)
{
    // if the reading of the left sensor is above a certain value, we assume that it is on the white line
    // if the reading of the right sensor is above a certain value, we assume that it is on the white line
    if (sensor = 'L')
    {
        sensor_state = analogRead(left_sensor_pin);
        //Serial.println("Left");
        //Serial.println(sensor_state);
    }
    else if (sensor = 'R')
    {
        sensor_state = analogRead(right_sensor_pin);
        //Serial.println("Right");
        //Serial.println(sensor_state);
    }
    else
    {
        Serial.println('sensor not defined');
    }

    if (sensor_state > IR_high)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void run_motor(int LEFT, int RIGHT)
{
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

        int left = line_white('L');
        Serial.print("Left: ");
        Serial.println(left);
        int right = line_white('R');
        Serial.print("Right: ");
        Serial.println(right);
        
        if (left && not right)
        {
            run_motor(0, 255);
        }
        else if (right && not left)
        {
            run_motor(255, 0);
        }
        else
        {
            run_motor(255,255);
        }
    }
}

void loop()
{
    uint8_t i;

    line_follow_basic();
}
