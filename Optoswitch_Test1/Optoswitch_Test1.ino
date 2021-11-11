#define TIMEOUT_MILLIS 100000000000
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield();

Adafruit_DCMotor *leftMotor = AFMS.getMotor(4);  //left motor on port 1
Adafruit_DCMotor *rightMotor = AFMS.getMotor(3); //right motor on port 2

//Sensor Connection - changed temp. because behind wheel
const int left_sensor_pin = A1;
const int right_sensor_pin = A0;
//const int midfront_sensor_pin = A2;
//const int midrear_sensor_pin = A3;

int sensor_state;
int cross_accum;
int n;
int sensor2;
int sensor0;

int IR_high1 = 200;
int IR_high0 = 450;
 
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
        //Serial.println(sensor_state);
            if (sensor_state > IR_high1)
            {

              return 1;
            }
            else
            {
              return 0;
            }
    }
    else if (sensor = 'R')
    {
        sensor_state = analogRead(right_sensor_pin);
        //Serial.println(sensor_state);
            if (sensor_state > IR_high0)
            {
              return 1;
            }
            else
            {
              return 0;
            }
    }
    else
    {
        //Serial.println('sensor not defined');
    }

}

int cross_times()
{
  sensor2 = analogRead(right_sensor_pin);
  sensor0 = analogRead(left_sensor_pin);
  if (sensor2 > IR_high0 && sensor0 > IR_high1)
  {
    cross_accum = cross_accum +1;
  }
  return cross_accum;
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
    Serial.println(right_sensor_pin);
    Serial.println(left_sensor_pin);
    //while (millis() - start_time < TIMEOUT_MILLIS)
    while (1)
    {

        // assumes for the moment that the sensors are ahead of the wheels.
        if (line_white('R'))
        {
            run_motor(0, 255);
        }
        else
        {
            run_motor(255, 0);
        }
    }
}

void loop()
{
    uint8_t i;

    line_follow_basic();

    n = cross_times();

    if (n=2)
    {
      run_motor(0,0);
      cross_accum = 0;
    }

    
}
