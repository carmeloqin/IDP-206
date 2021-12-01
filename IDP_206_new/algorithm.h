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
    simple_controller.rotate(CLOCKWISE, [start](){return millis() - start > 2200;});
  }

  void toBlue() {
    toRedBlueJunction();

    start = millis();
    simple_controller.rotate(ANTICLOCKWISE, [start](){return millis() - start > 2200;});
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
  
  void toBaseFromRed() {
    simple_controller.rotate(ANTICLOCKWISE, conditionals::foundLineWhileRotateACW, 1);

    line_follower.run(FORWARD, conditionals::isArrivingJunctionFront);
    line_follower.run(FORWARD, conditionals::isArrivingJunctionBack, 1, [](){delay(500);}); // go further into the box for 500ms
  }

  void toBaseFromBlue() {
    simple_controller.rotate(CLOCKWISE, conditionals::foundLineWhileRotateCW, 2);

    line_follower.run(FORWARD, conditionals::isArrivingJunctionFront);
    line_follower.run(FORWARD, conditionals::isArrivingJunctionBack, 1, [](){delay(500);}); // go further into the box for 500ms
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
    line_follower.run(FORWARD, conditionals::isDummyDetected, 1, [](){}, 100);

//    line_follower.run(FORWARD, conditionals::isDummyFound2, 1, [](){}, 100);
  }

  

  void rescueLineDummy() {
//    line_follower.run(FORWARD, conditionals::isArrivingJunctionBack, 2);

    Serial.println("1");

    line_follower.run(FORWARD, conditionals::isDummyFound);
    delay(1000);

//    line_follower.run(FORWARD, conditionals::isDummyInRange) ;


    // identify the dummy
    goSlow();
//    last_dummy_found = WHITE_DUMMY;
    indicator::indicate(last_dummy_found);

    // grab the dummy
    servos::pickUp();
    //delay(5000);

    dropOff(last_dummy_found, true); // true means return to base afterwards. false means search area.
    
    last_dummy_found = NO_DUMMY;
    indicator::indicate(last_dummy_found);
  }
  
  /*
  void rescueSideDummy1() {

    /*
    1: Approaching side dummy
    Go to white dummy junction
    Go back a little bit
    Turn left 60 degrees (Anticlockwise)
    Scan for 60 degrees with distance sensor, look for objects with less than maybe 80cm
    Approach side dummy slowly
    If signal lost: go to next section
     

    int sixtyDegreesTime = 500; //to change
     
    //NUMBER 1
    //Turn 180 degrees
    simple_controller.rotate(CLOCKWISE, conditionals::foundLineWhileRotateCW, 2);
    //Go to white junction
    line_follower.run(FORWARD, conditionals::isArrivingJunctionFront, 2);
    //Go back a little bit
    simple_controller.run(BACKWARD, [start](){return millis() - start > 500;});
    //Turn left 60 degrees (anticlockwise)
    simple_controller.rotate(ANTICLOCKWISE, [start](){return millis() - start > sixtyDegreesTime;});
    //Scan for 60 degrees with distance sensor, look for objects with less than maybe 80cm
    //Record the time for first large differentiation change
    //Turn back with half the time
    simple_controller.rotate(ANTICLOCKWISE, [start](){return millis() - start > sixtyDegreesTime;});
    
    
  }
  */
  
}
#endif 
