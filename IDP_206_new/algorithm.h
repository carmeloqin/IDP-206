#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "Arduino.h"
#include "conditionals.h"
#include "controllers.h"
#include "indicator.h"

struct A {
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
  } phase_1;

bool phase_1_stop() {
  return phase_1.stop();
}

namespace algo {
   // Find the dummy phase

  void getFirstDummy() {
    line_follower.run(FORWARD, phase_1_stop);

    indicator::indicate(last_dummy_found);
    delay(1000);
    indicator::indicate(NO_DUMMY);
    last_dummy_found = NO_DUMMY;
    
    simple_controller.rotate(CLOCKWISE, conditionals::isGettingOnLineFront);
    
    line_follower.run(FORWARD, conditionals::isArrivingJunctionBack, 2);
  }
}


#endif 