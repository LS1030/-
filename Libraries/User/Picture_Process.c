#include "Picture_Process.h"

#define CAMERA_H        ROW
#define CAMERA_W        COL
extern uint8 image[CAMERA_H][CAMERA_W];                 //�Ҷ�
uint8  img[CAMERA_H][CAMERA_W];                          //��ֵ��

uint8 otsuThreshold(uint8 *image, uint16 col, uint16 row);

uint8  leftback[CAMERA_H] ;                             //����洢��������ݵ�����
uint8  rightback[CAMERA_H] ;                            //����洢�ұ������ݵ�����
uint8  bianyanflag[CAMERA_H];                          //����洢���ش�����Ϣ������
uint8  middleline[CAMERA_H];
/*��ֵ��������ת���Ҷ�ͼ��Ϊ��ֵ��*/
void image_Binarizate(void)
{
	uint16 i, j;
	uint8 image_threshold = 110;  //ͼ����ֵ
	//image_threshold = otsuThreshold(image[0],COL,ROW);  //��򷨼�����ֵ
	for (i = 0; i < CAMERA_H; i++)
	{
		for ( j = 0; j < CAMERA_W; j++)
		{
                  if(i == 60 && j == 20)
                  {
                    img[i][j] = 0xFF;
                  }
			if (image[i][j]<= image_threshold)
			{
				img[i][j] = 0x00;          //��ɫ
			}
			else
			{
				img[i][j] = 0xFF;        //��ɫ
			}
		}
	}
}

uint8 otsuThreshold(uint8 *image, uint16 col, uint16 row)
{
    #define GrayScale 256
    uint16 width = col;
    uint16 height = row;
    int pixelCount[GrayScale];
    float pixelPro[GrayScale];
    int i, j, pixelSum = width * height;
    uint8 threshold = 0;
    uint8* data = image;  //ָ���������ݵ�ָ��
    for (i = 0; i < GrayScale; i++)
    {
        pixelCount[i] = 0;
        pixelPro[i] = 0;
    }

    //ͳ�ƻҶȼ���ÿ������������ͼ���еĸ���  
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            pixelCount[(int)data[i * width + j]]++;  //������ֵ��Ϊ����������±�
        }
    }

    //����ÿ������������ͼ���еı���  
    float maxPro = 0.0;
    for (i = 0; i < GrayScale; i++)
    {
        pixelPro[i] = (float)pixelCount[i] / pixelSum;
        if (pixelPro[i] > maxPro)
        {
            maxPro = pixelPro[i];
        }
    }

    //�����Ҷȼ�[0,255]  
    float w0, w1, u0tmp, u1tmp, u0, u1, u, deltaTmp, deltaMax = 0;
    for (i = 0; i < GrayScale; i++)     // i��Ϊ��ֵ
    {
        w0 = w1 = u0tmp = u1tmp = u0 = u1 = u = deltaTmp = 0;
        for (j = 0; j < GrayScale; j++)
        {
            if (j <= i)   //��������  
            {
                w0 += pixelPro[j];
                u0tmp += j * pixelPro[j];
            }
            else   //ǰ������  
            {
                w1 += pixelPro[j];
                u1tmp += j * pixelPro[j];
            }
        }
        u0 = u0tmp / w0;
        u1 = u1tmp / w1;
        u = u0tmp + u1tmp;
        deltaTmp = w0 * pow((u0 - u), 2) + w1 * pow((u1 - u), 2);
        if (deltaTmp > deltaMax)
        {
            deltaMax = deltaTmp;
            threshold = i;
        }
    }

    return threshold;
}

