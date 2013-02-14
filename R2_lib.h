/*
  Library function for FTC Team 1302 Robot R2
  2013-1
*/

///////////////////////////////////////////////////////////////////////////////////

void RunAt(float v_x, float v_y, float ang);  // x, y -1..+1  ang -180..+180
void servo_clip_left_MoveToDeg(float deg, int speed);  // -90-+90
void servo_clip_right_MoveToDeg(float  deg, int speed);
void servo_left_hand_bottom_MoveToDeg(float  deg, int speed);
void servo_left_hand_top_MoveToDeg(float  deg, int speed);
void servo_right_hand_bottom_MoveToDeg(float  deg, int speed);
void servo_right_hand_top_MoveToDeg(float  deg, int speed);
void arm_pickup_park ();
void arm_pickup_clip ();
void arm_pickup_release ();

void arm_left_stop();
void arm_left_up(int speed);
void arm_left_down(int speed);
bool is_arm_left_touch_bottom();
int get_arm_left_pos();

void arm_right_stop();
void arm_right_up(int speed);
void arm_right_down(int speed);
bool is_arm_right_touch_bottom();
int get_arm_right_pos();

void hand_left_jie();
void hand_left_gua();

void hand_right_gua();
void hand_right_jie();


///////////////////////////////////////////////////////////////////////////////////

void RunAt(float v_x, float v_y, float ang)  // x, y -1..+1  ang -180..+180
{
	float R, A	;

	if (v_x < -70) { v_x = -70;};
	if (v_x >  70) { v_x = 70;};
	if (v_y < -70) { v_y = -70;};
	if (v_y >  70) { v_y = 70;};
	if (ang < -30) { v_x = -30;};
	if (ang >  30) { v_x = 30;};

  if((abs(v_x)>2) || (abs(v_y)>2)){
    if(v_x!=0)
	    A=atan(v_y/v_x)/PI*180;
	  else
	  {
	    if (v_y>0) A=90; else A=-90;
	  };
	  if (v_x<0) A=A+180;
    A=A+135;
    R=sqrt(v_x*v_x+v_y*v_y);
    v_x=R*cosDegrees(A);
    v_y=R*sinDegrees(A);
  }
  else {
    v_x=0;
    v_y=0;
  };

	if (abs(v_x)<=1) { v_x = 0; };
	if (abs(v_y)<=1) { v_y = 0; };
	if (abs(ang)<=1) { ang = 0; };

	motor[drive_motor_1]=v_x+ang;
	motor[drive_motor_2]=v_y+ang;
	motor[drive_motor_3]=-(v_x-ang);
	motor[drive_motor_4]=-(v_y-ang);
}


void RunAt_old(float v_x, float v_y, float ang)  // x, y -1..+1  ang -180..+180
{
	float v1, v2, v3, v4	;

	if (v_x < -100) { v_x = -100;};
	if (v_x >  100) { v_x = 100;};
	if (v_y < -100) { v_y = -100;};
	if (v_y >  100) { v_y = 100;};
	if (ang < -180) { v_x = -180;};
	if (ang >  180) { v_x = 180;};

	if (abs(v_x)<15) { v_x = 0; };
	if (abs(v_y)<15) { v_y = 0; };
	if (abs(ang)<15) { ang = 0; };

	v_x=v_x / 100;
	v_y=v_y / 100;

	ang=ang/180.0*PI;
  ////////////////////////////////////////////
	float R=0.23;
  float l=0.5;
  float O1=0/180.0*PI;
  float O2=90/180.0*PI;
  float O3=180/180.0*PI;
  float O4=270/180.0*PI;

  v1=(R*cos(O1)/l*v_x) - (R*sin(O1)/l*v_y)+R*ang;
  v2=(R*cos(O2)/l*v_x) - (R*sin(O2)/l*v_y)+R*ang;
  v3=(R*cos(O3)/l*v_x) - (R*sin(O3)/l*v_y)+R*ang;
  v4=(R*cos(O4)/l*v_x) - (R*sin(O4)/l*v_y)+R*ang;
	/////////////////////////////////////////////////////
	motor[drive_motor_1]=round(v1*100);
	motor[drive_motor_2]=round(v2*100);
	motor[drive_motor_3]=round(v3*100);
	motor[drive_motor_4]=round(v4*100);
}


 void servo_clip_left_MoveToDeg(float deg, int speed)  // -90-+90
{
	int min=35;
	int max=258;
	int i;
	deg=deg+0;
	if (deg<0) deg=0;
	if (deg>180) deg=180;
	servoChangeRate[servo_clip_left]=speed;
	i=round(deg*(max-min)/180)+min;
	servo[servo_clip_left]=round(i);
};

