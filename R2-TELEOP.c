#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Sensor, S2,     sensor_arm_left_angle, sensorI2CCustom)
#pragma config(Sensor, S3,     sensor_arm_right_angle, sensorI2CCustom)
#pragma config(Sensor, S4,     HTSPB,          sensorI2CCustom9V)
#pragma config(Motor,  mtr_S1_C1_1,     drive_motor_1, tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     drive_motor_2, tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     arm_motor_left, tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     arm_motor_right, tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     drive_motor_3, tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     drive_motor_4, tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C4_1,    servo_clip_right,      tServoStandard)
#pragma config(Servo,  srvo_S1_C4_2,    servo_clip_left,     tServoStandard)
#pragma config(Servo,  srvo_S1_C4_3,    servo_left_hand_bottom, tServoStandard)
#pragma config(Servo,  srvo_S1_C4_4,    servo_left_hand_top,  tServoStandard)
#pragma config(Servo,  srvo_S1_C4_5,    servo_right_hand_bottom, tServoStandard)
#pragma config(Servo,  srvo_S1_C4_6,    servo_right_hand_top, tServoStandard)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/////////////////////////////////////////////////////////////////////////////////////////
//   R2 headers
/////////////////////////////////////////////////////////////////////////////////////////

#include "R2_const.h"
//asdfasdf
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
   // all code will be ignored when joystick in stop mode
  getJoystickSettings(joystick);
  while (joystick.StopPgm)
  {
    PlaySound(soundBlip);
    wait1Msec(200);
    getJoystickSettings(joystick);
  };

  int x, y, ang, x1, x2, y1, y2;

	int _dirAC = 0;
	int acS1, acS2, acS3, acS4, acS5 = 0;

  int arm_speed, t;

  PlaySound(soundUpwardTones);

	init();
	init_arm_pos();
	PlaySound(soundBeepBeep);
  while (true)
  {
    // process self defined timer
    t=time1[timer_R2_sys];
    ClearTimer(timer_R2_sys);
    timer_left_arm=timer_left_arm+t;
    timer_right_arm=timer_right_arm+t;
    timer_protect_left_move=timer_protect_left_move+t;
    timer_protect_right_move=timer_protect_right_move+t;
    timer_o_c_hand=timer_o_c_hand+t;

  	// process angle sensor
  	arm_left_pos=get_arm_left_pos();
  	arm_right_pos=get_arm_right_pos();
    // process IR sensor
    _dirAC = HTIRS2readACDir(sensor_IR);
    if (_dirAC >= 0)
    {
    	if (HTIRS2readAllACStrength(sensor_IR, acS1, acS2, acS3, acS4, acS5 ))
    	{
				nxtDisplayTextLine(1, "IR:%d", _dirAC);
		    //displayText(2, "0", dcS1, acS1);
		    //displayText(3, "1", dcS2, acS2);
		    //displayText(4, "2", dcS3, acS3);
		    //displayText(5, "3", dcS4, acS4);
		    //displayText(6, "4", dcS5, acS5);
    	}
    };
		// process joystick control

    getJoystickSettings(joystick);
    nxtDisplayTextLine(0, "L%3dR%3dB%2dT%4d",arm_left_pos ,arm_right_pos,joystick.joy1_Buttons, timer_left_arm);

    // robot move
    if (timer_protect_left_move>2000) timer_protect_left_move=2000;
    if (timer_protect_right_move>2000) timer_protect_right_move=2000;
    if (timer_o_c_hand>2000) timer_o_c_hand=2000;
    if ((!joy1Btn(JOY_BUTTON_J1_CLICK)) & (!joy1Btn(JOY_BUTTON_J2_CLICK)))
    {
	    if (joy1Btn(JOY_BUTTON_B))
	      ang=-15;
	    else if (joy1Btn(JOY_BUTTON_X))
	      ang=15;
	    else
	      ang=0;

	    if (abs(joystick.joy1_y2)<100) // ignore conflict with turbo speed
	    {
		    x=joystick.joy1_x2;
		    if (abs(x)>3)
		      ang = round((x/128.0)*30);
		  };

	    x=joystick.joy1_x1;
	    y=joystick.joy1_y1;
	    x=round(x/128.0*100);
	    y=round(y/128.0*100);

	    if ((abs(x)<3) & (abs(y)<3) & (abs(ang)==0))
	    {
	      int speed=40;
	      if (joystick.joy1_y2>100) speed=80;
	      if (joystick.joy1_y2<-100) speed=20;

		    switch(joystick.joy1_TopHat)
		    {
		      case JOY_BUTTON_TOPHAT_UP:        x=0;        y=speed;    break;
		      case JOY_BUTTON_TOPHAT_UP_RIGHT:  x=speed;    y=speed;    break;
		      case JOY_BUTTON_TOPHAT_RIGHT:     x=speed;    y= 0;       break;
		      case JOY_BUTTON_TOPHAT_DOWN_RIGHT:x=speed;    y=-speed;   break;
		      case JOY_BUTTON_TOPHAT_DOWN:      x=0;        y=-speed;   break;
		      case JOY_BUTTON_TOPHAT_DOWN_LEFT: x=-speed;   y=-speed;   break;
		      case JOY_BUTTON_TOPHAT_LEFT:      x=-speed;   y=0;        break;
		      case JOY_BUTTON_TOPHAT_UP_LEFT:   x=-speed;   y=speed;    break;
		      default: x=0; y=0; break;
		    };
		  };
		  if (timer_protect_left_move<1000) {x=0; y=0; ang=0;};
		  if (timer_protect_right_move<1000) {x=0; y=0; ang=0;};
		  RunAt(x, y, ang);
		}
		else
		  RunAt(0, 0, 0);


    // HAND MICRO MOVE back & forth
    if (joy1Btn(JOY_BUTTON_J1_CLICK)) {y1=joystick.joy1_y1; timer_protect_left_move=0;} else y1=0;
    if (joy1Btn(JOY_BUTTON_J2_CLICK))	{y2=joystick.joy1_y2; timer_protect_right_move=0;} else y2=0;

		if (left_hand_pos == HAND_GUA)
		  servo_left_hand_top_MoveToDeg(HAND_LEFT_TOP_GUA_ANG+round(y1*30/128), SERVO_SPEED_SLOW);
		if (right_hand_pos == HAND_GUA)
		  servo_right_hand_top_MoveToDeg(HAND_RIGHT_TOP_GUA_ANG+round(y2*30/128), SERVO_SPEED_SLOW);


		// open/close hand
    if ((joy1Btn(JOY_BUTTON_Y)) & (timer_o_c_hand>300))
    {
      timer_o_c_hand=0;
   		if (arm_left_pos>ARM_LEFT_SAFE_POS)
   		{
				if (left_hand_pos == HAND_JIE)
					hand_left_gua();
				else
					hand_left_jie();
	    };
   		if (arm_right_pos>ARM_RIGHT_SAFE_POS)
   		{
				if (right_hand_pos == HAND_JIE)
					hand_right_gua();
				else
					hand_right_jie();
		  };
	  };
		// HAND  roll
		if (arm_left_pos>ARM_LEFT_SAFE_POS)
		{
      if (joy1Btn(JOY_BUTTON_J1_CLICK)) x1=joystick.joy1_x1; else x1=0;
			if (left_hand_pos == HAND_JIE)
			  servo_left_hand_bottom_MoveToDeg(HAND_LEFT_BOTTOM_JIE_ANG+round(-x1*90/128), SERVO_SPEED_SLOW);
			else
			  servo_left_hand_bottom_MoveToDeg(HAND_LEFT_BOTTOM_GUA_ANG+round(-x1*90/128), SERVO_SPEED_SLOW);
			if (x1!=0)
			{
				if ((x1>120) || (x1<-120))
				{
					if (time1[timer_left_hand_roll]>1000)
					{
						if (left_hand_pos == HAND_JIE)
							hand_left_gua();
						else
							hand_left_jie();
						ClearTimer(timer_left_hand_roll);
					}
				} else
					ClearTimer(timer_left_hand_roll);
			} else
				ClearTimer(timer_left_hand_roll);
	  };

		if (arm_right_pos>ARM_LEFT_SAFE_POS)
		{
      if (joy1Btn(JOY_BUTTON_J2_CLICK))	x2=joystick.joy1_x2; else x2=0;
			if (right_hand_pos == HAND_JIE)
			  servo_right_hand_bottom_MoveToDeg(HAND_RIGHT_BOTTOM_JIE_ANG+round(x2*90/128), SERVO_SPEED_SLOW);
			else
			  servo_right_hand_bottom_MoveToDeg(HAND_RIGHT_BOTTOM_GUA_ANG+round(x2*90/128), SERVO_SPEED_SLOW);
			if (x2!=0)
			{
				if ((x2>120) || (x2<-120))
				{
					if (time1[timer_right_hand_roll]>1000)
					{
						if (right_hand_pos == HAND_JIE)
							hand_right_gua();
						else
							hand_right_jie();
						ClearTimer(timer_right_hand_roll);
					}
				} else
					ClearTimer(timer_right_hand_roll);
			} else
				ClearTimer(timer_right_hand_roll);
	  };


    // clip arm control
    if ((arm_clip_pos==ARM_CLIP_RELEASE) & (time1[timer_clipping]>1000))  // weighting
    {
		  servo_clip_left_MoveToDeg(ARM_CLIP_RELEASE_ANG-round(get_left_ring_weight()/400.0*90), SERVO_SPEED_NORMAL);
		  servo_clip_right_MoveToDeg(ARM_CLIP_RELEASE_ANG-round(get_right_ring_weight()/400.0*90), SERVO_SPEED_NORMAL);
    };

    if(joy1Btn(JOY_BUTTON_A))
    {
      if ((arm_clip_pos==ARM_CLIP_RELEASE) || (arm_clip_pos==ARM_CLIP_PARK))
      {
        if (time1[timer_clipping]>1000)
        {
        	arm_pickup_clip ();
          ClearTimer(timer_clipping);
        }
      }
      else
      {
        if (time1[timer_clipping]>1000)
        {
          arm_pickup_release();
          ClearTimer(timer_clipping);
        };
      };
    };

    if ((!arm_left_up_pressed) & !joy1Btn(JOY_BUTTON_LT)
      & (!arm_left_down_pressed) & !joy1Btn(JOY_BUTTON_LB))  // detect click
      timer_left_arm=0;

    if (arm_left_up_pressed & !joy1Btn(JOY_BUTTON_LT))
    {
      // set move target of left arm
      if (timer_left_arm<BUTTON_CLICK_DELAY)
        left_arm_move_up_one_level();
      arm_left_up_pressed=false;
    };

    if (arm_left_down_pressed & !joy1Btn(JOY_BUTTON_LB))
    {
      // set move target of left arm
      if (timer_left_arm<BUTTON_CLICK_DELAY)
        left_arm_move_down_one_level();
      arm_left_down_pressed=false;
    };

    // LEFT ARM UP
	  if(joy1Btn(JOY_BUTTON_LT)  & (arm_left_pos<ARM_LEFT_MAX))
	  {
	    arm_left_up_pressed=true;
	    arm_left_moving_up_to_target=false;
	    arm_left_moving_down_to_target=false;
	    if (timer_left_arm>BUTTON_CLICK_DELAY)
	    {
		  	arm_speed=100;
		  	if ((ARM_LEFT_MAX-arm_left_pos)<500) motor[arm_motor_left]=40;
		  	if ((ARM_LEFT_MAX-arm_left_pos)<400) motor[arm_motor_left]=30;
		  	if ((ARM_LEFT_MAX-arm_left_pos)<300) motor[arm_motor_left]=20;
		  	if ((ARM_LEFT_MAX-arm_left_pos)<200) motor[arm_motor_left]=10;
				arm_left_up(arm_speed);

		  	//if ((left_hand_pos == HAND_JIE) & (arm_left_pos>ARM_LEFT_OPEN_POS)) disable hand auto open
		  	//	hand_left_gua();
		  };
	  }
	  else if(joy1Btn(JOY_BUTTON_LB) & (arm_left_pos>ARM_LEFT_MIN))  // LEFT ARM DOWN
	  {
	    arm_left_down_pressed=true;
	    arm_left_moving_up_to_target=false;
	    arm_left_moving_down_to_target=false;
	    if (timer_left_arm>BUTTON_CLICK_DELAY)
	    {
		  	arm_speed=50;
		  	if ((arm_left_pos-ARM_LEFT_MIN)<500) motor[arm_motor_left]=20;
		  	if ((arm_left_pos-ARM_LEFT_MIN)<400) motor[arm_motor_left]=15;
		  	if ((arm_left_pos-ARM_LEFT_MIN)<300) motor[arm_motor_left]=10;
		  	if ((arm_left_pos-ARM_LEFT_MIN)<200) motor[arm_motor_left]=10;

		  	//if ((left_hand_pos == HAND_GUA) & (arm_left_pos<ARM_LEFT_SAFE_POS+200))
		  	//	hand_left_jie();

		  	if (!is_arm_left_touch_bottom())
					arm_left_down(arm_speed);
				else
					arm_left_stop();
		  };
    }
    else
			arm_left_stop();

    if (arm_left_moving_up_to_target)
    {
      if (arm_left_pos<arm_left_target)
		  	arm_left_up(50);
      else
      {
        arm_left_stop();
        arm_left_moving_up_to_target=false;
      };
    };

    if (arm_left_moving_down_to_target)
    {
      if (arm_left_pos>arm_left_target)
		  	arm_left_down(20);
      else
      {
        arm_left_stop();
        arm_left_moving_down_to_target=false;
      };
    };


    if ((!arm_right_up_pressed) & !joy1Btn(JOY_BUTTON_RT)
      & (!arm_right_down_pressed) & !joy1Btn(JOY_BUTTON_RB))  // detect click
      timer_right_arm=0;

    if (arm_right_up_pressed & !joy1Btn(JOY_BUTTON_RT))
    {
      // set move target of right arm
      if (timer_right_arm<BUTTON_CLICK_DELAY)
        right_arm_move_up_one_level();
      arm_right_up_pressed=false;
    };

    if (arm_right_down_pressed & !joy1Btn(JOY_BUTTON_RB))
    {
      // set move target of right arm
      if (timer_right_arm<BUTTON_CLICK_DELAY)
        right_arm_move_down_one_level();
      arm_right_down_pressed=false;
    };


    if(joy1Btn(JOY_BUTTON_RT) & (arm_right_pos<ARM_RIGHT_MAX))    // RIGHT ARM UP
    {
	    arm_right_up_pressed=true;
	    arm_right_moving_up_to_target=false;
	    arm_right_moving_down_to_target=false;
	    if (timer_right_arm>BUTTON_CLICK_DELAY)
	    {
		  	arm_speed=100;
		  	if ((ARM_RIGHT_MAX-arm_right_pos)<500) motor[arm_motor_right]=40;
		  	if ((ARM_RIGHT_MAX-arm_right_pos)<400) motor[arm_motor_right]=30;
		  	if ((ARM_RIGHT_MAX-arm_right_pos)<300) motor[arm_motor_right]=20;
		  	if ((ARM_RIGHT_MAX-arm_right_pos)<200) motor[arm_motor_right]=10;
		  	arm_right_up(arm_speed);

		  	//if ((right_hand_pos == HAND_JIE) & (arm_right_pos>ARM_RIGHT_OPEN_POS+200))
		  	//	hand_right_gua();
		  };
	  }
	  else if(joy1Btn(JOY_BUTTON_RB) & (arm_right_pos>ARM_RIGHT_MIN))   // RIGHT ARM DOWN
	  {
	    arm_right_down_pressed=true;
	    arm_right_moving_up_to_target=false;
	    arm_right_moving_down_to_target=false;
	    if (timer_right_arm>BUTTON_CLICK_DELAY)
	    {
	 	  	arm_speed=50;
		  	if ((arm_right_pos-ARM_RIGHT_MIN)<500) motor[arm_motor_right]=20;
		  	if ((arm_right_pos-ARM_RIGHT_MIN)<400) motor[arm_motor_right]=15;
		  	if ((arm_right_pos-ARM_RIGHT_MIN)<300) motor[arm_motor_right]=15;
		  	if ((arm_right_pos-ARM_RIGHT_MIN)<200) motor[arm_motor_right]=10;

		  	//if ((right_hand_pos == HAND_GUA) & (arm_right_pos<ARM_RIGHT_SAFE_POS))
		  	//	hand_right_jie();

		  	if (!is_arm_right_touch_bottom())
					arm_right_down(arm_speed);
				else
					arm_right_stop();
		  };
    }
    else
			arm_right_stop();

    if (arm_right_moving_up_to_target)
    {
      if (arm_right_pos<arm_right_target)
		  	arm_right_up(50);
      else
      {
        arm_right_stop();
        arm_right_moving_up_to_target=false;
      };
    };

    if (arm_right_moving_down_to_target)
    {
      if (arm_right_pos>arm_right_target)
		  	arm_right_down(20);
      else
      {
        arm_right_stop();
        arm_right_moving_down_to_target=false;
      };
    };
	}
}
