/************************************************************************************** 
*   ����    ��2013��11��6�� (��Ȩ���У�����ؾ�) 
*   Ŀ��    ��ARM Cortex-M0 LPC1114 
*   ���뻷����KEIL 4.60
*   �ⲿ����10Mhz(��Ƶ50M)
*   ����    ��ѧ��ʹ��GPIO�����������ж�
*   ����    ��Ration
*   �ٷ���ַ��http://www.rationmcu.com
*   �Ա���  ��http://ration.taobao.com
**************************************************************************************/
#include "LPC11XX.H"

#define LED1_ON  LPC_GPIO1->DATA &= ~(1<<0)
#define LED1_OFF LPC_GPIO1->DATA |= (1<<0)
#define LED2_ON  LPC_GPIO1->DATA &= ~(1<<1)
#define LED2_OFF LPC_GPIO1->DATA |= (1<<1)

#define KEY1_DOWN (LPC_GPIO1->DATA&(1<<9))!=(1<<9)
#define KEY1_UP   (LPC_GPIO1->DATA&(1<<9))==(1<<9)
#define KEY2_DOWN (LPC_GPIO1->DATA&(1<<10))!=(1<<10)
#define KEY2_UP   (LPC_GPIO1->DATA&(1<<10))==(1<<10)
/***********************************/
/* �������ƣ�����������ʱ          */
/***********************************/
void delay_xd()
{
	uint16_t i,j;
	
	for(i=0;i<50000;i++)
		for(j=0;j<10;j++);	
}
/***********************************/
/* �������ƣ���ʱ                  */
/***********************************/
void delay()
{
	uint16_t i,j;
	
	for(i=0;i<50000;i++)
		for(j=0;j<80;j++);
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
	
	LPC_GPIO1->DIR |= (1<<0);
	LPC_GPIO1->DATA |= (1<<0);
	LPC_GPIO1->DIR |= (1<<1);
	LPC_GPIO1->DATA |= (1<<1);
}
/***********************************/
/* �������ƣ�GPIO1�жϺ���         */
/***********************************/
void PIOINT1_IRQHandler()
{
		if((LPC_GPIO1->MIS&(1<<9))==(1<<9))
		{
			delay_xd();
			if(KEY1_UP)
			{
				LED1_ON;
				delay();
				LED1_OFF;
			}
			LPC_GPIO1->IC = 0XFFF;  // ��RIS״̬λ
		}
		if((LPC_GPIO1->MIS&(1<<10))==(1<<10))
		{
			delay_xd();
			if(KEY2_UP)
			{
				LED2_ON;
				delay();
				LED2_OFF;
			}
			LPC_GPIO1->IC = 0XFFF;  // ��RIS״̬λ
		}
}
/***********************************/
/* �������ƣ�������                */
/***********************************/
int main()
{
	led_init();
	LPC_GPIO1->IEV |= (1<<9); // ����P1.9�����ش���
	LPC_GPIO1->IEV |= (1<<10); // ����P1.10�����ش���
	LPC_GPIO1->IE |= (1<<9); //
	LPC_GPIO1->IE |= (1<<10);
	NVIC_EnableIRQ(EINT1_IRQn);
	
	while(1)
	{
		;
	}
}

