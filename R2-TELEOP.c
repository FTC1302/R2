
void TeleOp()
{
  int x, y, ang;
  int arm_speed, t;
  while (true)
  {
    // process self defined timer
    t=time1[timer_R2_sys];
    ClearTimer(timer_R2_sys);
    timer_flipping=timer_flipping+t;
    timer_JOY2_BUTTON_X=timer_JOY2_BUTTON_X+t;
    timer_JOY2_BUTTON_B=timer_JOY2_BUTTON_B+t;


    // process angle sensor
   arm_left_pos=get_arm_left_pos();
   arm_right_pos=get_arm_right_pos();

    // process joystick control

    getJoystickSettings(joystick);
    nxtDisplayTextLine(0, "L%3dR%3dB%2d",arm_left_pos ,arm_right_pos,joystick.joy1_Buttons);

    if (timer_flipping>2000) timer_flipping=2000;
    if (timer_JOY2_BUTTON_X>2000) timer_JOY2_BUTTON_X=2000;
    if (timer_JOY2_BUTTON_B>2000) timer_JOY2_BUTTON_B=2000;


    // robot move
    x=0; y=0; ang=0;
    if (joy1Btn(JOY_BUTTON_B))
      ang=-15;
    else if (joy1Btn(JOY_BUTTON_X) )
      ang=15;
    else
      ang=0;

    if (abs(joystick.joy1_y2)<100) // ignore conflict with turbo speed
    {
			x=-joystick.joy1_x2;
			if (abs(x)>JOYSTICK_ERROR)
			ang = round((x/128.0)*30);
		};

    x=joystick.joy1_x1;
    y=joystick.joy1_y1;
    x=round(x/128.0*100);
    y=round(y/128.0*100);
    if (abs(x)<JOYSTICK_ERROR) x=0;
    if (abs(y)<JOYSTICK_ERROR) y=0;

    if ((x==0) & (y==0) & (ang==0))
    {
      int speed=40;
			switch(joystick.joy1_TopHat)
			{
				case JOY_BUTTON_TOPHAT_UP: x=0; y=speed; break;
				case JOY_BUTTON_TOPHAT_UP_RIGHT: x=speed; y=speed; break;
				case JOY_BUTTON_TOPHAT_RIGHT: x=speed; y= 0; break;
				case JOY_BUTTON_TOPHAT_DOWN_RIGHT:x=speed; y=-speed; break;
				case JOY_BUTTON_TOPHAT_DOWN: x=0; y=-80; break;
				case JOY_BUTTON_TOPHAT_DOWN_LEFT: x=-speed; y=-speed; break;
				case JOY_BUTTON_TOPHAT_LEFT: x=-speed; y=0; break;
				case JOY_BUTTON_TOPHAT_UP_LEFT: x=-speed; y=speed; break;
				default: x=0; y=0; break;
			};
		};
		RunAt(x, y, ang);


    // hand operation


		btn_pause_pressed=joy2Btn(JOY_BUTTON_PAUSE);
		btn_start_pressed=joy2Btn(JOY_BUTTON_START);

		if (btn_pause_pressed)
		{
			if (arm_left_pos>ARM_LEFT_SAFE_POS)
				servo_left_hand_top_MoveToDeg(HAND_LEFT_TOP_RENG_ANG, SERVO_SPEED_NORMAL);
		}
		else if (last_btn_pause_pressed)
		{
			if (arm_left_pos>ARM_LEFT_SAFE_POS)
				servo_left_hand_top_MoveToDeg(HAND_LEFT_TOP_JIE_ANG, SERVO_SPEED_NORMAL);
		};

		if (btn_start_pressed)
		{
			if (arm_right_pos>ARM_RIGHT_SAFE_POS)
				servo_right_hand_top_MoveToDeg(HAND_RIGHT_TOP_RENG_ANG, SERVO_SPEED_NORMAL);
		}
		else if (last_btn_start_pressed)
		{
			if (arm_right_pos>ARM_RIGHT_SAFE_POS)
				servo_right_hand_top_MoveToDeg(HAND_RIGHT_TOP_JIE_ANG, SERVO_SPEED_NORMAL);
		};

		last_btn_pause_pressed=btn_pause_pressed;
		last_btn_start_pressed=btn_start_pressed;

    if (joy2Btn(JOY_BUTTON_Y) & (arm_left_pos>ARM_LEFT_SAFE_POS) & (arm_right_pos>ARM_RIGHT_SAFE_POS))
    {
      hand_all_close();
      left_hand_bottom_pos=HAND_CLOSE;
      right_hand_bottom_pos=HAND_CLOSE;
    };

    if (joy2Btn(JOY_BUTTON_A) & (arm_left_pos>ARM_LEFT_SAFE_POS)& (arm_right_pos>ARM_RIGHT_SAFE_POS))
    {
      hand_all_open();
      left_hand_bottom_pos=HAND_OPEN;
      right_hand_bottom_pos=HAND_OPEN;
    };

    if ((joy2Btn(JOY_BUTTON_X)) & (arm_left_pos>ARM_LEFT_SAFE_POS))
    {
      if (timer_JOY2_BUTTON_X>300){
        if (left_hand_bottom_pos==HAND_CLOSE)
        {
          servo_left_hand_bottom_MoveToDeg(HAND_LEFT_BOTTOM_GUA_ANG, SERVO_SPEED_NORMAL);
          left_hand_bottom_pos=HAND_OPEN;
        }
        else
        {
          servo_left_hand_bottom_MoveToDeg(HAND_LEFT_BOTTOM_JIE_ANG, SERVO_SPEED_NORMAL);
          servo_left_hand_top_MoveToDeg(HAND_LEFT_TOP_JIE_ANG, SERVO_SPEED_NORMAL);
          left_hand_bottom_pos=HAND_CLOSE;
        };
        timer_JOY2_BUTTON_X=0;
      };
    };

    if ((joy2Btn(JOY_BUTTON_B)) & (arm_right_pos>ARM_LEFT_SAFE_POS))
    {
      if (timer_JOY2_BUTTON_B>300){
        if (right_hand_bottom_pos==HAND_CLOSE)
        {
          servo_right_hand_bottom_MoveToDeg(HAND_LEFT_BOTTOM_GUA_ANG, SERVO_SPEED_NORMAL);
          right_hand_bottom_pos=HAND_OPEN;
        }
        else
        {
          servo_right_hand_bottom_MoveToDeg(HAND_RIGHT_BOTTOM_JIE_ANG, SERVO_SPEED_NORMAL);
          servo_right_hand_top_MoveToDeg(HAND_RIGHT_TOP_JIE_ANG, SERVO_SPEED_NORMAL);
          right_hand_bottom_pos=HAND_CLOSE;
        };
        timer_JOY2_BUTTON_B=0;
      };
    };

    if (joy2Btn(JOY_BUTTON_LB) & (arm_left_pos>ARM_LEFT_SAFE_POS))
      servo_left_hand_top_MoveToDeg(HAND_LEFT_TOP_GUA_ANG, SERVO_SPEED_NORMAL);

    if (joy2Btn(JOY_BUTTON_LT) & (arm_left_pos>ARM_LEFT_SAFE_POS))
      servo_left_hand_top_MoveToDeg(HAND_LEFT_TOP_YUN_ANG, SERVO_SPEED_NORMAL);

    if (joy2Btn(JOY_BUTTON_RB) & (arm_right_pos>ARM_RIGHT_SAFE_POS))
      servo_right_hand_top_MoveToDeg(HAND_RIGHT_TOP_GUA_ANG, SERVO_SPEED_NORMAL);

    if (joy2Btn(JOY_BUTTON_RT) & (arm_right_pos>ARM_RIGHT_SAFE_POS))
      servo_right_hand_top_MoveToDeg(HAND_RIGHT_TOP_YUN_ANG, SERVO_SPEED_NORMAL);



    // clip arm control
    if ((arm_clip_pos==ARM_CLIP_HORIZON) & (time1[timer_clipping]>300)) // weighting
    {
			servo_clip_left_MoveToDeg(ARM_CLIP_HORIZON_ANG-round(get_left_ring_weight()/400.0*60), SERVO_SPEED_NORMAL);
			servo_clip_right_MoveToDeg(ARM_CLIP_HORIZON_ANG-round(get_right_ring_weight()/400.0*60), SERVO_SPEED_NORMAL);
    };

    if (nMotorRunState[nxtmotor_flapper_left] == runStateIdle )
       motor[nxtmotor_flapper_left] = 0;

    if (nMotorRunState[nxtmotor_flapper_right] == runStateIdle )
       motor[nxtmotor_flapper_right] = 0;

    if(joy1Btn(JOY_BUTTON_RT))
    {
      arm_pickup_horizon();
    }

    if(joy1Btn(JOY_BUTTON_RB))
    {
      arm_pickup_park();
    }
    else if(joy1Btn(JOY_BUTTON_A))
    {
      if ((arm_clip_pos==ARM_CLIP_CLIP) || (arm_clip_pos==ARM_CLIP_HORIZON)|| (arm_clip_pos==ARM_CLIP_PARK))
      {
        if (time1[timer_clipping]>300)
        {
         arm_pickup_release();
          ClearTimer(timer_clipping);
        }
      }
      else
      {
        if (time1[timer_clipping]>300)
        {
          arm_pickup_clip();
          ClearTimer(timer_clipping);
        };
      };
    };

    if(joy1Btn(JOY_BUTTON_Y) & (arm_left_pos<ARM_LEFT_STOP_FLAPPER_POS) & (arm_right_pos<ARM_RIGHT_STOP_FLAPPER_POS))
    {
      if ((flipper_pos==FLIPPER_DOWN))
      {
        if (timer_flipping>300)
        {
         flipper_up();
          timer_flipping=0;
        }
      }
      else
      {
        if (timer_flipping>300)
        {
          flipper_down();
          timer_flipping=0;
        };
      };
    };

    //JSG control
    switch(joystick.joy2_TopHat)
    {
      case JOY_BUTTON_TOPHAT_RIGHT:
        motor[nxtmotor_JSG]=30;
      break;
      case JOY_BUTTON_TOPHAT_LEFT:
        motor[nxtmotor_JSG]=-30;
      break;
			default:
			  motor[nxtmotor_JSG]=0;
			break;
	  };

	/*
	int JSG_POWER=30;
	if (JSG_target>0)
	{
	if (nMotorEncoder[nxtmotor_JSG]<JSG_target)
	motor[nxtmotor_JSG]=JSG_POWER
	else
	motor[nxtmotor_JSG]=0;
	}
	else if (JSG_target<0)
	{
	if (nMotorEncoder[nxtmotor_JSG]>JSG_target)
	motor[nxtmotor_JSG]=-JSG_POWER
	else
	motor[nxtmotor_JSG]=0;
	}
	else {
	if (motor[nxtmotor_JSG]<-15)
	motor[nxtmotor_JSG]=JSG_POWER
	else if ((motor[nxtmotor_JSG]>8)
	motor[nxtmotor_JSG]=-JSG_POWER
	else
	motor[nxtmotor_JSG]=0
	}
	*/

	    // LEFT ARM UP
	if (arm_left_pos > ARM_LEFT_STOP_FLAPPER_POS)
		flipper_down();

	if ( ((joystick.joy2_y1>5) ||  (joystick.joy2_TopHat==JOY_BUTTON_TOPHAT_UP)) & (arm_left_pos<ARM_LEFT_MAX) )
	{
		if ((arm_left_pos>100) & (left_hand_bottom_pos == HAND_CLOSE))
		  servo_left_hand_top_MoveToDeg(HAND_LEFT_TOP_YUN_ANG, SERVO_SPEED_NORMAL);

		arm_speed=round(joystick.joy2_y1/128*100);
		if ((abs(arm_speed)<5) & ( joystick.joy2_TopHat==JOY_BUTTON_TOPHAT_UP))
			arm_speed=100;
		arm_left_up(arm_speed);
	}
	else if ( ((joystick.joy2_y1<-5) || ( joystick.joy2_TopHat==JOY_BUTTON_TOPHAT_DOWN)) & (arm_left_pos>ARM_LEFT_MIN)) // LEFT ARM DOWN
	{
		if ((arm_left_pos<300) & (left_hand_bottom_pos == HAND_CLOSE))
	  	servo_left_hand_top_MoveToDeg(HAND_LEFT_TOP_JIE_ANG, SERVO_SPEED_NORMAL);

		arm_speed=abs(round(joystick.joy2_y1/128.0*100));
		if ((abs(arm_speed)<5) & ( joystick.joy2_TopHat==JOY_BUTTON_TOPHAT_DOWN))
			arm_speed=70;
		if (!is_arm_left_touch_bottom())
		  arm_left_down(arm_speed);
		else
		  arm_left_stop();
	}
  else
	  arm_left_stop();


	if (arm_right_pos > ARM_RIGHT_STOP_FLAPPER_POS)
		flipper_down();

	if((joystick.joy2_y2>5) & (arm_right_pos<ARM_RIGHT_MAX)) // RIGHT ARM UP
	{
		if ((arm_right_pos>100) & (right_hand_bottom_pos == HAND_CLOSE))
			servo_right_hand_top_MoveToDeg(HAND_RIGHT_TOP_YUN_ANG, SERVO_SPEED_NORMAL);

		arm_speed=round(joystick.joy2_y2/128.0*100);
		arm_right_up(arm_speed);
  }
	else if((joystick.joy2_y2<-5) & (arm_right_pos>ARM_RIGHT_MIN)) // RIGHT ARM DOWN
	{
		if ((arm_right_pos<300) & (right_hand_bottom_pos == HAND_CLOSE))
		  servo_right_hand_top_MoveToDeg(HAND_RIGHT_TOP_JIE_ANG, SERVO_SPEED_NORMAL);

		arm_speed=-round(joystick.joy2_y2/128.0*100);
		if (!is_arm_right_touch_bottom())
		  arm_right_down(arm_speed);
		else
		  arm_right_stop();
	}
  else
		arm_right_stop();
  }
};
