#pragma region VEXcode Generated Robot Configuration
// Make sure all required headers are included.
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>




#include "vex.h"


using namespace vex;


// Brain should be defined by default
brain Brain;




// START V5 MACROS
#define waitUntil(condition)                                                   \
 do {                                                                         \
   wait(5, msec);                                                             \
 } while (!(condition))


#define repeat(iterations)                                                     \
 for (int iterator = 0; iterator < iterations; iterator++)
// END V5 MACROS




// Robot configuration code.
motor LeftMotor = motor(PORT1, ratio18_1, false);


motor RightMotor = motor(PORT10, ratio18_1, true);


motor ClawMotor = motor(PORT3, ratio18_1, false);


motor ArmMotor = motor(PORT8, ratio18_1, false);


controller Controller1 = controller(primary);
motor Motor14 = motor(PORT14, ratio18_1, false);


motor Motor18 = motor(PORT18, ratio18_1, false);


motor Motor2 = motor(PORT2, ratio18_1, true);








// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;
// define variables used for controlling motors based on controller inputs
bool Controller1LeftShoulderControlMotorsStopped = true;
bool Controller1RightShoulderControlMotorsStopped = true;
bool Controller1XBButtonsControlMotorsStopped = true;


// define a task that will handle monitoring inputs from Controller1
int rc_auto_loop_function_Controller1() {
 // process the controller input every 20 milliseconds
 // update the motors based on the input values
 while(true) {
   if(RemoteControlCodeEnabled) {
     // check the ButtonL1/ButtonL2 status to control ClawMotor
     if (Controller1.ButtonL1.pressing()) {
       ClawMotor.spin(forward);
       Controller1LeftShoulderControlMotorsStopped = false;
     } else if (Controller1.ButtonL2.pressing()) {
       ClawMotor.spin(reverse);
       Controller1LeftShoulderControlMotorsStopped = false;
     } else if (!Controller1LeftShoulderControlMotorsStopped) {
       ClawMotor.stop();
       ClawMotor.setStopping(hold);
       // set the toggle so that we don't constantly tell the motor to stop when the buttons are released
       Controller1LeftShoulderControlMotorsStopped = true;
     }
     // check the ButtonR1/ButtonR2 status to control ArmMotor
     if (Controller1.ButtonR1.pressing()) {
       ArmMotor.spin(forward);
       Motor2.spin(forward);
       Controller1RightShoulderControlMotorsStopped = false;
     } else if (Controller1.ButtonR2.pressing()) {
       ArmMotor.spin(reverse);
       Motor2.spin(reverse);
       Controller1RightShoulderControlMotorsStopped = false;
     } else if (!Controller1RightShoulderControlMotorsStopped) {
       ArmMotor.stop();
       Motor2.stop();
       ArmMotor.setStopping(hold);
       Motor2.setStopping(hold);
       // set the toggle so that we don't constantly tell the motor to stop when the buttons are released
       Controller1RightShoulderControlMotorsStopped = true;
     }
     // check the ButtonX/ButtonB status to control Motor14
     if (Controller1.ButtonX.pressing()) {
       Motor14.spin(forward);
       Controller1XBButtonsControlMotorsStopped = false;
     } else if (Controller1.ButtonB.pressing()) {
       Motor14.spin(reverse);
       Controller1XBButtonsControlMotorsStopped = false;
     } else if (!Controller1XBButtonsControlMotorsStopped) {
       Motor14.stop();
       Motor14.setStopping(hold);
       // set the toggle so that we don't constantly tell the motor to stop when the buttons are released
       Controller1XBButtonsControlMotorsStopped = true;
     }
   }
   // wait before repeating the process
   wait(20, msec);
 }
 return 0;
}


task rc_auto_loop_task_Controller1(rc_auto_loop_function_Controller1);
#pragma endregion VEXcode Generated Robot Configuration




// ----------------------------------------------------------------------------
//                                                                          
//  Project:        Left Arcade Control
//  Description:    This example will use the left X/Y Controller
//                  axis to control the Clawbot.
//  Configuration:  V5 Clawbot (Individual Motors)
//                  Controller
//                  Claw Motor in Port 3
//                  Arm Motor in Port 8
//                  Left Motor in Port 1
//                  Right Motor in Port 10  
//                                                                          
// ----------------------------------------------------------------------------




#include "vex.h"




using namespace vex;




int main() {
// Begin project code
// Main Controller loop to set motors to controller axis positions
double speed = .5;
bool upPressed = false;
bool downPressed = false;
while(true){
  if(Controller1.ButtonUp.pressing()){
    if(upPressed == false){
      if(speed < 1){
        speed += .1;
      }
      upPressed = true;
    }
  } else {
    upPressed = false;
  }




  if(Controller1.ButtonDown.pressing()){
    if(downPressed == false){
      if(speed > .1){
        speed -= .1;
      }
      downPressed = true;
    }
  } else {
    downPressed = false;
  }




   LeftMotor.setVelocity((int)((Controller1.Axis3.position() + Controller1.Axis4.position()) * speed), percent);
  RightMotor.setVelocity((int)((Controller1.Axis3.position() - Controller1.Axis4.position()) * speed), percent);
  Motor18.setVelocity((int)(Controller1.Axis1.position() * speed), percent);
  LeftMotor.spin(forward);
  RightMotor.spin(forward);
  Motor18.spin(forward);
  wait(5, msec);
}
}