void servo_clip_right_MoveToDeg(float  deg, int speed)
{
	int min=35;
	int max=255;
	int i;
	if (deg<0) deg=0;
	if (deg>180) deg=180;
	servoChangeRate[servo_clip_right]=speed;
	i=round(deg*(max-min)/180)+min;
	servo[servo_clip_right]=round(250-i);
};

void servo_left_hand_bottom_MoveToDeg(float  deg, int speed)
{
	int min=5;
	int max=250;
	int i;
	if (deg<0) deg=0;
	if (deg>180) deg=180;
	servoChangeRate[servo_left_hand_bottom]=speed;
	i=round(deg*(max-min)/180)+min;
	servo[servo_left_hand_bottom]=round(i);
};

void servo_left_hand_top_MoveToDeg(float deg, int speed)
{
	int min=3;
	int max=250;
	int i;
	if (deg<0) deg=0;
	if (deg>180) deg=180;
	servoChangeRate[servo_left_hand_top]=speed;
	i=round(deg*(max-min)/180)+min;
	servo[servo_left_hand_top]=round(255-i);
};

void servo_right_hand_bottom_MoveToDeg(float deg, int speed)
{
	int min=15;
	int max=255;
	int i;
	if (deg<0) deg=0;
	if (deg>180) deg=180;
	servoChangeRate[servo_right_hand_bottom]=speed;
	i=round(deg*(max-min)/180)+min;
	servo[servo_right_hand_bottom]=255-i;
};


void servo_right_hand_top_MoveToDeg(float deg, int speed)
{
	int min=3;
	int max=255;
	int i;
	if (deg<0) deg=0;
	if (deg>180) deg=180;
	servoChangeRate[servo_right_hand_top]=speed;
	i=round(deg*(max-min)/180)+min;
	servo[servo_right_hand_top]=i;
};

void arm_pickup_park ()
{
	servo_clip_left_MoveToDeg(140, SERVO_SPEED_VERY_SLOW);
	servo_clip_right_MoveToDeg(140, SERVO_SPEED_VERY_SLOW);
	arm_clip_pos=ARM_CLIP_PARK;
}
void arm_pickup_clip ()
{
	servo_clip_left_MoveToDeg(0, SERVO_SPEED_NORMAL);
	servo_clip_right_MoveToDeg(0, SERVO_SPEED_NORMAL);
	arm_clip_pos=ARM_CLIP_CLIP;

}
void arm_pickup_release ()
{
  servo_clip_left_MoveToDeg(90, SERVO_SPEED_NORMAL);
  servo_clip_right_MoveToDeg(90, SERVO_SPEED_NORMAL);
	arm_clip_pos=ARM_CLIP_RELEASE;
}

void arm_left_stop(){
		motor[arm_motor_left]=0;
}

void arm_left_up(int speed){
		motor[arm_motor_left]=-speed;
};

void arm_left_down(int speed){
		motor[arm_motor_left]=speed;
};


void hand_left_jie (){
	servo_left_hand_bottom_MoveToDeg(HAND_LEFT_BOTTOM_JIE_ANG, SERVO_SPEED_SLOW);
	servo_left_hand_top_MoveToDeg(HAND_LEFT_TOP_JIE_ANG, SERVO_SPEED_SLOW);
  left_hand_pos= HAND_JIE;
}

