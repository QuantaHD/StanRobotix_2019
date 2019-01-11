/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "OI.h"
#include <RobotMap.h>

using namespace std; 

OI::OI() {
  // Process operator interface input here.
  joystick = new Joystick(kJoystick1);
}

double OI::JoystickGetLeft() {
  return -joystick->GetRawAxis(3);
}

double OI::JoystickGetRight() {
  return -joystick->GetRawAxis(1);
}
