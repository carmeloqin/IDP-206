#ifndef LineFollower_h
#define LineFollower_h

#include "Arduino.h"
#include "constants.h"

namespace linefollower 
{
  int tuningFactor = 100;
  int KP;
  int KI = 0;
  int KD = 0;
  int defaultDelay = 10;
  int offset = 0;
  int averagePower = 150;
  
  struct LightValue {
    int front_left;
    int front_right;
    int back_left;
    int back_right;
  } ;

  const int leftFrontPin = A0;
  const int rightFrontPin = A1;
//  const int leftBackPin = A0;
//  const int rightBackPin = A0;
  
  class AnalogOptoSwitch {
    public:
      int pin;
      AnalogOptoSwitch (int pin) {
        pin = pin;
        pinMode(pin, INPUT);
      }

      int readLight() {
        int _ = analogRead(pin);
        delay(2);

        int sum;
        int times = 10;
        for (int i = 0; i < times; i++) {
          sum += analogRead(pin);
        }
        return sum / times;
      }
  };

  AnalogOptoSwitch left_front_sensor = new AnalogOptoSwitch(leftFrontPin);
  AnalogOptoSwitch right_front_sensor = new AnalogOptoSwitch(rightFrontPin);

  class DigitalOptoSwitch {
    public:
      int pin;
      DigitalOptoSwitch (int pin) {
        pin = pin;
        pinMode(pin, INPUT);
      }

      bool readLight() {
        return digitalRead(pin);
      }
  };
  
  class PID {
    private:
      int last_error = 0;
      int integral = 0;
      int derivative = 0;
    
    public:
      int Kp;
      int Ki;
      int Kd;
      
      PID (int k_p, int k_i, int k_d) { 
        Kp = k_p;
        Ki = k_i;
        Kd = k_d;
      }
  
      int next(int error) {
        integral += error;
        derivative = error - last_error;
  
        int output = KP*error + KI*integral + KD*derivative;
        output /= tuningFactor; //  Use multiply factor of 100 to get finer tuning
  
        return output;
      }
  };

  bool onJunctionFront(LightValue l_value) {
    return false;
  }

  bool onJunctionBack(LightValue l_value) {
    return false;
  }

  LightValue readLightValues() {
    LightValue l_value;
    l_value.front_left = left_front_sensor.readLight();
    l_value.front_right = right_front_sensor.readLight();
    return l_value;
  }

  void _move(int junction=0, bool reverse=false) {
    PID pid {KP, KI, KD};
    for (int i = junction; i >= 0; i--) {
      while(true) {
        LightValue l_value = readLightValues();

        int error = (l_value.front_right - l_value.front_left) - offset;
        int turn = pid.next(error);

        if (reverse) {
          turn *= (-1);
        }

        constants::left_motor->setSpeed(averagePower + turn);
        constants::right_motor->setSpeed(averagePower - turn);

//      Check if a junction is passed
        if (reverse) {
          if (onJunctionBack(l_value)) {
            break;
          }
        } else {
          if (onJunctionFront(l_value)) {
            break;
          }
        }
        
        delay(defaultDelay);
      }
    }
  }

  void goForward(int junction = 0) {
    _move(junction, false);
  }

  void goBackward(int junction = 0) {
    _move(junction, true);
  }
}

#endif
