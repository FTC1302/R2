
#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Sensor, S2,     sensor_arm_left_angle, sensorI2CCustom)
#pragma config(Sensor, S3,     sensor_arm_right_angle, sensorI2CCustom)
#pragma config(Sensor, S4,     HTSPB,          sensorI2CCustom9V)
#pragma config(Motor,  motorA,          nxtmotor_flapper_left,     tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorB,          nxtmotor_flapper_right,    tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C3_1,     drive_motor_1, tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     drive_motor_2, tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_1,     arm_motor_left, tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     arm_motor_right, tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     drive_motor_3, tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     drive_motor_4, tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C4_1,    servo_clip_right,     tServoStandard)
#pragma config(Servo,  srvo_S1_C4_2,    servo_clip_left,      tServoStandard)
#pragma config(Servo,  srvo_S1_C4_3,    servo_left_hand_bottom, tServoStandard)
#pragma config(Servo,  srvo_S1_C4_4,    servo_left_hand_top,  tServoStandard)
#pragma config(Servo,  srvo_S1_C4_5,    servo_right_hand_bottom, tServoStandard)
#pragma config(Servo,  srvo_S1_C4_6,    servo_right_hand_top, tServoStandard)
//*!!Code automatically generated by 5'ROBOTC' configuration wizard               !!*//

#include "R2_const.h"

// Global Variable for Robot
int arm_left_pos  = 0;
int arm_right_pos = 0;
int arm_left_target  = ARM_TARGET_NONE;
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
int flipper_pos = FLIPPER_DOWN;

int sensor_IR=sensor_arm_left_angle;


int left_hand_bottom_pos  = HAND_CLOSE;
int left_hand_upper_pos   = HAND_UP;
int right_hand_bottom_pos = HAND_CLOSE;
int right_hand_upper_pos  = HAND_UP;
TTimers timer_left_hand_roll  = T1;
TTimers timer_right_hand_roll = T2;
TTimers timer_clipping = T3;
TTimers timer_R2_sys = T4;
int timer_left_arm;
int timer_right_arm;
int timer_protect_left_move;
int timer_protect_right_move;
int timer_o_c_hand;
int timer_flipping;
int timer_JOY2_BUTTON_X;
int timer_JOY2_BUTTON_B;


#include <JoystickDriver.c>
#include "drivers/hitechnic-angle.h"
#include "drivers/HTSPB-driver.h"
#include "drivers/hitechnic-irseeker-v2.h"
#include "R2_lib.h"

void display_program_info(){
	eraseDisplay();
	nxtDisplayCenteredTextLine(1, "FTc tEaM 1032");
	nxtDisplayCenteredTextLine(3, "Robot Test Program");
	nxtDisplayCenteredTextLine(4, "ver:1");
	nxtDisplayCenteredTextLine(5, "2013.1");
	nxtDisplayCenteredTextLine(7, "dAdAlElE");
	wait1Msec(3000);
	eraseDisplay();

};

void init()
{
	RunAt(0, 0, 0);

  motor[nxtmotor_flapper_left] = 0;                // reset the Motor Encoder of Motor B
  motor[nxtmotor_flapper_right] = 0;                // reset the Motor Encoder of Motor C

	nMotorEncoder[nxtmotor_flapper_left] = 0;                // reset the Motor Encoder of Motor B
  nMotorEncoder[nxtmotor_flapper_right] = 0;                // reset the Motor Encoder of Motor C


	arm_pickup_park();
	hand_all_close();

  init_IR_sensor();
  init_prototype_board();

  wait1Msec(2000);

  ClearTimer(timer_R2_sys);
  timer_left_arm  = 0;
  timer_right_arm = 0;
  timer_protect_left_move=0;
  timer_protect_right_move=0;
  timer_o_c_hand=0;
  timer_JOY2_BUTTON_X=0;
  timer_JOY2_BUTTON_B=0;

  ClearTimer(timer_left_hand_roll);
	ClearTimer(timer_right_hand_roll);
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
		if (arm_left_touch_bottom!=is_arm_left_touch_bottom()){
	  	arm_left_touch_bottom=is_arm_left_touch_bottom();
		  PlaySound(soundBeepBeep);
		};
		if (arm_right_touch_bottom!=is_arm_right_touch_bottom()){
  		arm_right_touch_bottom=is_arm_right_touch_bottom();
		  PlaySound(soundBeepBeep);
		};

		if (arm_left_touch_bottom & arm_right_touch_bottom)
			break;

	  if (time1[T1]>1000) {
      PlaySound(soundBlip);
     	ClearTimer(T1);
    };
	};
	reset_angle_sensor();

	arm_left_target = ARM_TARGET_NONE;
  arm_right_target = ARM_TARGET_NONE;
  }
void auto_left()
	{
		RunAt(0,0,30);
		wait1Msec(560);
		RunAt(0,100,0);
		wait1Msec(1800);
		RunAt(100,0,0);
		wait1Msec(1600);
		RunAt(0,0,-30);
		wait1Msec(430);
		RunAt(0,50,0);
		wait1Msec(1000);
		RunAt(-30,0,0);
		wait1Msec(1100);
		RunAt(0,50,0);
		wait1Msec(900);
	}
	void auto_middle()
	{
		RunAt(0,0,-30);
		wait1Msec(430);
		RunAt(0,100,0);
		wait1Msec(1500);
		RunAt(-100,0,0);
		wait1Msec(2000);
		RunAt(0,0,30);
		wait1Msec(430);
		RunAt(0,50,0);
		wait1Msec(1000);
		RunAt(30,0,0);
		wait1Msec(950);
		RunAt(0,50,0);
		wait1Msec(900);

	}
	void auto_right()
	{
	  RunAt(0,-50,0);
	  wait1Msec(800);
	  RunAt(0,0,0);
	  wait1Msec(500);
		RunAt(0,100,0);
	  wait1Msec(4000);
	  RunAt(0,0,0);
	  wait1Msec(1000);
		RunAt(30,0,0);
		wait1Msec(650);
		RunAt(0,50,0);
		wait1Msec(900);
		RunAt(0,0,0);
		wait1Msec(0);

	}
task main()
	{


	int hongwai;
	int left_arm_pos;
	int right_arm_pos;
	left_arm_pos=get_arm_left_pos();
	right_arm_pos=get_arm_right_pos();
	hongwai=get_IR_direction();
	RunAt(0,100,0);
	wait1Msec(3000);
	RunAt(0,50,0);
	wait1Msec(1000);
	if(hongwai==5)
	{
		auto_left();

	}
		else
		{
			if(hongwai<5)
			{
				auto_middle();
			}
			else;
			{
				auto_right();
			}
		}
		while(right_arm_pos<1500)
	{
		arm_right_up(100);
		right_arm_pos=get_arm_right_pos()
	}
		arm_right_up(0);
}
