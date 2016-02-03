/************************************************************************************** 
*   日期    ：2013年11月6日 (版权所有，翻版必究) 
*   目标    ：ARM Cortex-M0 LPC1114 
*   编译环境：KEIL 4.60
*   外部晶振：10Mhz(主频50M)
*   功能    ：学会使用GPIO引脚下降沿中断
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
/* 函数名称：GPIO1中断函数         */
/***********************************/
void PIOINT1_IRQHandler()
{
	if((LPC_GPIO1->MIS&(1<<9))==(1<<9)) // 如果是P1.9引起的中断
	{
		LED1_ON;
		while(KEY1_DOWN);
		LED1_OFF;
		LPC_GPIO1->IC = 0XFFF;  // 清中断
	}
	if((LPC_GPIO1->MIS&(1<<10))==(1<<10)) // 如果是P1.10引起的中断
	{
		LED2_ON;
		while(KEY2_DOWN);
		LED2_OFF;
		LPC_GPIO1->IC = 0XFFF;  // 清中断
	}
}
/***********************************/
/* 函数名称：主函数                */
/***********************************/
int main()
{
	led_init(); // 配置LED
	LPC_GPIO1->IE |= (1<<9); // 允许P1.9引脚上的中断
	LPC_GPIO1->IE |= (1<<10); // 允许P1.10引脚上的中断
	NVIC_EnableIRQ(EINT1_IRQn); // 打开GPIO1中断
	
	while(1)
	{
		;
	}
}

