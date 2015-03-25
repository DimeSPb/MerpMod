/*	Copyright (C) 2014 Scott T Anderson & 2012-2013 Merrill A. Myers III merrillamyersiii@gmail.com
	
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
*/

#include "EcuHacks.h"

#if ALS_HACKS

void AntiLag()
{
	if (pRamVariables->DriveMode == 4 && *pAf1Res > EGTResistanceThreshold && *pCoolantTemp > ECTALSThreshold)
		{
			if (pRamVariables->ALSActive == 0)
				{
					pRamVariables->ALSActive = 0x01;
				}
			else if (pRamVariables->ALSActive == 1 || pRamVariables->ALSActive == 2)
				{
					if (TestIdleSwitch())
						{
							float RimRPMCutoff = (DefaultALSTargetIdleSpeedFCRI - DefaultRimRPMDiff);
							
							if (RIMCutMode == 1 && *pAcceleratorPedal <= FCRIPedalThresh && *pFuelCut < 13 && *pVehicleSpeed < RIMVehicleSpeedDisable)
								{
									pRamVariables->ALSTargetIdleSpeed = DefaultALSTargetIdleSpeedFCRI;
									pRamVariables->ALSActive = 0x02;
									if (*pEngineSpeed > RimRPMCutoff)
										{
											RotationalFuelCut();
										}
								}
/*							else if (RIMCutMode == 2 && *pAcceleratorPedal <= FCRIPedalThresh && *pFuelCut < 13 && *pVehicleSpeed < RIMVehicleSpeedDisable)
								{
									//set idle speed
									RotationalSparkCut();
									pRamVariables->ALSActive = 0x02;
								}
							else if (RIMCutMode == 3 && *pAcceleratorPedal <= FCRIPedalThresh && *pFuelCut < 13 && *pVehicleSpeed < RIMVehicleSpeedDisable)
								{
									//Set Idle Speed
									//RotationalFuelCut();
									//RotationalSparkCut();
									//RotationalComboCut();
									pRamVariables->ALSActive = 0x02;
								}
*/
							else if (*pEngineSpeed >= ALSRPMLimit && *pVehicleSpeed < ALSVehicleSpeedDisable && *pAcceleratorPedal < FCRIPedalThresh)//Add Smoothing for exiting?
								{
									//Enter ANTILAG!
									pRamVariables->ALSActive = 0x05;
									pRamVariables->FuelCut = *pFuelCut;
									pRamVariables->ALSTargetIdleSpeed = DefaultALSTargetIdleSpeed;
									pRamVariables->StartTimer3 = 0.0;
								}
							else
								{
									pRamVariables->FuelCut = *pFuelCut;
									pRamVariables->ALSActive = 0x01;
								}
						}
					else if (*pAcceleratorPedal > ALSAcceleratorTrigger)
						{
							pRamVariables->ALSActive = 0x03;
						}
					else
						{
							pRamVariables->ALSActive = 0x01;
							pRamVariables->FuelCut = *pFuelCut;
							pRamVariables->ALSTargetIdleSpeed = DefaultALSTargetIdleSpeedFCRI;
						}
				}
			else if (pRamVariables->ALSActive >= 3 && *pVehicleSpeed > ALSVehicleSpeedEnable && TestClutchSwitch())
				{
					pRamVariables->ALSActive = 0x04;
				}
			else if (pRamVariables->ALSActive >= 3 && *pVehicleSpeed > ALSVehicleSpeedEnable)
				{
					pRamVariables->ALSRequestedTorque = 0.0;
					pRamVariables->ALSActive = 0x03;
				}
			else if (pRamVariables->ALSActive == 5)
				{
					Timers(0.0, 5.0, 3);
					if (pRamVariables->TimerUp3 == 1 || *pVehicleSpeed > ALSVehicleSpeedDisable || *pAcceleratorPedal > ALSPedalThresh) // Or hits boost limit
						{
							pRamVariables->ALSActive = 0x01;
						}
					else if (ALSCutMode == 1 && *pBoost > DefaultALSBoostLimit)//Do I want Boost control here?
						{
							RotationalFuelCut();
						}
					else
						{
							pRamVariables->FuelCut = *pFuelCut;
							//	AntiLag Stuff
							//RotationalSparkCut();
							//RotationalFuelCut();
							//RotationalComboCut();
						}
				}
			else if (pRamVariables->ALSActive >= 3)
				{
					pRamVariables->ALSActive = 0x01;
					pRamVariables->ALSRequestedTorque = 0.0;
				}
			else
				{
					pRamVariables->ALSRequestedTorque = 0.0;
				}
			if (RollingAntiLagEnabled == HackEnabled && *pAcceleratorPedal > ALSAcceleratorTrigger)
				{
					RollingAntiLag();
				}
			else
				{
				}
		}
	else
		{
			pRamVariables->ALSActive = 0x00;
			pRamVariables->FuelCut = *pFuelCut;
		}
	ThrottleKick();
}

