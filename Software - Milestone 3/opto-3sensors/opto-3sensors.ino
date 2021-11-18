#define TIMEOUT_MILLIS 100000000000
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield();

Adafruit_DCMotor *leftMotor = AFMS.getMotor(3);  //left motor on port 1
Adafruit_DCMotor *rightMotor = AFMS.getMotor(4); //right motor on port 2

//Sensor Connection - changed temp. because behind wheel
const int left_sensor_pin = A0;
const int right_sensor_pin = A2;
const int mid_sensor_pin = A1;

int sensor_state_left;
int sensor_state_right;
int sensor_state_mid;

int IR_high = 500;
int IR_highm = 500;
 
void setup()
{
    Serial.begin(9600);
    AFMS.begin();
    // Set the speed to start, from 0 (off) to 255 (max speed)
    leftMotor->setSpeed(0);
    leftMotor->run(BACKWARD);
    // turn on motor
    leftMotor->run(RELEASE);

    rightMotor->setSpeed(0);
    rightMotor->run(BACKWARD);
    rightMotor->run(RELEASE);
}

bool left_sensor()
{
    sensor_state_left = analogRead(left_sensor_pin);
    if (sensor_state_left > IR_high)
    {
      return 1;
    }
    else
    {
      return 0;
    }
}

bool right_sensor()
{
    sensor_state_right = analogRead(right_sensor_pin);
    if (sensor_state_right > IR_high)
    {
      return 1;
    }
    else
    {
      return 0;
    }
}


bool mid_sensor()
{
    sensor_state_mid = analogRead(mid_sensor_pin);
    if (sensor_state_mid > IR_highm)
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
    leftMotor->run(FORWARD);
    rightMotor->setSpeed(RIGHT);
    rightMotor->run(FORWARD);
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
        int rightbool = right_sensor();
        int leftbool = left_sensor();
        int midbool = mid_sensor();

        int command[3] = {leftbool, midbool, rightbool};
        
        if (command[0] && command[1] && not command[2])
        {
            run_motor(100, 150);
            Serial.println("110");
        }
        else if (command[0] && not command[1] && not command[2])
        {
            run_motor(100,150);
            Serial.println("100");
        }
        else if (not command[0] && command[1] && command[2])
        {
            run_motor(150, 100);
            Serial.println("011");
        }
        else if (not command[0] && command[1] && not command[2])
        {
            run_motor(255,255);
            Serial.println("010");
        }
        else if (not command[0] && not command[1] && command[2])
        {
            run_motor(150,100);
            Serial.println("001");
        }
        else
        {
            run_motor(255,255);
            Serial.println("000");
        }
    }
}

void loop()
{
    uint8_t i;

    line_follow_basic();
}
