/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once


#include <RobotMap.h>


#include <SpeedController.h>
#include <SpeedControllerGroup.h>

#include "C:\Users\lenovo i5 2\wpilib\user\cpp\include\ctre\Phoenix.h"
#include "C:\Users\lenovo i5 2\wpilib\cpp\current\include\Drive\DifferentialDrive.h"
#include "C:\Users\lenovo i5 2\wpilib\cpp\current\include\Commands/Subsystem.h"




class DriveTrain : public frc::Subsystem {
 private:

  WPI_TalonSRX motorL1{kMotorLeft1};
	WPI_TalonSRX motorL2{kMotorLeft2};
	WPI_TalonSRX motorR1{kMotorRight1};
	WPI_TalonSRX motorR2{kMotorRight2};

	frc::SpeedControllerGroup leftSide{motorL1, motorL2};
	frc::SpeedControllerGroup rightSide{motorR1, motorR2};

  DifferentialDrive Drive{leftSide, rightSide};

  // It's desirable that everything possible under private except
  // for methods that implement subsystem capabilities

 public:
  DriveTrain();
  void InitDefaultCommand() override;
  void f_TankDrive(double left, double right);
};
