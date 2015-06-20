#define MOD_DATE 15.6.20.1023

#include "Switch.h"
#define MOD_CONFIG Switch
#define MOD_BUILD Testing
#define MOD_RELEASE 0
#define ECU_CALIBRATION_ID A2ZJE11J
#define ECU_IDENTIFIER 4312594006
/////////////////////
// NonSpecific Rom Info and Routines
/////////////////////

#define dCalId (0x00002000)
#define dEcuId (0x000CC7E8)
#define dRomHoleStart (0x000E1000)
#define pRamHoleStart (0xFFFF6F90)
#define sPull2DFloat (0x0000209C)
#define sPull3DFloat (0x00002110)

/////////////////////
// Switch Hacks
/////////////////////

#define pTGVLeftVoltage ((unsigned short*)0xFFFF2d2c)
#define pTGVRightVoltage ((unsigned short*)0xFFFF2d2e)
#define sShortToFloat (0x0000253c)

/////////////////////
// Rev Limit Hack
/////////////////////

#define hRevLimDelete (0x00013470)
#define sRevLimStart (0x0002C7AC)
#define sRevLimEnd (0x0002C7E2)
#define pFlagsRevLim ((unsigned char*)0xFFFF5660)
#define RevLimBitMask (0x80)

/////////////////////
// Speed Density Hack
/////////////////////

#define hMafCalc (0x00007F98)
#define sMafCalc (0x00007F3C)

/////////////////////
// Injector Hack
/////////////////////

#define dInjectorScaling ((float*)0x000C5BBC)
#define hInjectorScaling (0x000265F0)

/////////////////////
// Cel Hacks
/////////////////////

#define sCelTrigger (0x00071F34)
#define hCelSignal (0x0007204C)
#define pCelSignalOem ((unsigned char*)0xFFFF6BEE)

/////////////////////
// Boost Hacks
/////////////////////

#define hPullTargetBoost (0x0001520C)
#define hTableTargetBoostKcaAlt (0x00015224)
#define tTargetBoostKcaAlt (0x00079c3c)
#define tTargetBoostKcaBHi (0x00079E10)
#define tTargetBoostKcaBLo (0x00079DF4)
#define hTableTargetBoostKcaBHi (0x00015220)
#define hTableTargetBoostKcaBLo (0x0001521C)

/////////////////////
// WGDC Hacks
/////////////////////

#define hPullWgdc (0x00015584)
#define hWgdc (0x00012FD8)
#define sWgdc (0x00014D38)
#define hTableWgdcInitialKcaBHi (0x0001558c)
#define tWgdcInitialKcaBHi (0x00079d68)
#define hTableWgdcInitialKcaBLo (0x00015588)
#define tWgdcInitialKcaBLo (0x00079d4c)
#define hTableWgdcMax (0x000157bc)
#define tWgdcMax (0x00079DA0)

/////////////////////
// Primary Open Loop Fueling Hacks
/////////////////////

#define pPolf4Byte (0xFFFF54F4)
#define hPull3DPolf (0x00029f70)
#define hTablePolfKcaBLo (0x00029f78)
#define tPolfKcaBLo (0x0007afd0)
#define hTablePolfKcaBHi (0x00029f7c)
#define tPolfKcaBHi (0x0007afec)
#define hJsrPolf (0x00029dd8)
#define hPolf (0x0001348c)
#define sPolf (0x00029d2C)
#define pPolfEnrich (0xFFFF54F4)

/////////////////////
// Timing Hacks
/////////////////////

#define hBaseTiming (0x00013538)
#define hTableBaseTimingKCAHi (0x0002ffa8)
#define tBaseTimingKCAHi (0x0007b664)
#define hTableBaseTimingKCALo (0x0002ffa0)
#define tBaseTimingKCALo (0x0007b648)
#define pBaseTiming (0xFFFF57F0)
#define sBaseTiming (0x0002fdd8)
#define hPull3DTiming (0x0002ffa4)
#define hSubKca (0x00032E78)
#define pKcaIam (0xFFFF5920)
#define hTableBaseTimingIdleOverSpeed (0x0002fd0c)
#define tBaseTimingIdleOverSpeed (0x0007b2a4)
#define hTableBaseTimingIdleUnderSpeed (0x0002fd10)
#define dBaseTimingIdleUnderSpeed (0x000c8744)

/////////////////////
// Spark Cut
/////////////////////

////#define sSparkCutOcrStart (0x0000A756)
////#define sSparkCutOcrEnd (0x0000A76C)
////#define sSparkCutGrStart (0x0000A7C6)
////#define sSparkCutGrEnd (0x0000A7CE)

/////////////////////
// Flags-Signals
/////////////////////

