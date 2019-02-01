/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Subsystems\Vision.h"
#include "Subsystems\DriveTrain.h"
#include "Timer.h"
#include <iostream>

Vision::Vision() : Subsystem("Vision"), m_cameraServer(nullptr) {}

void Vision::InitDefaultCommand() 
{
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}

void Vision::Initialization()
{
  
  //m_cameraServer->GetInstance()->StartAutomaticCapture("USBCamera");
  if (m_cameraServer != nullptr)
  {
    m_cameraServer->GetInstance()->AddAxisCamera("Axis Cam",kCameraIP);
    m_cameraServer->GetInstance()->PutVideo("Camera MS",480,360);
  }

  mNetworkTableInstanceInst = nt::NetworkTableInstance::GetDefault();
}

void Vision::GetLine(double * oLine)
{

  std::cout<<"before table call"<<std::endl;
  //auto inst = nt::NetworkTableInstance::GetDefault();
  auto table = mNetworkTableInstanceInst.GetTable("GRIP/myLinesReport");
  std::cout<<"after table call"<<std::endl;

  auto wCoordX1 = table->GetEntry("x1").GetDoubleArray(0); 
  auto wCoordY1 = table->GetEntry("y1").GetDoubleArray(0);
  auto wCoordX2 = table->GetEntry("x2").GetDoubleArray(0);
  auto wCoordY2 = table->GetEntry("y2").GetDoubleArray(0);
  auto wAngle = table->GetEntry("angle").GetDoubleArray(90); 
  std::cout<<"after entry calls"<<std::endl;

  int wTaille = 2;
  // Attention : sizeof() est une taille en octets, pas la longueur du array
  //int wTaille =  sizeof( table->GetEntry("y1").GetDoubleArray(0) );
  for(int i = 0; i < wTaille ; i++ )
  {
    if(wCoordY1[i]<kLineDetectionVerticalThreshold
      && wCoordY2[i]<kLineDetectionVerticalThreshold)
    {
      std::cout<<"in for loop"<<std::endl;
      oLine[0] = wCoordX1[i];
      oLine[1] = wCoordY1[i];
      oLine[2] = wCoordX2[i];
      oLine[3] = wCoordY2[i];
      oLine[4] = wAngle[i];
      break;
    }
  }
}

double Vision::GetLineAngle()
{
  std::cout<<"before array creation"<<std::endl;
  double *wLine = new double(5);
  GetLine(wLine);

  return wLine[4];
}

// Fonction: AlignerRobotLigne
// Entree: oTableau est un array qui contient les valeurs d une ligne
// Sortie: retour: vitesse du robot pour s'aligner
// Sert pour un parametre de la methode TankDrive
// L'autre prend un 0
// Rend par defaut un 0 si le robot est aligne avec la ligne
double Vision::AlignerRobotLigne(const double iTableau[5])
{
  double angle = iTableau[4];
  if(angle != 90)
  {
    if(angle < 90)
    {
      return 0.4;
    }

    else
    {
      return -0.4;
    }
  }
  return 0;
}

void Vision::DisplayData() 
{
  double wCoordLine[5];
  GetLine(wCoordLine);
 
  SmartDashboard::PutNumber("x1", wCoordLine[0]);
  SmartDashboard::PutNumber("y1", wCoordLine[1]);
  SmartDashboard::PutNumber("x2", wCoordLine[2]);
  SmartDashboard::PutNumber("y2", wCoordLine[3]);
  SmartDashboard::PutNumber("angle", wCoordLine[4]);
}