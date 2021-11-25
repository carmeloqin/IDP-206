#ifndef CONTROLLERS_H
#define CONTROLLERS_H

#include "Arduino.h"
#include "variables.h"
#include "motors.h"
#include "sensors.h"
#include "helper.h"

namespace controller {
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

//        Serial.print(l_value.front_right);
//        Serial.print("\t");
//        Serial.print(l_value.front_left);
//        Serial.print("\t");
//        Serial.print(l_value.back_right);
//        Serial.print("\t");
//        Serial.println(l_value.back_left);
//        
//        bool leftw = isWhite(l_value.front_left); // Left is white
//        bool rightw = isWhite(l_value.front_right);
//        bool leftb = isBlack(l_value.front_left);
//        bool rightb = isBlack(l_value.front_right);
//        bool leftm = !leftw && !leftb;
//        bool rightm = !rightw && !rightb;
  
        int error = (l_value.front_right - l_value.front_left) - offset;
  
//        if (leftb && rightm) {
//          error = - (l_value.front_right + BLACK + THRESHOLD);
//        } else if (leftm && rightb) {
//          error = l_value.front_left + BLACK + THRESHOLD;
//        }
        return error;
      }
  
    public:
      void run(byte flag, bool isDone(), int repeat = 1,
               void done() = [](){},
               void error() = [](){Serial.println("Error! Vehicle is off the line!");}) {
        PID pid {};
        motors::runLeft(flag);
        motors::runRight(flag);
        last_at_junction = millis();
  
        for (int i = 0; i < repeat; i++) {
          while (!isDone()) {
            if (!isOnLineFront()) {
              motors::runLeft(RELEASE);
              motors::runRight(RELEASE);
              return error();
            }
  
            int turn = pid.next(getError());
  
            if (flag == BACKWARD) {
              turn *= (-1);
            }
            motors::setMotorsSpeed(turn, averagePower);
          }
          Serial.print("Junction Arrived: ");
          Serial.println(i+1);
        }
        
        motors::runLeft(RELEASE);
        motors::runRight(RELEASE);
        done();
      }
  };

  class SimpleController {
    public:
      void run(byte flag, bool isDone(), int repeat = 1,
               void done() = [](){},
               void error() = [](){Serial.println("Error! Vehicle is not moving!");}) {
        motors::runLeft(flag);
        motors::runRight(flag);
        motors::setMotorsSpeed(0, averagePower);

        for (int i = 0; i < repeat; i++) {
          while (!isDone()) {
            if (!isMoving()) {
              motors::runLeft(RELEASE);
              motors::runRight(RELEASE);
              return error();
            }
          }
        }
        
        motors::runLeft(RELEASE);
        motors::runRight(RELEASE);
        done();
      }
      
      void rotate(byte flag, bool isDone(), int repeat = 1,
                  void done() = [](){},
                  void error() = [](){Serial.println("Error! Vehicle is not rotating!");}) {
        switch (flag) {
          case CLOCKWISE:
            motors::runLeft(FORWARD);
            motors::runRight(BACKWARD);
            break;
          case ANTICLOCKWISE:
            motors::runLeft(BACKWARD);
            motors::runRight(FORWARD);
            break;
        }
        motors::setMotorsSpeed(0, averagePower); // turning = 0
  
        for (int i = 0; i < repeat; i++) {
          delay(1000);
          while (!isDone()) {
            if (!isRotating()) {
              motors::runLeft(RELEASE);
              motors::runRight(RELEASE);
              return error();
            }
            // could do some delay here
          } 
        }

        delay(50);
        motors::runLeft(RELEASE);
        motors::runRight(RELEASE);
        done();
      }
  };
}

controller::LineFollower line_follower = controller::LineFollower();
controller::SimpleController simple_controller = controller::SimpleController();

#endif
