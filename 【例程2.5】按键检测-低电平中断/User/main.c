/************************************************************************************** 
*   日期    ：2013年11月6日 (版权所有，翻版必究) 
*   目标    ：ARM Cortex-M0 LPC1114 
*   编译环境：KEIL 4.60
*   外部晶振：10Mhz(主频50M)
*   功能    ：学会使用GPIO引脚低电平中断
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
	
	LPC_GPIO1->DIR |= (1<<0);
	LPC_GPIO1->DATA |= (1<<0);
	LPC_GPIO1->DIR |= (1<<1);
	LPC_GPIO1->DATA |= (1<<1);
}
/***********************************/
/* 函数名称：GPIO1中断函数         */
/***********************************/
void PIOINT1_IRQHandler()
{
	if((LPC_GPIO1->MIS&(1<<9))==(1<<9))
	{
		LED1_ON;
		while(KEY1_DOWN);
		LED1_OFF;
		LPC_GPIO1->IC = 0XFFF;  // 清RIS状态位
	}
	if((LPC_GPIO1->MIS&(1<<10))==(1<<10))
	{
		LED2_ON;
		while(KEY2_DOWN);
		LED2_OFF;
		LPC_GPIO1->IC = 0XFFF;  // 清RIS状态位
	}
}
/***********************************/
/* 函数名称：主函数                */
/***********************************/
int main()
{
	led_init();
	LPC_GPIO1->IS |= (1<<9); // 设置P1.9电平触发
	LPC_GPIO1->IS |= (1<<10); // 设置P1.10电平触发
	LPC_GPIO1->IE |= (1<<9); // 允许P1.9产生中断
	LPC_GPIO1->IE |= (1<<10); // 允许P1.10产生中断
	NVIC_EnableIRQ(EINT1_IRQn);
	
	while(1)
	{
		;
	}
}

