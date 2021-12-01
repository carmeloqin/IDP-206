#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "Arduino.h"
#include "conditionals.h"
#include "controllers.h"
#include "indicator.h"
#include "servos.h"

namespace algo {
  unsigned long start;
  
  void toWhite() {
    line_follower.run(FORWARD, conditionals::isArrivingJunctionFront);
  }

  void toRedBlueJunction() {
    line_follower.run(FORWARD, conditionals::isArrivingJunctionFront);
    
    start = millis();
    simple_controller.run(BACKWARD, [start](){return millis() - start > 250;});
    
    simple_controller.rotate(CLOCKWISE, conditionals::foundLineWhileRotateCW);
    
    line_follower.run(FORWARD, conditionals::isArrivingJunctionBack);
  }

  void toRed() {
    toRedBlueJunction();

    start = millis();
    simple_controller.rotate(CLOCKWISE, [start](){return millis() - start > 750;});
  }

  void toBlue() {
    toRedBlueJunction();

    start = millis();
    simple_controller.rotate(ANTICLOCKWISE, [start](){return millis() - start > 750;});
  }

  void toSearchFromWhite() {
    start = millis();
    simple_controller.run(BACKWARD, [start](){return millis() - start > 250;});

    simple_controller.rotate(CLOCKWISE, conditionals::foundLineWhileRotateCW);

    start = millis();
    simple_controller.run(FORWARD, [start](){return millis() - start > 2000;});

    simple_controller.rotate(CLOCKWISE, conditionals::foundLineWhileRotateCW);
  }

  void toSearchFromRed() {
    simple_controller.rotate(CLOCKWISE, conditionals::foundLineWhileRotateCW, 2);
  }

  void toSearchFromBlue() {
    simple_controller.rotate(ANTICLOCKWISE, conditionals::foundLineWhileRotateACW, 2);
  }

  void toBaseFromWhite() {
    start = millis();
    simple_controller.run(BACKWARD, [start](){return millis() - start > 250;});

    simple_controller.rotate(CLOCKWISE, conditionals::foundLineWhileRotateCW);

    line_follower.run(FORWARD, conditionals::isArrivingJunctionBack, 2, [](){delay(500);}); // go further into the box for 500ms
  }
  
  void toBaseFromRedBlueJunction() {
    struct {
      bool arrived = false;
  
      bool isTrue() {
        if(!arrived) {
          arrived = conditionals::isArrivingJunctionFront();
          return false;
        }
        return conditionals::isArrivingJunctionBack();
      }
    } stopping_condition;
  
    line_follower.run(FORWARD, [stopping_condition](){return stopping_condition.isTrue();}, 1, [](){delay(500);}); // go further into the box for 500ms
  }
  
  void toBaseFromRed() {
    simple_controller.rotate(ANTICLOCKWISE, conditionals::foundLineWhileRotateACW, 2);
    toBaseFromRedBlueJunction();
  }

  void toBaseFromBlue() {
    simple_controller.rotate(CLOCKWISE, conditionals::foundLineWhileRotateCW, 2);
    toBaseFromRedBlueJunction();
  }

  void dropOff(byte dummy, bool returnToBaseAfterwards = false) {
    switch (dummy) {
      case NO_DUMMY:
      case WHITE_DUMMY:
        toWhite();
        break;
      case RED_DUMMY:
        toRed();
        break;
      case BLUE_DUMMY:
        toBlue();
        break;
    }

    servos::dropOff();

    if (!returnToBaseAfterwards) {
      switch (dummy) {
        case NO_DUMMY:
        case WHITE_DUMMY:
          toSearchFromWhite();
          break;
        case RED_DUMMY:
          toSearchFromRed();
          break;
        case BLUE_DUMMY:
          toSearchFromBlue();
          break;
      }
    } else {
      switch (dummy) {
        case NO_DUMMY:
        case WHITE_DUMMY:
          toBaseFromWhite();
          break;
        case RED_DUMMY:
          toBaseFromRed();
          break;
        case BLUE_DUMMY:
          toBaseFromBlue();
          break;
      }
    }
  }

  void goSlow() {
    // go slow to identify the dummy
    line_follower.run(FORWARD, conditionals::isDummyDetected, 1, [](){}, 70);
  }

  void rescueLineDummy() {
    // passing 2 junctions then stop when a dummy is found
    struct {
      int junctions_arrived = 0;
    
      bool isTrue() {
        if (junctions_arrived < 2) {
          if (conditionals::isArrivingJunctionBack()) {
            junctions_arrived++;
          }
          return false;
        }
        return conditionals::isDummyFound();
      }
    } stopping_condition;
    line_follower.run(FORWARD, [stopping_condition](){return stopping_condition.isTrue();});

    // identify the dummy
    goSlow();
    indicator::indicate(last_dummy_found);

    // grab the dummy
    servos::pickUp();
    delay(5000);

    dropOff(last_dummy_found, true); // true means return to base afterwards. false means search area.
    
    last_dummy_found = NO_DUMMY;
    indicator::indicate(last_dummy_found);
  }
}
#endif 
