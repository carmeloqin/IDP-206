#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "conditionals.h"
#include "controllers.h"
#include "indicator.h"

namespace algo {
  struct {
    int junctions_arrived = 0;
  
    bool stop() {
      if (junctions_arrived < 2) {
        if (conditionals::isArrivingJunctionBack()) {
          junctions_arrived++;
        }
        return false;
      }
  
      return conditionals::isDummyFound();
    }
  } phase_1; // Find the dummy phase

  void getFirstDummy() {
    line_follower.run(FORWARD, [phase_1](){return phase_1.stop();});

    indicator::indicate(last_dummy_found);
    delay(1000);
    indicator::indicate(NO_DUMMY);
    
    simple_controller.rotate(CLOCKWISE, conditionals::isGettingOnLineFront);
    
    line_follower.run(FORWARD, conditionals::isArrivingJunctionBack, 2);
  }
}


#endif 
