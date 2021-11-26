#ifndef DUMMY_H
#define DUMMY_H

#include "sensors.h"

namespace dummy {
  int identifyDummy(int repeat = 3) {
    int sum;
    for (int i = 0; i < repeat; i++) {
      sum += sensors::getIRPhototransitorCounts(leftIRPhototransitorPin);// todo
    }
    
    int average = sum / repeat;
    if (average > 3000 && average < 4000) {
      return WHITE_DUMMY;
    } else if (average > 50 && average < 300) {
      return RED_DUMMY;
    } else if (average > 1400 && average < 2600) {
      return BLUE_DUMMY;
    } else {
      return NO_DUMMY;
    }
  }
}

#endif 
