Ring it UP!!!@FTC Team 1302 
===========================

FTC 1302 2013赛季： 参赛机器人R2 程序。

文件说明：
=========
/drivers 		: 角度传感器、红外线传感器及各种其他hitechnic传感器驱动程序所在目录

/prototype_drivers 	: 原型板驱动

R2_const.h		: 常数定义文件

R2_lib.h		: 库函数定义文件

R2_TELEOP.C 		: R2遥控阶段正式程序

以下为各种测试程序：

R2_SENSOR.C		: 传感器测试程序，程序运行后可以显示左右触碰，左右角度，左右称重和红外传感器的测量值。

R2_SERVO.C		: 测试伺服电机位置，左右机械手在接圈与挂圈位置切换

R2_TEST_PB.C


总体性说明：
===========
机器人的方向为【取圈臂在后，机械臂马达在前，所有的左右、前后均以此方向为基准】。



R2操作方法：
===========

开机
----

R2开机会先播放音乐声，然后将左右机械手置于接圈位置，取圈臂置于停机位置，然后等待两秒钟，等待伺服电机就位后，左右机械臂向下运动，直到左右触碰开关都被压住。这时的位置作为机械臂的起始位置，到位后发出“嘟嘟”声。

操作
----
手柄1//驾驶及取圈

	X	逆时针旋转

	B	逆时针旋转

	A	取圈臂夹/放

	Y	翻板反转

	LB

	LT

	RB

	RT

	J1(左)	全向运动控制

	J1_CLICK

	J2(右)	X方向控制旋转,Y方向推到头是加速TOPHAT运动。

	J2_CLICK

	TOPHAT	全向运动，速度为60



手柄2//挂圈

	X	逆时针旋转

	B	逆时针旋转

	A	取圈臂夹/放

	Y	翻板反转

	LB	左机械臂向下一层

	LT	左机械臂向上一层

	RB	右机械臂向下一层

	RT	右机械臂向上一层

	J1(左)	Y方向控制左机械臂上下

	J1_CLICK

	J2(右)	Y方向控制右机械臂上下

	J2_CLICK

	TOPHAT	全向运动，速度为60




端口定义：
=========
```C
#pragma config(Hubs,  	S1, 		HTMotor,  HTMotor,  HTMotor,  HTServo)  	// TETRIX控制器接在 NXT S1端口，
#pragma config(Sensor, 	S2,     	sensor_arm_left_angle, 	sensorI2CCustom)  	// 左机械臂的角度传感器
#pragma config(Sensor, 	S3,     	sensor_arm_right_angle, sensorI2CCustom)	// 右机械臂角度传感器
#pragma config(Sensor, 	S4,     	HTSPB,          	sensorI2CCustom9V)	// 原型板，扩充了两个触碰传感器和左右两个用于称重的压力传感器
#pragma config(Motor,  	mtr_S1_C1_1,    drive_motor_1, 		tmotorTetrix, openLoop)	// 运动马达1 【注意】运动马达顺序不能接错，否则全向轮算法会混乱。
#pragma config(Motor,  	mtr_S1_C1_2,    drive_motor_2, 		tmotorTetrix, openLoop)	// 运动马达2
#pragma config(Motor,  	mtr_S1_C2_1,    arm_motor_left, 	tmotorTetrix, openLoop)	// 左机械臂驱动马达
#pragma config(Motor,  	mtr_S1_C2_2,    arm_motor_right, 	tmotorTetrix, openLoop)	// 右机械臂马达
#pragma config(Motor,  	mtr_S1_C3_1,    drive_motor_3, 		tmotorTetrix, openLoop)	// 运动马达3
#pragma config(Motor,  	mtr_S1_C3_2,    drive_motor_4, 		tmotorTetrix, openLoop)	// 运动马达4
#pragma config(Servo,  	srvo_S1_C4_1,   servo_clip_left,      	tServoStandard)		// 取圈臂左侧伺服电机
#pragma config(Servo,  	srvo_S1_C4_2,   servo_clip_right,     	tServoStandard)		// 取圈臂右侧伺服电机
#pragma config(Servo,  	srvo_S1_C4_3,   servo_left_hand_bottom, tServoStandard)		// 左机械手底部伺服电机
#pragma config(Servo,  	srvo_S1_C4_4,   servo_left_hand_top,  	tServoStandard)		// 左机械手顶部伺服电机
#pragma config(Servo,  	srvo_S1_C4_5,   servo_right_hand_bottom, tServoStandard)	// 右机械手底部伺服电机
#pragma config(Servo,  	srvo_S1_C4_6,   servo_right_hand_top, 	tServoStandard)		// 右机械手顶部伺服电机
```


