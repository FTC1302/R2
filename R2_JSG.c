#pragma config(Motor,  motorC,          nxtmotor_JSG,    tmotorNXT, PIDControl, encoder)

#include "R2_const.h"
#include <JoystickDriver.c>
int JSG_target = 0;

task main()
{
/*
	motor[nxtmotor_JSG] = 0;                // reset the Motor Encoder of Motor C
  nMotorEncoder[nxtmotor_JSG] = 0;                // reset the Motor Encoder of Motor C
  while(true)
  {
    getJoystickSettings(joystick);


     //JSG control
    if (joystick.joy1_TopHat==JOY_BUTTON_TOPHAT_RIGHT)
        JSG_target=20;
    else if (joystick.joy1_TopHat==JOY_BUTTON_TOPHAT_LEFT)
        JSG_target=-20;
    else
        JSG_target=0;

    int JSG_POWER=30;
    if (JSG_target>0)
    {
      if (nMotorEncoder[nxtmotor_JSG]<JSG_target)
        motor[nxtmotor_JSG]=JSG_POWER;
      else
        motor[nxtmotor_JSG]=0;
    }
    else if (JSG_target<0)
    {
      if (nMotorEncoder[nxtmotor_JSG]>JSG_target)
        motor[nxtmotor_JSG]=-JSG_POWER;
      else
        motor[nxtmotor_JSG]=0;
    }
    else
    {
      if (motor[nxtmotor_JSG]<-15)
        motor[nxtmotor_JSG]=JSG_POWER;
      else if (motor[nxtmotor_JSG]>8)
        motor[nxtmotor_JSG]=-JSG_POWER;
      else
      {
        motor[nxtmotor_JSG]=0;
        PlaySound(soundBeepBeep);
      };
    }

  }

*/










  int p=30;
while(true){
  while(nMotorEncoder[nxtmotor_JSG] < 20)  // while the Motor Encoder of Motor B has not yet reached 360 counts:
  {
    motor[nxtmotor_JSG] = p;                 // motor B is given a power level of 75
  };
  motor[nxtmotor_JSG]=0;

  wait10Msec(100);
  while(nMotorEncoder[nxtmotor_JSG] > 8)  // while the Motor Encoder of Motor B has not yet reached 360 counts:
  {
    motor[nxtmotor_JSG] = -p;                 // motor B is given a power level of 75
  }
  motor[nxtmotor_JSG]=0;
  wait10Msec(100);
  while(nMotorEncoder[nxtmotor_JSG] > -20)  // while the Motor Encoder of Motor B has not yet reached 360 counts:
  {
    motor[nxtmotor_JSG] = -p;                 // motor B is given a power level of 75
  }
  motor[nxtmotor_JSG]=0;
  wait10Msec(100);
  while(nMotorEncoder[nxtmotor_JSG] < -15)  // while the Motor Encoder of Motor B has not yet reached 360 counts:
  {
    motor[nxtmotor_JSG] = p;                 // motor B is given a power level of 75
  }
  motor[nxtmotor_JSG]=0;
  wait10Msec(100);
}
  wait10Msec(10000);

}
