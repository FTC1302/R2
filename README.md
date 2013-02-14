== R2 ==

---- program for robot R2 of FTC team 1302 ----

FTC参赛队 1302 2013赛季：Ring it UP!!! 参赛机器人R2 程序。

文件说明：
/drivers 		: 角度传感器、红外线传感器及各种其他hitechnic传感器驱动程序所在目录
/prototype_drivers 	: 原型板驱动
R2_const.h		: 常数定义文件
R2_lib.h		: 库函数定义文件
R2_TELEOP.C 		: R2遥控阶段正式程序

以下为各种测试程序：
R2_TEST.C
R2_TEST_SERVO.C
R2_TEST_PB.C


总体性说明：
===========
机器人的方向为【取圈臂在后，机械臂马达在前，所有的左右、前后均以此方向为基准】。



常数说明：
=========
```C
//游戏手柄常数，感谢罗罗的耐心和细心，把混乱的手柄代码搞清楚了。
const int JOY_BUTTON_X=01;
const int JOY_BUTTON_A=02;
const int JOY_BUTTON_B=03;
const int JOY_BUTTON_Y=04;
const int JOY_BUTTON_LB=05;
const int JOY_BUTTON_RB=06;
const int JOY_BUTTON_LT=07;
const int JOY_BUTTON_RT=08;
const int JOY_BUTTON_J1_CLICK=11;
const int JOY_BUTTON_J2_CLICK=12;
const int JOY_BUTTON_TOPHAT_UP= 0;
const int JOY_BUTTON_TOPHAT_UP_RIGHT= 1;
const int JOY_BUTTON_TOPHAT_RIGHT= 2;
const int JOY_BUTTON_TOPHAT_DOWN_RIGHT= 3;
const int JOY_BUTTON_TOPHAT_DOWN= 4;
const int JOY_BUTTON_TOPHAT_DOWN_LEFT= 5;
const int JOY_BUTTON_TOPHAT_LEFT= 6;
const int JOY_BUTTON_TOPHAT_UP_LEFT= 7;

//检测按钮“点击”（注意不是“按住”）的时间定义，这里定义的是300毫秒以内的算“点击”
const int BUTTON_CLICK_DELAY=300;


// 关于伺服电机的说明：
// 所有的伺服电机都调整为0-180度运动，方向根据需要按下面的定义设定：（顺时针/逆时针均为伺服电机轴面向自己时看到的方向）
// 1. 取圈臂左：顺时针/逆时针
// 2. 取圈臂右：顺时针/逆时针
// 3. 左机械手底部：顺时针/逆时针
// 4. 左机械手顶部：顺时针/逆时针
// 5. 右机械手底部：顺时针/逆时针
// 6. 右机械手顶部：顺时针/逆时针

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



R2函数库说明
============
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

///////////////////////////////////////////////////////////////////////////////////
```