#include "servos.h"

void dropOff (byte flag) { //For the line one for now
    
  
  switch(flag) {
    case WHITE_DUMMY:
      // go forward until white junction
      //line_follower.run(FORWARD, [until junction]);

      // go forward for 500ms or sth
      //line_follower.run(FORWARD, [for 500ms]);

      // drop dummy off
      servos::descendLifter();
      servos::openGrabber();
      servos::ascendLifter();
      
      // go backwards until front sensors touch the white line
      // line_follower.run(BACKWARDS, [until junction]);
      
      
      break;
    case RED_DUMMY:

      // Turn 180 degrees
      simple_controller.rotate(CLOCKWISE, conditionals::isGettingOnLineFront);

      // Go forward until cross junction
      //line_follower.run(FORWARD, [until junction]);
      
      // turn right 90 degrees, maybe use the back sensors?
      simple_controller.rotate(CLOCKWISE, conditionals::isGettingOnLineFront);
      simple_controller.rotate(CLOCKWISE, [a little bit more]);
      // or maybe time the time to turn 90 degrees
      // or use IMU if possible

      // go forward for 500ms or sth
      //line_follower.run(FORWARD, [for 500ms]);

      // drop dummy off
      servos::descendLifter();
      servos::openGrabber();
      servos::ascendLifter();
      
      // go backwards until front sensors touch the white line
      // line_follower.run(BACKWARDS, [until junction]);

      // turn right 90 degrees 
      simple_controller.rotate(CLOCKWISE, conditionals::isGettingOnLineFront);
      // this doesn't work cuz it doesn't turn 90 degrees
      
      break;
    case BLUE_DUMMY:
      //hi
      break;
    case NO_DUMMY:
      // Repeat sensing
      break;
}
