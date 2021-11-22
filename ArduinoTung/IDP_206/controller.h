#ifndef CONTROLLER_H
#define CONTROLLER_H

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
        
        bool leftw = isWhite(l_value.front_left); // Left is white
        bool rightw = isWhite(l_value.front_right);
        bool leftb = isBlack(l_value.front_left);
        bool rightb = isBlack(l_value.front_right);
        bool leftm = !leftw && !leftb;
        bool rightm = !rightw && !rightb;
  
        int error = (l_value.front_right - l_value.front_left) - offset;
  
        if (leftb && rightm) {
          error = - (l_value.front_right + BLACK + THRESHOLD);
        } else if (leftm && rightb) {
          error = l_value.front_left + BLACK + THRESHOLD;
        }
  
        return error;
      }
  
    public:
      void run(byte flag, bool isDone (), int repeat = 1,
               void errorCallback () = doNothing) {
        PID pid {};
        motors::runLeft(FORWARD);
        motors::runRight(FORWARD);
  
        for (int i = 0; i < repeat; i++) {
          while (!isDone()) {
            if (!isOnLine()) {
              motors::runLeft(RELEASE);
              motors::runRight(RELEASE);
              return errorCallback();
            }
  
            int turn = pid.next(getError());
  
            if (flag == BACKWARD) {
              turn *= (-1);
            }
            motors::setMotorsSpeed(turn);
          }
        }
        motors::runLeft(RELEASE);
        motors::runRight(RELEASE);
      }
  
      void turn(byte flag, bool isDone (), int repeat = 1,
                void errorCallback () = doNothing) {
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
  
        for (int i = 0; i < repeat; i++) {
          while (!isDone()) {
            if (!isTurning()) {
              motors::runLeft(RELEASE);
              motors::runRight(RELEASE);
              return errorCallback();
            }
            // could do some delay here
          } 
        }
        
        motors::runLeft(RELEASE);
        motors::runRight(RELEASE);
      }
  };
}

controller::LineFollower line_follower = controller::LineFollower();

#endif
