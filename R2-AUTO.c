
void auto_right()
	{
		motor[nxtmotor_JSG] = 0;
  	nMotorEncoder[nxtmotor_JSG] = 0;
		motor[nxtmotor_JSG] = 30;
		wait1Msec(300);
		motor[nxtmotor_JSG] = 0;
		wait1Msec(10);
		motor[nxtmotor_JSG] = 0;
  	motor[nxtmotor_flapper_left]=30;
		motor[nxtmotor_flapper_right]=30;
		wait1Msec(500);
		motor[nxtmotor_flapper_left]=-30;
		motor[nxtmotor_flapper_right]=-30;
		wait1Msec(150);
		motor[nxtmotor_flapper_left]=0;
		motor[nxtmotor_flapper_right]=0;
		wait1Msec(100);
		nMotorEncoder[nxtmotor_JSG] = 0;
		motor[nxtmotor_JSG] = -30;
		wait1Msec(300);
		motor[nxtmotor_JSG] = 0;
		wait1Msec(10);
		motor[nxtmotor_JSG] = 0;
  	nMotorEncoder[nxtmotor_JSG] = 0;
		motor[nxtmotor_JSG] = 30;
		wait1Msec(300);
		motor[nxtmotor_JSG] = 0;
		wait1Msec(10);
		motor[nxtmotor_JSG] = 0;
  	nMotorEncoder[nxtmotor_JSG] = 0;
		motor[nxtmotor_JSG] = -30;
		wait1Msec(300);
		motor[nxtmotor_JSG] = 0;
		wait1Msec(10);
		RunAt(40,0,0);
		wait1Msec(1000);
	  RunAt(0,0,-30);
	  wait1Msec(300);
	  RunAt(0,50,0);
	  wait1Msec(2000);
		RunAt(-30,0,0);
	  wait1Msec(500);
		RunAt(0,50,0);
		wait1Msec(1000);
		RunAt(30,0,0);
		wait1Msec(420);
		RunAt(0,50,0);
		wait1Msec(1000);
		RunAt(0,0,30);
		wait1Msec(290);
		RunAt(0,0,0);
		wait1Msec(10);
	}

void auto_middle()
	{
		motor[nxtmotor_JSG] = 0;
  	nMotorEncoder[nxtmotor_JSG] = 0;
		motor[nxtmotor_JSG] = 30;
		wait1Msec(300);
		motor[nxtmotor_JSG] = 0;
		wait1Msec(10);
		motor[nxtmotor_flapper_left]=30;
		motor[nxtmotor_flapper_right]=30;
		wait1Msec(500);
		motor[nxtmotor_flapper_left]=-30;
		motor[nxtmotor_flapper_right]=-30;
		wait1Msec(150);
		motor[nxtmotor_flapper_left]=0;
		motor[nxtmotor_flapper_right]=0;
		wait1Msec(100);
		motor[nxtmotor_JSG] = 0;
  	nMotorEncoder[nxtmotor_JSG] = 0;
		motor[nxtmotor_JSG] = -30;
		wait1Msec(300);
		motor[nxtmotor_JSG] = 0;
		wait1Msec(10);
		motor[nxtmotor_JSG] = 0;
  	nMotorEncoder[nxtmotor_JSG] = 0;
		motor[nxtmotor_JSG] = 30;
		wait1Msec(300);
		motor[nxtmotor_JSG] = 0;
		wait1Msec(10);
		motor[nxtmotor_JSG] = 0;
  	nMotorEncoder[nxtmotor_JSG] = 0;
		motor[nxtmotor_JSG] = -30;
		wait1Msec(300);
		motor[nxtmotor_JSG] = 0;
		wait1Msec(10);
		RunAt(-30,0,0);
		wait1Msec(400);
	  RunAt(0,50,0);
	  wait1Msec(800);
	  RunAt(0,0,-30);
	  wait1Msec(400);
		RunAt(0,50,0);
	  wait1Msec(1000);
		RunAt(30,0,0);
		wait1Msec(1000);
		RunAt(0,50,0);
		wait1Msec(500);
		RunAt(-30,0,0);
		wait1Msec(500);
		RunAt(0,30,0);
		wait1Msec(1000);
		RunAt(0,0,30);
		wait1Msec(150);
		RunAt(0,0,0);
		wait1Msec(10);

	}
	void auto_left()
	{
		motor[nxtmotor_JSG] = 0;
  	nMotorEncoder[nxtmotor_JSG] = 0;
		motor[nxtmotor_JSG] = -30;
		wait1Msec(300);
		motor[nxtmotor_JSG] = 0;
		wait1Msec(10);
		motor[nxtmotor_flapper_left]=30;
		motor[nxtmotor_flapper_right]=30;
		wait1Msec(500);
		motor[nxtmotor_flapper_left]=-30;
		motor[nxtmotor_flapper_right]=-30;
		wait1Msec(150);
		motor[nxtmotor_flapper_left]=0;
		motor[nxtmotor_flapper_right]=0;
		wait1Msec(100);
		motor[nxtmotor_JSG] = 0;
  	nMotorEncoder[nxtmotor_JSG] = 0;
		motor[nxtmotor_JSG] = -30;
		wait1Msec(300);
		motor[nxtmotor_JSG] = 0;
		wait1Msec(10);
		motor[nxtmotor_JSG] = 0;
  	nMotorEncoder[nxtmotor_JSG] = 0;
		motor[nxtmotor_JSG] = 30;
		wait1Msec(300);
		motor[nxtmotor_JSG] = 0;
		wait1Msec(10);
		motor[nxtmotor_JSG] = 0;
  	nMotorEncoder[nxtmotor_JSG] = 0;
		motor[nxtmotor_JSG] = -30;
		wait1Msec(300);
		motor[nxtmotor_JSG] = 0;
		wait1Msec(10);
		RunAt(-30,0,0);
		wait1Msec(400);
	  RunAt(0,50,0);
	  wait1Msec(800);
	  RunAt(0,0,-30);
	  wait1Msec(400);
		RunAt(0,50,0);
	  wait1Msec(1000);
		RunAt(-30,0,0);
		wait1Msec(1000);
		RunAt(0,50,0);
		wait1Msec(500);
		RunAt(30,0,0);
		wait1Msec(500);
		RunAt(0,30,0);
		wait1Msec(1000);
		RunAt(0,0,-30);
		wait1Msec(150);
		RunAt(0,0,0);
		wait1Msec(10);

	}

