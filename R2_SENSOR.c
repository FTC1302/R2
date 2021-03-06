#pragma config(Hubs, S1, HTMotor, HTMotor, HTMotor, HTServo)
#pragma config(Sensor, S2, sensor_arm_left_angle, sensorI2CCustom)
#pragma config(Sensor, S3, sensor_arm_right_angle, sensorI2CCustom)
#pragma config(Sensor, S4, HTSPB, sensorI2CCustom9V)
#pragma config(Motor, motorA, nxtmotor_flapper_left, tmotorNXT, PIDControl, encoder)
#pragma config(Motor, motorB, nxtmotor_flapper_right, tmotorNXT, PIDControl, encoder)
#pragma config(Motor, motorC, nxtmotor_JSG, tmotorNXT, PIDControl, encoder)
#pragma config(Motor, mtr_S1_C3_1, drive_motor_1, tmotorTetrix, openLoop)
#pragma config(Motor, mtr_S1_C3_2, drive_motor_2, tmotorTetrix, openLoop)
#pragma config(Motor, mtr_S1_C1_1, arm_motor_left, tmotorTetrix, openLoop)
#pragma config(Motor, mtr_S1_C1_2, arm_motor_right, tmotorTetrix, openLoop)
#pragma config(Motor, mtr_S1_C2_1, drive_motor_3, tmotorTetrix, openLoop)
#pragma config(Motor, mtr_S1_C2_2, drive_motor_4, tmotorTetrix, openLoop)
#pragma config(Servo, srvo_S1_C4_1, servo_clip_right, tServoStandard)
#pragma config(Servo, srvo_S1_C4_2, servo_clip_left, tServoStandard)
#pragma config(Servo, srvo_S1_C4_3, servo_left_hand_bottom, tServoStandard)
#pragma config(Servo, srvo_S1_C4_4, servo_left_hand_top, tServoStandard)
#pragma config(Servo, srvo_S1_C4_5, servo_right_hand_bottom, tServoStandard)
#pragma config(Servo, srvo_S1_C4_6, servo_right_hand_top, tServoStandard)
//*!!Code automatically generated by 'ROBOTC' configuration wizard !!*//

/////////////////////////////////////////////////////////////////////////////////////////
// R2 headers
/////////////////////////////////////////////////////////////////////////////////////////

#include "R2_const.h"

// Global Variable for Robot
int arm_left_pos = 0;
int arm_right_pos = 0;

int arm_clip_pos = ARM_CLIP_PARK;
int flipper_pos = FLIPPER_DOWN;
int JSG_target = 0;

int sensor_IR=sensor_arm_left_angle;


int left_hand_bottom_pos = HAND_CLOSE;
int left_hand_upper_pos = HAND_UP;
int right_hand_bottom_pos = HAND_CLOSE;
int right_hand_upper_pos = HAND_UP;
TTimers timer_clipping = T3;
TTimers timer_R2_sys = T4;
int timer_flipping;
int timer_JOY2_BUTTON_X;
int timer_JOY2_BUTTON_B;


#include <JoystickDriver.c>
#include "drivers/hitechnic-angle.h"
#include "drivers/HTSPB-driver.h"
#include "drivers/hitechnic-irseeker-v2.h"
#include "R2_lib.h"
/////////////////////////////////////////////////////////////////////////////////////////

void display_program_info()
{
  eraseDisplay();
  nxtDisplayCenteredTextLine(1, "FTc tEaM 1032");
  nxtDisplayCenteredTextLine(3, "Compatetion Program");
	nxtDisplayCenteredTextLine(4, "ver:3");
	nxtDisplayCenteredTextLine(5, "2013.1");
	nxtDisplayCenteredTextLine(7, "dAdAlElE");
	wait1Msec(3000);
	eraseDisplay();
};


void init()
{
  RunAt(0, 0, 0);

  motor[nxtmotor_flapper_left] = 0; // reset the Motor Encoder of Motor B
	nMotorEncoder[nxtmotor_flapper_left] = 0; // reset the Motor Encoder of Motor B

	motor[nxtmotor_flapper_right] = 0; // reset the Motor Encoder of Motor C
  nMotorEncoder[nxtmotor_flapper_right] = 0; // reset the Motor Encoder of Motor C

  motor[nxtmotor_JSG] = 0; // reset the Motor Encoder of Motor C
  nMotorEncoder[nxtmotor_JSG] = 0; // reset the Motor Encoder of Motor C


	arm_pickup_park();
	hand_all_close();

  init_IR_sensor();
  init_prototype_board();

  wait1Msec(2000);

  ClearTimer(timer_R2_sys);
  timer_JOY2_BUTTON_X=0;
  timer_JOY2_BUTTON_B=0;

  ClearTimer(timer_clipping);
};


void init_arm_pos()
{
	bool arm_left_touch_bottom, arm_right_touch_bottom;
	ClearTimer(T1);
	arm_left_touch_bottom=is_arm_left_touch_bottom();
	arm_right_touch_bottom=is_arm_right_touch_bottom();

  while(true)
	{
    nxtDisplayTextLine(0, "%d, %d",arm_left_touch_bottom, arm_right_touch_bottom);
    if (arm_left_touch_bottom!=is_arm_left_touch_bottom())
    {
	    arm_left_touch_bottom=is_arm_left_touch_bottom();
	    PlaySound(soundBeepBeep);
	  };
	  if (arm_right_touch_bottom!=is_arm_right_touch_bottom())
	  {
	    arm_right_touch_bottom=is_arm_right_touch_bottom();
      PlaySound(soundBeepBeep);
    };

    if (arm_left_touch_bottom & arm_right_touch_bottom)
      break;

    if (time1[T1]>1000)
    {
      PlaySound(soundBlip);
      ClearTimer(T1);
    };
  };
  reset_angle_sensor();
}

task main()
{
	eraseDisplay();
  while(true)
  {
	  bool left_arm_touch_bottom, right_arm_touch_bottom;
	  left_arm_touch_bottom = is_arm_left_touch_bottom();
	  right_arm_touch_bottom = is_arm_right_touch_bottom();

	  int IR_Direction;
	  IR_Direction=get_IR_direction();

	  int left_angle_counter, right_angle_counter;
	  left_angle_counter=get_arm_left_pos();
	  right_angle_counter=get_arm_right_pos();

	  int left_ring_weight, right_ring_weight;
	  left_ring_weight=get_left_ring_weight();
	  right_ring_weight=get_right_ring_weight();

    nxtDisplayCenteredTextLine(0, "tEaM 1302 R2");
    nxtDisplayTextLine(2, "Touch:L%3d R%3d", left_arm_touch_bottom, right_arm_touch_bottom);
    nxtDisplayTextLine(3, "Angle:L%3d R%3d", left_angle_counter, right_angle_counter);
    nxtDisplayTextLine(4, "Weigh:L%3d R%3d", left_ring_weight, right_ring_weight);
    nxtDisplayTextLine(5, "IR   : %2d", IR_Direction);

  };
}
