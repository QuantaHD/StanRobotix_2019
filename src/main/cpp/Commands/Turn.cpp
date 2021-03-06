/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Commands/Turn.h"

#include <iostream>

Turn::Turn(double iAngle, RotationPID* ipid, bool dynamicAngle)
{
  Requires(&Robot::m_drivetrain);
  mAngleIncrement = iAngle;
  mPidPtr = ipid;
  mDynamicAngle = dynamicAngle;
}

void Turn::Initialize() 
{
  //mPidPtr = new RotationPID(Robot::PIDSettingsPtr[0], Robot::PIDSettingsPtr[1], Robot::PIDSettingsPtr[2]);
  if (mPidPtr != nullptr)
  {
    delete mPidPtr;
    mPidPtr = nullptr;
  }

  mPidPtr = new RotationPID(Robot::PIDP,Robot::PIDI,Robot::PIDD);

  Robot::mPid = mPidPtr;
  
  if (mDynamicAngle)
  {
    mAngleIncrement = Robot::PIDVal;
  }
  mTargetAngle = mAngleIncrement + Robot::m_gps.GetAngle();
  mPidPtr->SetSetpoint(mTargetAngle);
}

void Turn::Execute() 
{
  double wPower = 0;
  
  if(mPidPtr != nullptr) 
  {
    wPower = mPidPtr->GetPIDOutput();
  }

  Robot::m_drivetrain.TankDrive(wPower, -wPower); 
}

bool Turn::IsFinished() 
{ 
  if(mPidPtr != nullptr) 
  { 
    return mPidPtr->OnTarget();
  }
  else return false; 
}

void Turn::End() 
{
  Robot::m_drivetrain.TankDrive(0,0);
}

void Turn::Interrupted() 
{
  Robot::m_drivetrain.TankDrive(0,0);
}
