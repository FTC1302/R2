#pragma config(Hubs,  S1, HTMotor,  HTServo,  HTMotor,  HTMotor)
#pragma config(Sensor, S2,     sensor_arm_left_angle, sensorI2CCustom)
#pragma config(Sensor, S3,     sensor_arm_right_angle, sensorI2CCustom)
#pragma config(Sensor, S4,     HTSPB,          sensorI2CCustom9V)
#pragma config(Motor,  mtr_S1_C1_1,     drive_motor_1, tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     drive_motor_2, tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     drive_motor_3, tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     drive_motor_4, tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_1,     arm_motor_left, tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_2,     arm_motor_right, tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C2_1,    servo_clip_left,      tServoStandard)
#pragma config(Servo,  srvo_S1_C2_2,    servo_clip_right,     tServoStandard)
#pragma config(Servo,  srvo_S1_C2_3,    servo_left_hand_bottom, tServoStandard)
#pragma config(Servo,  srvo_S1_C2_4,    servo_left_hand_top,   tServoStandard)
#pragma config(Servo,  srvo_S1_C2_5,    servo_right_hand_bottom, tServoStandard)
#pragma config(Servo,  srvo_S1_C2_6,    servo_right_hand_top,  tServoStandard)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/////////////////////////////////////////////////////////////////////////////////////////
//   R2 headers
/////////////////////////////////////////////////////////////////////////////////////////

#include "R2_const.h"

// Global Variable for Robot
int arm_left_pos  = 0;
int arm_right_pos = 0;
int arm_left_target = ARM_TARGET_NONE;
int arm_right_target = ARM_TARGET_NONE;
bool arm_left_moving_up_to_target    = false;
bool arm_left_moving_down_to_target  = false;
bool arm_right_moving_up_to_target   = false;
bool arm_right_moving_down_to_target = false;

bool arm_left_up_pressed    = false;
bool arm_left_down_pressed  = false;
bool arm_right_up_pressed   = false;
bool arm_right_down_pressed = false;

int arm_clip_pos = ARM_CLIP_PARK;

int sensor_IR=sensor_arm_left_angle;

int left_hand_pos = HAND_JIE;
int right_hand_pos= HAND_JIE;
TTimers timer_left_hand_roll  = T1;
TTimers timer_right_hand_roll = T2;
TTimers timer_clipping = T3;
TTimers timer_R2_sys = T4;
int timer_left_arm;
int timer_right_arm;


#include <JoystickDriver.c>
#include "drivers/hitechnic-angle.h"
#include "drivers/HTSPB-driver.h"
#include "drivers/hitechnic-irseeker-v2.h"
#include "R2_lib.h"
/////////////////////////////////////////////////////////////////////////////////////////


void init()
{
	RunAt(0, 0, 0);

	arm_pickup_park();
	hand_left_jie();
  hand_right_jie();

  init_IR_sensor();
  init_prototype_board();

  wait1Msec(1000);

  ClearTimer(timer_R2_sys);
  timer_left_arm  = 0;
  timer_right_arm = 0;

  ClearTimer(timer_left_hand_roll);
	ClearTimer(timer_right_hand_roll);
	ClearTimer(timer_clipping);
};



task main()
{
  float x, y, R, A, ang, x1, x2, y1, y2;
	int _dirAC = 0;
	int acS1, acS2, acS3, acS4, acS5 = 0;
  int arm_speed, t;
  PlaySound(soundUpwardTones);

	init();
	//init_arm_pos();
	PlaySound(soundBeepBeep);
  while (true)
  {
		// process joystick control

    if (!joystick.StopPgm){
	    // robot move
	    getJoystickSettings(joystick);

	    if (joy1Btn(JOY_BUTTON_X))
	      ang=-15
	    else if (joy1Btn(JOY_BUTTON_B))
	      ang=15
	    else
	      ang=0;

	    x=joystick.joy1_x1;
	    y=joystick.joy1_y1;
	    x=round(x/128.0*100);
	    y=round(y/128.0*100);
	    nxtDisplayTextLine(0, "x:%3dy:%3dT%d",x, y,joystick.joy1_TopHat);

	    if ((abs(x)>3) || (abs(y)>3) || (abs(ang)>0))
	      RunAt(x, y, ang);
		  else {
		    switch(joystick.joy1_TopHat){
		      case JOY_BUTTON_TOPHAT_UP:        RunAt(0, 20, 0);  break;
		      case JOY_BUTTON_TOPHAT_UP_RIGHT:  RunAt(20, 20, 0); break;
		      case JOY_BUTTON_TOPHAT_RIGHT:     RunAt(20, 0, 0);  break;
		      case JOY_BUTTON_TOPHAT_DOWN_RIGHT:RunAt(20, -20, 0); break;
		      case JOY_BUTTON_TOPHAT_DOWN:      RunAt(0, -20, 0); break;
		      case JOY_BUTTON_TOPHAT_DOWN_LEFT: RunAt(-20, -20, 0); break;
		      case JOY_BUTTON_TOPHAT_LEFT:      RunAt(-20, 0, 0); break;
		      case JOY_BUTTON_TOPHAT_UP_LEFT:   RunAt(-20, 20, 0); break;
		      default: RunAt(0, 0, 0); break;
		    };
		  };
		};
	};
}