常数说明(R2-const.h)：
==================
```C
//游戏手柄常数，感谢罗罗的耐心和细心，把混乱的手柄代码搞清楚了。
X=01;
A=02;
B=03;
Y=04;
LB=05;
RB=06;
LT=07;
RT=08;
J1_CLICK=11;
J2_CLICK=12;
TOPHAT_UP= 0;
TOPHAT_UP_RIGHT= 1;
TOPHAT_RIGHT= 2;
TOPHAT_DOWN_RIGHT= 3;
TOPHAT_DOWN= 4;
TOPHAT_DOWN_LEFT= 5;
TOPHAT_LEFT= 6;
TOPHAT_UP_LEFT= 7;

//检测按钮“点击”（注意不是“按住”）的时间定义，这里定义的是300毫秒以内的算“点击”
const int BUTTON_CLICK_DELAY=300;


// 关于伺服电机的说明：
// 所有的伺服电机都调整为0-180度运动，方向根据需要按下面的定义设定：（顺时针/逆时针均为伺服电机轴面向自己时看到的方向）
// 1. 取圈臂左：顺时针/逆时针
// 2. 取圈臂右：顺时针/逆时针
// 3. 左机械手底部：顺时针
// 4. 左机械手顶部：逆时针
// 5. 右机械手底部：逆时针
// 6. 右机械手顶部：顺时针

//伺服电机移动速度常数,从非常快到非常慢，使用什么速度的主要考虑的因素是在不会把圈圈掉下来的情况下尽可能的快，有时候还要考虑不要让伺服电机之间打架。
const int SERVO_SPEED_VERY_SLOW	=	1;
const int SERVO_SPEED_SLOW	=	3;
const int SERVO_SPEED_NORMAL	=	5;
const int SERVO_SPEED_FAST	=	7;
const int SERVO_SPEED_VERY_FAST	=	9;


//左面的机械手参数定义，单位是角度（0度-180度）
const int HAND_LEFT_TOP_JIE_ANG=50;
const int HAND_LEFT_BOTTOM_JIE_ANG=5;
const int HAND_LEFT_TOP_GUA_ANG=110; //140;
const int HAND_LEFT_BOTTOM_GUA_ANG=180;

//右面的机械手参数定义
const int HAND_RIGHT_TOP_JIE_ANG=63;
const int HAND_RIGHT_BOTTOM_JIE_ANG=175;
const int HAND_RIGHT_TOP_GUA_ANG=110; //93;
const int HAND_RIGHT_BOTTOM_GUA_ANG=00;

//当前机械手状态定义，1=接圈的状态， 2=挂圈的状态
const int HAND_JIE = 1;
const int HAND_GUA = 2;


//取圈臂状态定义，1=停靠状态  2=准备夹的状态  3=已经夹住的状态
const int ARM_CLIP_PARK    = 1;
const int ARM_CLIP_RELEASE = 2;
const int ARM_CLIP_CLIP    = 3;

// 关于机械臂高度：高度值为安装在两个机械臂驱动马达轴上的角度传感器读出的累积角度值。

//左面机械臂的参数定义，分为最低位置，最高位置，安全位置，自动打开位置。
const int ARM_LEFT_MIN=10;
const int ARM_LEFT_MAX=2000;
const int ARM_LEFT_SAFE_POS=600;
const int ARM_LEFT_OPEN_POS=1000;

//左面机械臂的参数定义，分为最低位置，最高位置，安全位置，自动打开位置。
const int ARM_RIGHT_MIN=10;
const int ARM_RIGHT_MAX=2000;
const int ARM_RIGHT_SAFE_POS=600;
const int ARM_RIGHT_OPEN_POS=1000;

//定义左右机械臂自动移动到设定高度的高度值，对应三层衣架的高度。
const int ARM_TARGET_NONE   = -1;
const int ARM_TARGET_LEVEL1 = 800;
const int ARM_TARGET_LEVEL2 = 1200;
const int ARM_TARGET_LEVEL3 = 1600;
```


R2函数库说明(R2-lib.h)
======================
```C
void RunAt(float v_x, float v_y, float ang); 
// 设定R2的运动状态
// v_x: X轴方向的速度 -100 - +100
// v_y: Y轴方向的速度 -100 - +100
// ang: 自身旋转的角速度 -30 - +30
// 坐标系说明，机器人的右方为X轴正方向，前方为Y轴的正方向。


void servo_clip_left_MoveToDeg(float deg, int speed); 
void servo_clip_right_MoveToDeg(float  deg, int speed);
void servo_left_hand_bottom_MoveToDeg(float  deg, int speed);
void servo_left_hand_top_MoveToDeg(float  deg, int speed);
void servo_right_hand_bottom_MoveToDeg(float  deg, int speed);
void servo_right_hand_top_MoveToDeg(float  deg, int speed);
// 六个伺服电机的驱动函数
// deg  : 目标角度，范围是0-180
// speed: 移动速度，使用伺服电机运动速度常数


void arm_pickup_park ();
void arm_pickup_clip ();
void arm_pickup_release ();
// 取圈臂动作：停靠、夹取、释放三个位置。


void hand_left_jie();
void hand_left_gua();
// 命令左机械手移动到“接圈”或“挂圈”的位置。


void hand_right_gua();
void hand_right_jie();
// 命令右机械手移动到“接圈”或“挂圈”的位置。

void arm_left_stop();
// 命令左机械臂停止运动

void arm_left_up(int speed);
void arm_left_down(int speed);
// 命令左机械臂以速度“speed”向上或向下运动。

bool is_arm_left_touch_bottom();
// 返回左机械臂是否碰到底部的触碰传感器。

int get_arm_left_pos();
// 返回左机械臂的当前位置，返回值为角度传感器的累计角度值。


void arm_right_stop();
void arm_right_up(int speed);
void arm_right_down(int speed);
bool is_arm_right_touch_bottom();
int get_arm_right_pos();
//以上右机械臂函数参考左机械臂说明。


void init_IR_sensor();
//初始化红外传感器

int get_IR_direction();
// 读取红外传感器的方向，0-没有检测到红外线信号，1-9代表从左后方到右后方，5代表正前方。2-左，8-右

void init_prototype_board();
//初始化原型板

void reset_angle_sensor();
//重置角度传感器，将当前位置作为位置“0”。


int get_left_ring_weight();
int get_right_ring_weight();
//读取左右称重传感器的重量值，0-1023，数字越大代表越重。

///////////////////////////////////////////////////////////////////////////////////
```