/*ɨ�躯������ȡ�������أ�����ÿ������ƫ��*/
void image_scan(void)
{
	uint16 i, j;
	uint16 leftscan,rightscan,leftend,rightend;
	uint8 leftflag , rightflag ;
	//�ɽ���Զ��ǰ����ȫ������ɨ�裬����ȷ����һ��ɨ�����ֹ��
	//ǰ����ɨ��ʱ���ֱ���м���������������غ��ұ���
	for ( i = CAMERA_H-1; i >=CAMERA_H-3; i--)
	{
		leftflag = 0; rightflag = 0;
		for (j = CAMERA_W / 2; j > 5; j--)//�������������
		{
			if (img[i][j]==0 && img[i][j + 1]==255)//��������������������У���ߺ�ɫ�ұ߰�ɫ
			{
				leftback[i] = j;//������ȷ��Ϊ���е������������
				leftflag = 1;
				break;
			}
                        else
                        {
                          leftback[i] = 1;	                
                        }
		}
		for (j = CAMERA_W / 2; j < CAMERA_W-5; j++)//�����ұ���
		{
			if (img[i][j] == 0 && img[i][j - 1] == 255)//�ұ�������������Һ�
			{
				rightback[i] = j;//������ȷ��Ϊ���е������������
				rightflag = 2;
				break;
			}
                         else
                        {
                          leftback[i] = CAMERA_W-1;	                   
                        }
		}
		bianyanflag[i] = leftflag + rightflag;//��ÿ��ɨ�������洢���б����Ƿ���ڵ���Ϣ
                middleline[i]=rightback[i]-leftback[i];
	}
	//��ǰ���б���λ��ȷ��������������Χ�Լ���ɨ����
	for ( i = CAMERA_H-4; i >0; i--)
	{
		leftflag = 0; rightflag = 0;
                leftend = 0;rightend = 0; 
                if(bianyanflag[i+1]==3||bianyanflag[i+1]==1)
                {
                  leftscan = MAX(leftback[i+1]-10,5);
                  rightend = leftback[i+1];
                }
                else if(bianyanflag[i+2]==3||bianyanflag[i+2]==1)
                {
                  leftscan = MAX(leftback[i+2]-10,5);
                  rightend = leftback[i+2];
                }
                else if(bianyanflag[i+3]==3||bianyanflag[i+3]==1)
                {
                  leftscan = MAX(leftback[i+3]-10,5);
                  rightend = leftback[i+3];
                }
                else
                {
                  leftscan=5;
                  rightend=5;
                }
		
                if(bianyanflag[i+1]==3||bianyanflag[i+1]==2)
                {
                  rightscan=MIN(rightback[i+1]+10,CAMERA_W-1);
                  leftend = rightback[i+1];
                }
                else if(bianyanflag[i+2]==3||bianyanflag[i+2]==2)
                {
                  rightscan=MIN(rightback[i+2]+10,CAMERA_W-1);
                  leftend = rightback[i+2];
                }
                else if(bianyanflag[i+3]==3||bianyanflag[i+3]==2)
                {
                  rightscan=MIN(rightback[i+3]+10,CAMERA_W-1);
                  leftend = rightback[i+3];
                }
                else
                {
                  rightscan=CAMERA_W-5;
                  leftend=CAMERA_W-5;
                }
		
		for ( j = leftscan; j <= leftend; j++)//���������
		{
			if (img[i][j] == 0 && img[i][j + 1] == 255)//��������������������У���ߺ�ɫ�ұ߰�ɫ
			{
				leftback[i] = j;//������ȷ��Ϊ���е������������
				leftflag = 1;
				break;
			}
		}
		for ( j = rightscan; j >rightend; j--)
		{
			if (img[i][j] == 0 && img[i][j - 1] == 255)
			{
				rightback[i] = j;
				rightflag = 2;
				break;
			}
		}
		bianyanflag[i] = leftflag + rightflag;
//		if (leftflag==0)//ÿһ��ɨ����ɺ���в���
//		{
//			if (bianyanflag[i + 1]==1|| bianyanflag[i + 1] == 3)
//			{
//				leftback[i] = leftback[i+1];
//			}
//			else
//			{
//				leftback[i] = 0;
//			}
//		}
//		if (rightflag == 0)//ÿһ��ɨ����ɺ���в���
//		{
//			if (bianyanflag[i + 1] == 2 || bianyanflag[i + 1] == 3)
//			{
//				rightback[i] = rightback[i + 1];
//			}
//			else
//			{
//				rightback[i] = CAMERA_W-1;
//			}
//		}
                middleline[i]=(rightback[i]+leftback[i])/2;
	}
        
        for(i = CAMERA_H-1; i >0; i--)
        {
            image[i][middleline[i]] = 0x00;
            image[i][rightback[i]] = 0x00;
            image[i][leftback[i]] = 0x00;
        }
    
        
}


//�����ȡһ��ƫ��ֵ������ж���Ϣ
uint8 Get_Middle(void)
{
	uint8 flag = 0;//1Ϊ����ת��2Ϊ����ת
		int midline1_H = (CAMERA_H/2)-3;
		int midline2_H = (CAMERA_H/2);
		int midline3_H = (CAMERA_H/2)+5;
		int midline1_L, midline2_L, midline3_L;

		midline1_L = (rightback[midline1_H] + leftback[midline1_H]) / 2;
		midline2_L = (rightback[midline2_H] + leftback[midline2_H]) / 2;
		midline3_L = (rightback[midline3_H] + leftback[midline3_H]) / 2;
		if ((midline1_L+ midline2_L+ midline3_L)/3 < CAMERA_W/2)
		{
			flag = 1;
		}
		else if ((midline1_L + midline2_L + midline3_L)/3 > CAMERA_W / 2)
		{
			flag = 2;
		}
		return flag;
}