#ifndef __PICTURE_PROCESS_H
#define __PICTURE_PROCESS_H

#include "headfile.h"

 /*                                                �궨����                                              */
#define image_bin 135 //���ö�ֵ����ֵΪ�������ܻҶȵ�һ��


#define  MIN(x,y) ((x) <= (y) ? (x) : (y)) 
#define  MAX(x,y) ((x) >= (y) ? (x) : (y)) 

/************************************************************************/
/*                      �ڲ��������������                              */
//extern uint8  leftback[CAMERA_H];                   
//extern uint8  rightback[CAMERA_H];                  
//extern uint8  bianyanflag[CAMERA_H];
/************************************************************************/
void image_Binarizate(void);
void image_scan(void);
uint8 Get_Middle(void);
#endif