void ThrottleKick()
{
	float ALSRevMax = (DefaultALSTargetIdleSpeed + 500.0);
	
//	ALSTPSRPMCompensation = ((pRamVariables->ALSTargetIdleSpeed - *pEngineSpeed) / 100.0)
//	float ALSTPSBoostCompensation = (*pBoostError * 5.0);

	if (*pEngineSpeed < ALSRevMax)
		{
			if (pRamVariables->ALSActive == 5)
				{
					pRamVariables->ALSTPS = ALSTPS;//	= (ALSTPS + ALSTPSBoostCompensation);
				}
			else if (pRamVariables->ALSActive == 4)
				{
				//	pRamVariables->ALSTPS = pRamVariables->ALSRevMatch;	//	Rev Matching
					pRamVariables->ALSTPS = *pTargetTPSIdle;
				}
			else
				{
					pRamVariables->ALSTPS = *pTargetTPSIdle;
				}
		}
	else
		{
			pRamVariables->ALSTPS = *pTargetTPSIdle;
		}
}

void RotationalFuelCut()
{
	short FuelCut;
	if (pRamVariables->ALSActive == 5 || pRamVariables->ALSActive == 4)
		{
		}
	else
		{
			if (pRamVariables->FuelCutRIM == 3)
				{
					FuelCut = 0x06;
				}
			else if (pRamVariables->FuelCutRIM == 6)
				{
					FuelCut = 0x0C;
				}
			else if (pRamVariables->FuelCutRIM == 9)
				{
					FuelCut = 0x03;
				}
			else
				{
					FuelCut = 0x09;
				}
			pRamVariables->FuelCutRIM = FuelCut;
			pRamVariables->FuelCut = pRamVariables->FuelCutRIM;
		}
}
void RollingAntiLag()
{
	if (TestBrakeSwitch() && *pVehicleSpeed >= ALSVehicleSpeedEnable)//Maybe Switch Brake for Cruise Cancel or something?
		{
			pRamVariables->ALSActive = 0x04;
			pRamVariables->FuelCut = *pFuelCut;
		}
}

/*
void RotationalSparkCut()
{
	if (ALSCutMode == 2 && *pBoost >= DefaultALSBoostLimit)
		{	
			SparkCutRotationalIdle();
		}
	OEMSparkRoutine();
}

hPrepForSpark (0x00006E0C)
sPrepForSpark (0x0000A458)
pCyl1SparkCut ((unsigned char*)0xFFFF5DF0)
pCyl2SparkCut ((unsigned char*)0xFFFF5DF8)
pCyl3SparkCut ((unsigned char*)0xFFFF5E00)
pCyl4SparkCut ((unsigned char*)0xFFFF5E08)

void SparkCutRotationalIdle()
{
	if (sparkcuts = normal)
		{
			cut 1
		}
	else if (cut 1)
		{
			cut 2
		}
	else if (cut 2)
		{
			cut 3
		}
	else if (cut 3)
		{
			cut 4
		}
	else if (cut 4)
		{
			cut 1
		}
}
*/
#endif