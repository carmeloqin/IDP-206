#ifndef CONTROLLERS_H
#define CONTROLLERS_H

#include "Arduino.h"
#include "variables.h"
#include "motors.h"
#include "sensors.h"
#include "conditionals.h"

namespace controllers {

  class PID {
    private:
      int last_error = 0;
      int integral = 0;
      int derivative = 0;
  
    public:
      int Kp;
      int Ki;
      int Kd;
  
      PID (int k_p = KP, int k_i = KI, int k_d = KD) {
        Kp = k_p;
        Ki = k_i;
        Kd = k_d;
      }
  
      int next(int error) {
        integral += error;
        derivative = error - last_error;
  
        int output = Kp * error + Ki * integral + Kd * derivative;
        output /= tuningFactor; //  Use multiply factor of 100 to get finer tuning
  
        return output;
      }
  
      void reset() {
        last_error = 0;
        integral = 0;
        derivative = 0;
      }
  };
  
  class LineFollower {
    private:
      int getError() {
        LightValues l_value = sensors::getLightValues();
        return (l_value.front_right - l_value.front_left) - offset;
      }
  
    public:
      template<typename Function>
      void run(byte flag, Function&& isDone, int repeat = 1,
               void done() = [](){},
               int power = averagePower,
               void error() = [](){Serial.println("[controllers]Error! Vehicle is off the line!");}) {
        PID pid {};
        motors::runLeft(flag);
        motors::runRight(flag);
        delay(250); //todo remove
        for (int i = 0; i < repeat; i++) {
          while (!isDone()) {
            if (!conditionals::isOnLineFront()) {
              motors::runLeft(RELEASE);
              motors::runRight(RELEASE);
              return error();
            }
  
            int turn = pid.next(getError());
  
            if (flag == BACKWARD) {
              turn *= (-1);
            }
            motors::setMotorsSpeed(turn, power);
            
            delay(50);
          }
        }

        done();
        motors::runLeft(RELEASE);
        motors::runRight(RELEASE);
      }
  };

  class SimpleController {
    public:
      template<typename Function>
      void run(byte flag, Function&& isDone, int repeat = 1,
               void done() = [](){},
               int power = averagePower,
               void error() = [](){Serial.println("[controllers]Error! Vehicle is not moving!");}) {
        motors::runLeft(flag);
        motors::runRight(flag);
        motors::setMotorsSpeed(0, power);

        for (int i = 0; i < repeat; i++) {
          while (!isDone()) {
            if (!conditionals::isMoving()) {
              motors::runLeft(RELEASE);
              motors::runRight(RELEASE);
              return error();
            }
            delay(50);
          }
        }
        
        motors::runLeft(RELEASE);
        motors::runRight(RELEASE);
        done();
      }
      
      void rotate(byte flag, bool isDone(), int repeat = 1,
                  void done() = [](){},
                  int power = averagePower,
                  void error() = [](){Serial.println("Error! Vehicle is not rotating!");}) {
        switch (flag) {
          case CLOCKWISE:
            motors::runLeft(BACKWARD);
            motors::runRight(FORWARD);
            break;
          case ANTICLOCKWISE:
            motors::runLeft(FORWARD);
            motors::runRight(BACKWARD);
            break;
        }
        motors::setMotorsSpeed(0, power); // turning = 0

        delay(rotateDelay); // TOCHANGE
        for (int i = 0; i < repeat; i++) {
          while (!isDone()) {
            if (!conditionals::isRotating()) {
              motors::runLeft(RELEASE);
              motors::runRight(RELEASE);
              return error();
            }
            delay(50);
          } 
        }

//        delay(50); // To get back to the centre of the line; //don't need it now
        motors::runLeft(RELEASE);
        motors::runRight(RELEASE);
        done();
      }
  };
}

controllers::LineFollower line_follower = controllers::LineFollower();
controllers::SimpleController simple_controller = controllers::SimpleController();

#endif
