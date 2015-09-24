#include "inc/hw_memmap.h"		//?��?��o��?����?			
#include "inc/hw_types.h"		//��y?Y����D��o��?����?��???��??�¡�??��o����y	
#include "driverlib/debug.h"	//�̡¨�?��?	
#include "driverlib/gpio.h" 	//������?IO?��o��?����?	
#include "driverlib/sysctl.h"	//?�̨�3????o��?����?

/*
LED0(Yellow)-->PF3,	LED1(Green)-->PF2	�̨���???��DD��

???��?��
SW_1	JP43	PB6		Right
SW_2	JP41	PE5		Press
SW_3	JP42	PE4		Up
SW_4	JP44	PF1		Down
SW_5	JP45	PB4		Left
�̨���???�䣤����
*/

int main(void)					
{

	int flagup1 = 0;
	int flagup2 =0;
	int flagdown1 = 0;
	int flagdown2 =0;
	int flagleft1 = 0;
	int flagleft2 =0;
	int flagright1 = 0;
	int flagright2 =0;
	int flaghere1 = 0;
	int flaghere2 =0;
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);		//��1?��???��B
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);		//��1?��???��E
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);		//��1?��???��F

	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,				//PF2,PF3����???a2mA��?������?3?
						  GPIO_PIN_2 |
						  GPIO_PIN_3);								   
	GPIOPinWrite(GPIO_PORTF_BASE,						//LED0,LED0???e
				 GPIO_PIN_2,
				 GPIO_PIN_2);
	GPIOPinWrite(GPIO_PORTF_BASE,
				 GPIO_PIN_3,
				 GPIO_PIN_3);

	GPIOPinTypeGPIOInput(GPIO_PORTB_BASE,			 	//����??PB6,PE5,PE4,PF1,PB4?a��?��?
						 GPIO_PIN_4 | 
						 GPIO_PIN_6);
	GPIOPinTypeGPIOInput(GPIO_PORTE_BASE,
						 GPIO_PIN_4 | 
						 GPIO_PIN_5);	
	GPIOPinTypeGPIOInput(GPIO_PORTF_BASE,
						 GPIO_PIN_1);
		
	while(1)
	{
		if (GPIOPinRead(GPIO_PORTB_BASE,GPIO_PIN_6) == 0)
		{
			flagright2 = 1;
			flagdown2 =0;
			flagleft2 =0;
			flagup2 =0;
			flaghere2 =0;
			if ((flagright1 == 1) && (flagright2 == 1))
			{
			 	GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_2,GPIO_PIN_2);		//LED1?e
				GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_3,~GPIO_PIN_3);
			}
		}
		else
		{
		
		if (GPIOPinRead(GPIO_PORTB_BASE,GPIO_PIN_4) == 0)				//����?������
		{
			flagleft2 = 1;
			flagdown2 =0;
			flagup2 =0;
			flagright2 =0;
			flaghere2 =0;
			if (flagleft1 == 1 && flagleft2 == 1)
			{
				GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_2,GPIO_PIN_2);		//LED1?e
				GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_3,~GPIO_PIN_3);
			}		//LED0����
		}
		else
		{
			if (GPIOPinRead(GPIO_PORTE_BASE,GPIO_PIN_4 ) == 0)
			{
				flagup2 = 1;
				flagdown2 =0;
				flagleft2 =0;
				flagright2 =0;
				flaghere2 =0;
				if (flagup1 == 1 && flagup2 == 1)
				{
					GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_2,~GPIO_PIN_2);	//LED1����
					GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_3,GPIO_PIN_3);
				}	//LED0?e
			}
			else
			{
			 if (GPIOPinRead(GPIO_PORTF_BASE,GPIO_PIN_1) == 0)			//��??��??
			{
				flagdown2 = 1;
				flagup2 =0;
				flagleft2 =0;
				flagright2 =0;
				flaghere2 =0;
				if (flagdown1 == 1 && flagdown2 == 1)
				{
					GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_2,~GPIO_PIN_2);	//LED1����
					GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_3,GPIO_PIN_3);
				}	//LED0?e
			}
			else
			{
				if (GPIOPinRead(GPIO_PORTE_BASE,GPIO_PIN_5)==0)
				{	//���??
				 	flaghere2 = 1;
					flagup2 =0;
					flagleft2 =0;
					flagright2 =0;
					flagdown2 =0;
					if (flaghere1 == 1 && flaghere2 == 1)
					{
						GPIOPinWrite(GPIO_PORTF_BASE,
								 	GPIO_PIN_2 |
								 	GPIO_PIN_3,
								 	~GPIO_PIN_2 &
								 	~GPIO_PIN_3);
					}						//LED0?��LED1����
				}
				else
				{
					flagup1 = flagup2;
					flagdown1 = flagdown2;
					flagleft1 = flagleft2;
					flagright1 = flagright2;
					flaghere1 = flaghere2;
					GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_2 |
								 GPIO_PIN_3,
								 GPIO_PIN_2 |
								 GPIO_PIN_3);
				}							//1?��?LED0o��LED1
			}
			}
			}
		} 	 
	}							   
}
