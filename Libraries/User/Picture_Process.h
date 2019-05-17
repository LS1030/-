#ifndef __PICTURE_PROCESS_H
#define __PICTURE_PROCESS_H

#include "headfile.h"

 /*                                                宏定义区                                              */
#define image_bin 135 //设置二值化阈值为常数，总灰度的一半


#define  MIN(x,y) ((x) <= (y) ? (x) : (y)) 
#define  MAX(x,y) ((x) >= (y) ? (x) : (y)) 

/************************************************************************/
/*                      内部输出变量及数组                              */
//extern uint8  leftback[CAMERA_H];                   
//extern uint8  rightback[CAMERA_H];                  
//extern uint8  bianyanflag[CAMERA_H];
/************************************************************************/
void image_Binarizate(void);
void image_scan(void);
uint8 Get_Middle(void);
#endif

