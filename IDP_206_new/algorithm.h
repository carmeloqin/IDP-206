#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "Arduino.h"
#include "conditionals.h"
#include "controllers.h"
#include "indicator.h"
#include "servos.h"

namespace algo {
  unsigned long start;
  unsigned long timeout = 2000;
  struct {
      int junctions_arrived = 0;
    
      bool stop() {
        if (junctions_arrived < 2) {
          if (conditionals::isArrivingJunctionBack()) {
            junctions_arrived++;
            Serial.println(junctions_arrived);
          }
          return false;
        }
        bool found = conditionals::isDummyFound();
        Serial.println(found);
        return found;
      }
    } finding_phase;
  
  struct {
    int junction_arrived = false;
    unsigned long start = 0;
    bool stop() {
      if (!junction_arrived) {
        return conditionals::isLeavingJunctionFront();
      }
  
      if (start == 0) {
        start = millis();
      }
  
      return millis() - start > 500; // go more for 500ms
    }
  } dropping_phase;
  
  void findDummy() {
    line_follower.run(FORWARD, [](){return finding_phase.stop();});
  }
   
  void dropOff(byte flag) {
    //
    line_follower.run(FORWARD, conditionals::isArrivingJunctionFront);
    if (flag == WHITE_DUMMY) {
      start = millis();
      simple_controller.run(FORWARD, [start](){return millis() - start > 250;});
      servos::dropOff();
      simple_controller.rotate(CLOCKWISE, conditionals::foundLineWhileRotateCW, 2);
    } else {
      start = millis();
      simple_controller.run(BACKWARD, [start](){return millis() - start > 250;});
      Serial.println("1");
      simple_controller.rotate(CLOCKWISE, conditionals::foundLineWhileRotateCW);
      Serial.println("2");
      line_follower.run(FORWARD, conditionals::isArrivingJunctionBack);
      Serial.println("3");


      start = millis();
      switch(flag) {
        case RED_DUMMY:
          simple_controller.rotate(CLOCKWISE, [start, timeout](){return millis() - start > timeout;});
      Serial.println("4");

          servos::dropOff();
          simple_controller.rotate(CLOCKWISE, conditionals::foundLineWhileRotateCW, 2);
          break;
        case BLUE_DUMMY:
          simple_controller.rotate(ANTICLOCKWISE, [start, timeout](){return millis() - start > timeout;});
          servos::dropOff();
          simple_controller.rotate(ANTICLOCKWISE, conditionals::foundLineWhileRotateACW, 2);
          break;
      }
    }
  }

  void getLineDummy() {
    findDummy(); // Going forward until it finds a dummy

    // identify dummy here
    indicator::indicate(last_dummy_found);

    servos::pickUp();
    
    // Grab dummy here
    dropOff(WHITE_DUMMY);    
    
//    simple_controller.rotate(CLOCKWISE, conditionals::foundLineWhileRotateCW);
//    
//    line_follower.run(FORWARD, conditionals::isArrivingJunctionBack, 2);
  }
}


#endif 
