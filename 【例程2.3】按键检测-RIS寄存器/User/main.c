/************************************************************************************** 
*   日期    ：2013年11月6日 (版权所有，翻版必究) 
*   目标    ：ARM Cortex-M0 LPC1114 
*   编译环境：KEIL 4.60
*   外部晶振：10Mhz(主频50M)
*   功能    ：学会利用RIS寄存器获取GPIO引脚的高低电平
*   作者    ：Ration
*   官方网址：http://www.rationmcu.com
*   淘宝店  ：http://ration.taobao.com
**************************************************************************************/
#include "LPC11XX.H"

#define LED1_ON  LPC_GPIO1->DATA &= ~(1<<0)
#define LED1_OFF LPC_GPIO1->DATA |= (1<<0)
#define LED2_ON  LPC_GPIO1->DATA &= ~(1<<1)
#define LED2_OFF LPC_GPIO1->DATA |= (1<<1)

#define KEY1_DOWN (LPC_GPIO1->DATA&(1<<9))!=(1<<9)
#define KEY2_DOWN (LPC_GPIO1->DATA&(1<<10))!=(1<<10)
/***********************************/
/* 函数名称：LED灯初始化           */
/***********************************/
void led_init()
{
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<16); // 使能IOCON时钟 
	LPC_IOCON->R_PIO1_0 &= ~0x07;    
	LPC_IOCON->R_PIO1_0 |= 0x01; //把P1.0脚设置为GPIO
	LPC_IOCON->R_PIO1_1 &= ~0x07;	
	LPC_IOCON->R_PIO1_1 |= 0x01; //把P1.1脚设置为GPIO
	LPC_SYSCON->SYSAHBCLKCTRL &= ~(1<<16); // 禁能IOCON时钟
	
	LPC_GPIO1->DIR |= (1<<0); // 把P1.0设置为输出引脚
	LPC_GPIO1->DATA |= (1<<0); // 把P1.0设置为高电平
	LPC_GPIO1->DIR |= (1<<1); // 把P1.1设置为输出引脚
	LPC_GPIO1->DATA |= (1<<1); // 把P1.1设置为高电平
}
/***********************************/
/* 函数名称：主函数                */
/***********************************/
int main()
{
	led_init();
	
	while(1)
	{
		if((LPC_GPIO1->RIS&(1<<9))==(1<<9)) // 读取RIS寄存器
		{
			LED1_ON;
			while(KEY1_DOWN);
			LED1_OFF;
			LPC_GPIO1->IC = 0XFFF;  // 清RIS状态位
		}
		if((LPC_GPIO1->RIS&(1<<10))==(1<<10)) // 读取RIS寄存器
		{
			LED2_ON;
			while(KEY2_DOWN);
			LED2_OFF;
			LPC_GPIO1->IC = 0XFFF;  // 清RIS状态位
		}
	}
}

