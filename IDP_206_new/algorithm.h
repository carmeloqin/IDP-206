#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "Arduino.h"
#include "conditionals.h"
#include "controllers.h"
#include "indicator.h"
#include "servos.h"

namespace algo {
  unsigned long start;
  unsigned long timeout = 1700;
  struct {
      int junctions_arrived = 0;
    
      bool stop() {
        if (junctions_arrived < 1) {
          if (conditionals::isArrivingJunctionBack()) {
            junctions_arrived++;
            Serial.print("[algo finding_phase]Junction Arrived: ");
            Serial.println(junctions_arrived);
          }
          return false;
        }
        bool found = conditionals::isDummyFound();
//        Serial.print("Dummy Found: ");
//        Serial.println(found);
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
      Serial.println("[algo::dropOff]Dummy being dropped off"); //todo
      servos::dropOff();
      Serial.println("[algo::dropOff]Dummy dropped off"); //todo
      simple_controller.rotate(CLOCKWISE, conditionals::foundLineWhileRotateCW, 1);
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
    Serial.println("[algo::getLineDummy]Dummy Found"); //todo
    delay(2000);
    
    // TODO identify dummy here
    
    indicator::indicate(last_dummy_found);

    // Grab dummy
    Serial.println("[algo::getLineDummy]Dummy being grabbed"); //todo
    servos::pickUp();
    Serial.println("[algo::getLineDummy]Dummy grabbed"); //todo    
    
    dropOff(WHITE_DUMMY);  // WHITE TO TEST IT  

    
    
//    simple_controller.rotate(CLOCKWISE, conditionals::foundLineWhileRotateCW);
//    
//    line_follower.run(FORWARD, conditionals::isArrivingJunctionBack, 2);
  }
}


#endif 
