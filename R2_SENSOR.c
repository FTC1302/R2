#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     sensor_arm_left_angle, sensorI2CCustom)
#pragma config(Sensor, S3,     sensor_arm_right_angle, sensorI2CCustom)
#pragma config(Sensor, S4,     HTSPB,          sensorI2CCustom9V)
#pragma config(Motor,  mtr_S1_C1_1,     drive_motor_1, tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     drive_motor_2, tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     arm_motor_left, tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     arm_motor_right, tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     drive_motor_3, tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     drive_motor_4, tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C4_1,    servo_clip_left,      tServoStandard)
#pragma config(Servo,  srvo_S1_C4_2,    servo_clip_right,     tServoStandard)
#pragma config(Servo,  srvo_S1_C4_3,    servo_left_hand_bottom, tServoStandard)
#pragma config(Servo,  srvo_S1_C4_4,    servo_left_hand_top,  tServoStandard)
#pragma config(Servo,  srvo_S1_C4_5,    servo_right_hand_bottom, tServoStandard)
#pragma config(Servo,  srvo_S1_C4_6,    servo_right_hand_top, tServoStandard)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

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
int timer_protect_left_move;
int timer_protect_right_move;
int timer_o_c_hand;



//#include <JoystickDriver.c>
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

	arm_pickup_park();
	hand_left_jie();
  hand_right_jie();

  init_IR_sensor();
  init_prototype_board();

  wait1Msec(2000);

  ClearTimer(timer_R2_sys);
  timer_left_arm  = 0;
  timer_right_arm = 0;
  timer_protect_left_move=0;
  timer_protect_right_move=0;
  timer_o_c_hand=0;

  ClearTimer(timer_left_hand_roll);
	ClearTimer(timer_right_hand_roll);
	ClearTimer(timer_clipping);
};


void init_arm_pos()
{
	bool arm_left_touch_bottom, arm_right_touch_bottom;
	while(true)
	{
		arm_left_touch_bottom=is_arm_left_touch_bottom();
		arm_right_touch_bottom=is_arm_right_touch_bottom();

		if (arm_left_touch_bottom & arm_right_touch_bottom)
			break;

		if (!arm_left_touch_bottom)
			arm_left_down(10);
		else
			arm_left_stop();

		if (!arm_right_touch_bottom)
			arm_right_down(10);
		else
			arm_right_stop();
	};
	reset_angle_sensor();

	arm_left_target = ARM_TARGET_NONE;
  arm_right_target = ARM_TARGET_NONE;
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