void hand_left_gua (){
  servo_left_hand_bottom_MoveToDeg(HAND_LEFT_BOTTOM_GUA_ANG, SERVO_SPEED_SLOW);
  servo_left_hand_top_MoveToDeg(HAND_LEFT_TOP_GUA_ANG, SERVO_SPEED_SLOW);
  left_hand_pos= HAND_GUA;
}

bool is_arm_left_touch_bottom(){
	int pb_io_stat;
	pb_io_stat= HTSPBreadIO(HTSPB, 0xff);
	if (pb_io_stat & 2) return true; else return false;
}


int get_arm_left_pos(){
	return HTANGreadAccumulatedAngle(sensor_arm_left_angle);
}

void left_arm_move_up_one_level(){
  arm_left_target=ARM_TARGET_LEVEL3;
  if (arm_left_pos<ARM_TARGET_LEVEL2) arm_left_target=ARM_TARGET_LEVEL2;
  if (arm_left_pos<ARM_TARGET_LEVEL1) arm_left_target=ARM_TARGET_LEVEL1;
  arm_left_moving_up_to_target=true;
};

void left_arm_move_down_one_level(){
  arm_left_target=ARM_TARGET_LEVEL1;
  if (arm_left_pos>ARM_TARGET_LEVEL2) arm_left_target=ARM_TARGET_LEVEL2;
  if (arm_left_pos>ARM_TARGET_LEVEL3) arm_left_target=ARM_TARGET_LEVEL3;
  arm_left_moving_down_to_target=true;
};

void right_arm_move_up_one_level(){
  arm_right_target=ARM_TARGET_LEVEL3;
  if (arm_right_pos<ARM_TARGET_LEVEL2) arm_right_target=ARM_TARGET_LEVEL2;
  if (arm_right_pos<ARM_TARGET_LEVEL1) arm_right_target=ARM_TARGET_LEVEL1;
  arm_right_moving_up_to_target=true;
};

void right_arm_move_down_one_level(){
  arm_right_target=ARM_TARGET_LEVEL1;
  if (arm_right_pos>ARM_TARGET_LEVEL2) arm_right_target=ARM_TARGET_LEVEL2;
  if (arm_right_pos>ARM_TARGET_LEVEL3) arm_right_target=ARM_TARGET_LEVEL3;
  arm_right_moving_down_to_target=true;
};

void arm_right_stop(){
	motor[arm_motor_right]=0;
}

void arm_right_up(int speed){
	motor[arm_motor_right]=speed;
};

void arm_right_down(int speed){
	motor[arm_motor_right]=-speed;
};

void hand_right_gua (){
  servo_right_hand_bottom_MoveToDeg(HAND_RIGHT_BOTTOM_GUA_ANG, SERVO_SPEED_SLOW);
  servo_right_hand_top_MoveToDeg(HAND_RIGHT_TOP_GUA_ANG, SERVO_SPEED_SLOW);
  right_hand_pos= HAND_GUA;
}

void hand_right_jie (){
  servo_right_hand_bottom_MoveToDeg(HAND_RIGHT_BOTTOM_JIE_ANG, SERVO_SPEED_SLOW);
  servo_right_hand_top_MoveToDeg(HAND_RIGHT_TOP_JIE_ANG, SERVO_SPEED_SLOW);
  right_hand_pos= HAND_JIE;

}

bool is_arm_right_touch_bottom(){
	int pb_io_stat;
	pb_io_stat= HTSPBreadIO(HTSPB, 0xff);
	if (pb_io_stat & 1) return true; else return false;
}

int get_arm_right_pos(){
	return -HTANGreadAccumulatedAngle(sensor_arm_right_angle);
}

void init_IR_sensor(){
  HTIRS2setDSPMode(sensor_IR, DSP_1200);
}

void init_prototype_board(){
  HTSPBsetupIO(HTSPB, 0x00);
}

void reset_angle_sensor(){
  // Reset Angle sensor
  HTANGresetAngle(sensor_arm_left_angle);
  HTANGresetAccumulatedAngle(sensor_arm_left_angle);
  HTANGresetAngle(sensor_arm_right_angle);
  HTANGresetAccumulatedAngle(sensor_arm_right_angle);

  arm_left_pos=0;
	arm_right_pos=0;
}
