/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Subsystems\GPS.h"
#include <iostream>

GPS::GPS() : frc::Subsystem("GPS"), mGyroPtr(nullptr), mAcceleroPtr(nullptr), mRightEncoder(nullptr), mLeftEncoder(nullptr)
{
  mGyroPtr = new ADXRS450_Gyro();
  mAcceleroPtr = new frc::BuiltInAccelerometer();

  mRightEncoder = new Encoder(0,1,false);
  mLeftEncoder = new Encoder(2,3,false);

  mDistCaptPtr = new AnalogInput(0);
}

void GPS::InitDefaultCommand() 
{
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}

void GPS::ResetSensors() 
{
  if(mGyroPtr != nullptr)
  {
    mGyroPtr->Calibrate();
  }
}

double GPS::GetAngle() 
{
  if(mGyroPtr != nullptr)
  {
    return mGyroPtr->GetAngle();
  }
  else return 0;
}

double GPS::GetXAcceleration() 
{
  if(mAcceleroPtr != nullptr)
  {
    return mAcceleroPtr->GetX();
  }
  else return 0;
}

double GPS::GetYAcceleration() 
{
  if(mAcceleroPtr != nullptr)
  {
    return mAcceleroPtr->GetY();
  }
  else return 0;
}

double GPS::GetZAcceleration() 
{
  if(mAcceleroPtr != nullptr)
  {
    return mAcceleroPtr->GetZ();
  }
  else return 0;
}

double GPS::GetAcceleration()
{
  if(mAcceleroPtr != nullptr)
  {
    return sqrt(pow(mAcceleroPtr->GetX(),2)   //formule pour calculer
              + pow(mAcceleroPtr->GetY(),2)   // l'acceleration totale
              + pow(mAcceleroPtr->GetZ(),2));
  }
  else return 0;
}

double GPS::GetEncoderDistance()
{
  if(mRightEncoder != nullptr)
  {
    return mRightEncoder->GetRaw()/1430*kCircumference;
  }
  else return 0;
}

double GPS::GetCapteurDistance()
{
  // en pouces
  return (mDistCaptPtr->GetVoltage()*VoltToFootDistCapt*12);
}

double GPS::ComputeDistance(double iX1, double iY1, double iX2, double iY2)
{
  return sqrt(  pow(iX1 - iX2, 2) 
              + pow(iY1 - iY2, 2));
}