#define pCruiseMasterFlags ((unsigned char*)0xFFFF4C18)//	NEED TO SCAN
#define CruiseMasterBitMask ((unsigned char)0x01)
#define pResumeFlags ((unsigned char*)0xFFFF4C18)
#define ResumeBitMask ((unsigned char)0x04)
#define pCoastFlags ((unsigned char*)0xFFFF4C18)
#define CoastBitMask ((unsigned char)0x02)
#define pBrakeFlags ((unsigned char*)0xFFFF4C18)
#define BrakeBitMask ((unsigned char)0x08)
#define pClutchFlags ((unsigned char*)0xFFFF5049)
#define ClutchBitMask ((unsigned char)0x80)
#define pIdleFlags ((unsigned char*)0xFFFF4FC4)	//		NEED TO SCAN
#define IdleBitMask ((unsigned char)0x80)
#define pNeutralFlags ((unsigned char*)0xFFFF5047)	//	Need to SCAN
#define NeutralBitMask ((unsigned char)0x02)
#define pDefoggerFlags ((unsigned char*)0xFFFF5047)
#define DefoggerBitMask ((unsigned char)0x80)		//	Need to SCAN
#define pClosedLoopFlags ((unsigned char*)0xFFFF6B79)
//8 = Closed Loop (normal)]  [10 = Open Loop (normal)]  [7 = Open Loop due insufficient coolant temp]  [14 = Open Loop due to system failure].

/////////////////////
// NonSpecific Engine params
/////////////////////

#define pFbkc4 ((float*)0xFFFF58CC)
#define pIam4 ((float*)0xFFFF2570)
#define pEngineSpeed ((float*)0xFFFF5078)
#define pVehicleSpeed ((float*)0xFFFF5068)
#define pCoolantTemp ((float*)0xFFFF2DC8)
#define pAtmoPress ((float*)0xFFFF2E34)
#define pManifoldAbsolutePressure ((float*)0xFFFF4DCC)
#define pIntakeAirTemp ((float*)0xFFFF2DB8)
#define pMassAirFlow ((float*)0xFFFF2DF4)
#define pMafSensorVoltage ((short*)0xFFFF2D22)
#define pEngineLoad ((float*)0xFFFF4F58)
#define pReqTorque ((float*)0xFFFF5AC4)
#define pThrottlePlate ((float*)0xFFFF4E5C)
#define pWgdc4 ((float*)0xFFFF4BA8)
#define pCurrentGear ((unsigned char*)0xFFFF516D)
#define pAf1Res ((float*)0xFFFF4A50)
#define pDeltaMap ((float*)0xFFFF4DC0)
#define pAcceleratorPedal ((float*)0xFFFF4FB4)
#define pThrottlePlateTarget ((float*)0xFFFF5AC0)
#define pTargetIdleSpeed ((float*)0xFFFF5BC4)
#define hPullTargetIdleSpeed (0x0003A6E0)
#define hTableTargetIdleSpeedA (0x0003A6E4)
#define tTargetIdleSpeedA (0x0007BA10)
#define hTableTargetIdleSpeedB (0x0003A6EC)
#define tTargetIdleSpeedB (0x0007BA38)
#define hTableTargetIdleSpeedC (0x0003A6F4)
#define tTargetIdleSpeedC (0x0007BA60)
#define hPullIdleMapSelection (0x0003A6CC)
#define pIdleMapSelection (0xFFFF5C3C)
#define hPullRequestedTorqueA (0x00039B74)
#define tRequestedTorqueA (0x0007BD60)
#define hTableRequestedTorqueA (0x00039B70)
#define sFloatToShort (0x0000250C)
#define sFloatToByte (0x0000254C)
#define pAVCS ((float*)0xFFFF6124)
#define hPullAVCS (0x00047AB4)
#define tAVCS (0x0007C1DC)
#define hTableAVCS (0x00047ABC)
#define pO2SensorScaling ((float*)0xFFFF4A48)
#define hPullO2SensorScaling (0x0000F3E4)
#define tO2SensorScaling (0x0007BE6C)
#define hTableO2SensorScaling (0x0000F3E0)
#define pAFSensor1Current ((float*)0xFFFF4A4C)
#define hOpenLoopAFRmin (0x00029F90)
#define dOpenLoopAFRmin (0x000C5E2C)
////#define hTargetTPSBandPass (0x000BE73C)
#define sBandPass (0x00002480)
#define pTargetTPSIdle ((float*)0xFFFF5AE4)
#define pTargetIdleAir ((float*)0xFFFF5AF4)
#define hTargetIdleTPSstiA (0x0001D75C)
#define hTargetIdleTPSstiB (0x0003962C)
#define hFuelCut (0x000254D8)
#define pFuelCut ((short*)0xFFFF524C)
#define pBoost ((float*)0xFFFF4DD0)

/////////////////////
// OBD Experimental stuff
/////////////////////

//#define pObdVinDirect ((unsigned char*)0xFFFF2004)

/////////////////////
// New Definitions
/////////////////////

#define dLoadSmoothingA (0x000C1BF4)
#define dLoadSmoothingB (0x000C1BF8)
#define dLoadSmoothingFinal (0x000C1BFC)

/////////////////////
// Memory Reset
/////////////////////

#define sMemoryReset (0x00010950)
#define hMemoryReset (0x0000DFE0)
#define pMemoryResetLimit (0xFFFFBFFB)
#define hMemoryResetLimit (0x000110D8)
#define sMemorySoftReset (0x00049B34)

