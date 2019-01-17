/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "OI.h"
#include "Subsystems/DriveTrain.h"
#include "Subsystems/GPS.h"
#include "Subsystems/RotationPID.h"
#include <SmartDashboard/SendableChooser.h>
#include <TimedRobot.h>

class Robot : public frc::TimedRobot 
{
 public:
  static DriveTrain m_drivetrain;
  static GPS m_gps; 
  static OI m_oi;

  static RotationPID mPid;

  void RobotInit() override;
  void RobotPeriodic() override;
  void DisabledInit() override;
  void DisabledPeriodic() override;
  void AutonomousInit() override;
  void AutonomousPeriodic() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void TestPeriodic() override;

 private:
  // Have it null by default so that if testing teleop it
  // doesn't have undefined behavior and potentially crash.
  frc::Command* m_autonomousCommand = nullptr;

  frc::SendableChooser<frc::Command*> m_chooser;

};
