/********************************************
逐飞科技 总钻风-摄像头  历程
Designed by Fly Sir
软件版本:V1.1
最后更新:2016年5月3日
相关信息参考下列地址：
淘宝店：https://seekfree.taobao.com/
------------------------------------
软件版本： IAR 7.2 or MDK 5.17
目标核心： MK60DN512VLL10
============================================
MT9V032接线定义：
------------------------------------ 
	模块管脚            单片机管脚
    SDA(51的RX)         C17
    SCL(51的TX)         C16
	场中断              C6
    行中断				未使用，因此不接
    像素中断            C18            
    数据口              C8-C15 

    串口  
    波特率 115200 
    数据位 8 
    校验位 无
    停止位 1位
    流控   无
	串口连接注意事项：切勿使用蓝牙等无线串口连接
    RX                  D3
    TX                  D2
============================================

分辨率是                188*120
摄像头参数设置可以到    SEEKFREE-->h_file-->SEEKFREE_MT9V032.h

总钻风-摄像头测试步骤：
1.下载程序到开发板
2.插上串口线或者USB转TTL
3.接好MT9V032模块接线
4.通电在TFT液晶上即可观看    
*********************************************/  
#include "headfile.h"



int main(void)
{
   uint8 direction; 
   
    get_clk();//上电后必须运行一次这个函数，获取各个频率信息，便于后面各个模块的参数设置
    uart_init (uart2, 256000);                          //初始换串口与电脑通信
    camera_init();
    port_init(C5, ALT1);     //run
    port_init(C7, ALT1);     //left
    port_init(C8, ALT1);     //right
    gpio_init(C5, GPO, 0);
    gpio_init(C7, GPO, 0);
    gpio_init(C8, GPO, 0);
	//lcd_init();
	
    for(;;)
	{
          gpio_set(C5, 0);
          mt9v032_get_image();  
         
          image_scan();
           seekfree_sendimg_032();

           direction = Get_Middle();
          switch(direction)
          {
          case 0:
          {
            gpio_set(C7, 0);
            gpio_set(C8, 0);
            break;
          }
          case 1:   //向左
          {
            gpio_set(C7, 1);
            gpio_set(C8, 0);
            break;
          }
          case 2:   //向右
          {
            gpio_set(C7, 0);
            gpio_set(C8, 1);
            break;
          }
          default:
          break;
          }
        
	}
}

