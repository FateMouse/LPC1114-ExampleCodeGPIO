/************************************************************************************** 
*   ����    ��2013��11��6�� (��Ȩ���У�����ؾ�) 
*   Ŀ��    ��ARM Cortex-M0 LPC1114 
*   ���뻷����KEIL 4.60
*   �ⲿ����10Mhz(��Ƶ50M)
*   ����    ��LED��ˮ�ƣ�ѧ�����GPIO���ŵĵ�ƽ�ߵ�
*   ����    ��Ration
*   �ٷ���ַ��http://www.rationmcu.com
*   �Ա���  ��http://ration.taobao.com
**************************************************************************************/
#include "LPC11XX.H"

#define LED1_ON  LPC_GPIO1->DATA &= ~(1<<0)
#define LED1_OFF LPC_GPIO1->DATA |= (1<<0)
#define LED2_ON  LPC_GPIO1->DATA &= ~(1<<1)
#define LED2_OFF LPC_GPIO1->DATA |= (1<<1)

/***********************************/
/* �������ƣ���ʱ����              */
/***********************************/
void delay()
{
	uint16_t i,j;
	
	for(i=0;i<5000;i++)
		for(j=0;j<200;j++);
}

/***********************************/
/* �������ƣ�LED�Ƴ�ʼ��           */
/***********************************/
void led_init()
{
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<16); // ʹ��IOCONʱ�� 
	LPC_IOCON->R_PIO1_0 &= ~0x07;    
	LPC_IOCON->R_PIO1_0 |= 0x01; //��P1.0������ΪGPIO
	LPC_IOCON->R_PIO1_1 &= ~0x07;	
	LPC_IOCON->R_PIO1_1 |= 0x01; //��P1.1������ΪGPIO
	LPC_SYSCON->SYSAHBCLKCTRL &= ~(1<<16); // ����IOCONʱ��
	
	LPC_GPIO1->DIR |= (1<<0); // ��P1.0����Ϊ�������
	LPC_GPIO1->DATA |= (1<<0); // ��P1.0����Ϊ�ߵ�ƽ
	LPC_GPIO1->DIR |= (1<<1); // ��P1.1����Ϊ�������
	LPC_GPIO1->DATA |= (1<<1); // ��P1.1����Ϊ�ߵ�ƽ
}
/***********************************/
/* �������ƣ�������                */
/***********************************/
int main()
{
	led_init();
	
	while(1)
	{
		delay();
		LED1_ON;
		LED2_OFF;
		delay();
		LED1_OFF;
		LED2_ON;
	}
}