void AutoRun()
{
	int hongwai;
	int left_arm_pos;
	int right_arm_pos;
	left_arm_pos=get_arm_left_pos();
	right_arm_pos=get_arm_right_pos();
	hongwai=get_IR_direction();
	RunAt(0,100,0);
	wait1Msec(1050);
	RunAt(50,50,0);
	wait1Msec(200);
	RunAt(0,100,0);
	wait1Msec(2000);
	RunAt(0,0,0);
	wait1Msec(10);
	hongwai=get_IR_direction();
	if((hongwai==3) || (hongwai==4))
	{
		auto_middle();
		while(right_arm_pos<2000)
		{
			arm_right_up(100);
			right_arm_pos=get_arm_right_pos();
		}
		arm_right_stop();
		servo_right_hand_top_MoveToDeg(HAND_RIGHT_TOP_GUA_ANG,SERVO_SPEED_NORMAL);
		servo_right_hand_bottom_MoveToDeg(HAND_RIGHT_BOTTOM_GUA_ANG,SERVO_SPEED_NORMAL);
		wait1Msec(2000);
		while(right_arm_pos>600)
		{
			arm_right_down(100);
			right_arm_pos=get_arm_right_pos();
		}
		arm_right_stop();
		servo_right_hand_top_MoveToDeg(HAND_RIGHT_TOP_JIE_ANG,SERVO_SPEED_NORMAL);
		servo_right_hand_bottom_MoveToDeg(HAND_RIGHT_BOTTOM_JIE_ANG,SERVO_SPEED_NORMAL);
		wait1Msec(1000);
		while(right_arm_pos>50)
		{
			arm_right_down(100);
			right_arm_pos=get_arm_right_pos();
		}
		arm_right_stop();
	}
	else if((hongwai>4) && (hongwai<8))
	{
		auto_left();
		while(left_arm_pos<2000)
		{
			arm_left_up(100);
			left_arm_pos=get_arm_left_pos();
		}
		arm_left_stop();
		servo_left_hand_top_MoveToDeg(HAND_LEFT_TOP_GUA_ANG,SERVO_SPEED_NORMAL);
		servo_left_hand_bottom_MoveToDeg(HAND_LEFT_BOTTOM_GUA_ANG,SERVO_SPEED_NORMAL);
		wait1Msec(2000);
		while(left_arm_pos>600)
		{
			arm_left_down(100);
			left_arm_pos=get_arm_left_pos();
		}
		arm_left_stop();
		servo_left_hand_top_MoveToDeg(HAND_LEFT_TOP_JIE_ANG,SERVO_SPEED_NORMAL);
		servo_left_hand_bottom_MoveToDeg(HAND_LEFT_BOTTOM_JIE_ANG,SERVO_SPEED_NORMAL);
		wait1Msec(1000);
		while(left_arm_pos>50)
		{
			arm_left_down(100);
			left_arm_pos=get_arm_left_pos();
		}
		arm_left_stop();
	}
	else if((hongwai<=2)
	{
		auto_right();
		while(right_arm_pos<2000)
		{
			arm_right_up(100);
			right_arm_pos=get_arm_right_pos();
		}
		arm_right_stop();
		servo_right_hand_top_MoveToDeg(HAND_RIGHT_TOP_GUA_ANG,SERVO_SPEED_NORMAL);
		servo_right_hand_bottom_MoveToDeg(HAND_RIGHT_BOTTOM_GUA_ANG,SERVO_SPEED_NORMAL);
		wait1Msec(2000);
		while(right_arm_pos>600)
		{
			arm_right_down(100);
			right_arm_pos=get_arm_right_pos();
		}
		arm_right_stop();
		servo_right_hand_top_MoveToDeg(HAND_RIGHT_TOP_JIE_ANG,SERVO_SPEED_NORMAL);
		servo_right_hand_bottom_MoveToDeg(HAND_RIGHT_BOTTOM_JIE_ANG,SERVO_SPEED_NORMAL);
		wait1Msec(1000);
		while(right_arm_pos>50)
		{
			arm_right_down(100);
			right_arm_pos=get_arm_right_pos();
		}
		arm_right_stop();

	}
}
