#include "tm4c123gh6pm.h"
#include "std_types.h"
#include "bitwise_operation.h"

#include "GPTM_Interface.h"
#include "GPTM_Registers.h"
#include "GPTM_CFG.h"

void GPTM_Init(void)
{
    /*Enable Clock For Timer 1*/
    SET_BIT(SYSCTL_RCGCTIMER_R,1);

    /*Wait for timer Clock*/
    while(!GET_BIT(SYSCTL_RCGCTIMER_R, 1));

	/*Disable for timer*/
	CLR_BIT(GPTMCTL,GPTMCTL_TAEN) ;

	/*32 or 64 bit timer*/
	GPTMCFG=(GPTMCFG&0xFFFFFFF8)| _32_64_Bit_Timer;

	/*Perpdic Mode*/
	GPTMTAMR=(GPTMTAMR&0xFFFFFFFC)| Periodic_Mode;

	/*Direction of counts >>> Up*/
	GPTMTAMR=(GPTMTAMR&0xFFFFFFEF)| DOWN;

	/*Enable interrupt*/
	SET_BIT(GPTMIMR,GPTMIMR_TATOIM);

	/*Load Value For 60 SEC*/
	GPTMTAILR=0x39387000;

	/*Stalling for debugging*/
	SET_BIT(GPTMCTL,GPTMCTL_TASTALL);

	/*Enable Timer*/
	SET_BIT(GPTMCTL,GPTMCTL_TAEN);
}

void GPTM_delay_sec (uint8 delay_Sec)
{
	 uint8 Counts=0;
	
	/*Disable for timer*/
	CLR_BIT(GPTMCTL,GPTMCTL_TAEN);

	/*32 or 64 bit timer*/
	GPTMCFG=(GPTMCFG&0xFFFFFFF8)| _32_64_Bit_Timer;

	/*Perpdic Mode*/
	GPTMTAMR=(GPTMTAMR&0xFFFFFFFC)| Periodic_Mode;

	/*Direction of counts >>> Up*/
	GPTMTAMR=(GPTMTAMR&0xFFFFFFEF)| DOWN;

	/*Load Value*/    /*for 1 sec*/
	GPTMTAILR=0x2FAF080;

	/*Stalling for debugging*/
	SET_BIT(GPTMCTL,GPTMCTL_TASTALL);

	/*Enable Timer*/
	SET_BIT(GPTMCTL,GPTMCTL_TAEN);
	
	while(Counts!=delay_Sec)
	{
		while (!GET_BIT(GPTMRIS,GPTMRIS_TATORIS));
		SET_BIT(GPTMICR,GPTMICR_TATOCINT);
		Counts++;
	}
}

void GPTM_delay_millisec (uint8 delay_ms)
{
	uint8 Counts=0;
	
	/*Disable for timer*/
	CLR_BIT(GPTMCTL,GPTMCTL_TAEN);

	/*32 or 64 bit timer*/
	GPTMCFG=(GPTMCFG&0xFFFFFFF8)| _32_64_Bit_Timer;

	/*Perpdic Mode*/
	GPTMTAMR=(GPTMTAMR&0xFFFFFFFC)| ONE_SHOT_MODE;

	/*Direction of counts >>> Up*/
	GPTMTAMR=(GPTMTAMR&0xFFFFFFEF)| DOWN;

	/*Load Value*/    /*for 1 ms*/
	GPTMTAILR=0xC350;

	/*Stalling for debugging*/
	SET_BIT(GPTMCTL,GPTMCTL_TASTALL);

	/*Enable Timer*/
	SET_BIT(GPTMCTL,GPTMCTL_TAEN);
	
	while(Counts!=delay_ms)
	{
		while (!GET_BIT(GPTMRIS,GPTMRIS_TATORIS));
		SET_BIT(GPTMICR,GPTMICR_TATOCINT);
		Counts++;
	}
}

void TIMER0A_Handler(void)
{
	// Turn OFF motors

}


/*
void WTimer_0_Inputcapture_INIT(void)
{
    SET_BIT(SYSCTL_RCGCWTIMER_R,0);enable clock to timer 0
    CLR_BIT(WTIMER0_CTL_R,0);timer A disabled from counting or captured
    WTIMER0_CFG_R=0x04;enable Timer 32 bit mode
    WTIMER0_TAMR_R=0x03;capture mode
    SET_BIT(WTIMER0_TAMR_R,2);to make edge time
    SET_BIT(WTIMER0_TAMR_R,4);count up
    WTIMER0_CTL_R|=(1<<3)|(1<<2);enable BOTH edge

    SET_BIT(GPIO_PORTC_AFSEL_R,4);
                                   *  make pin from Gpio to alternating function

    GPIO_PORTC_PCTL_R|= (0x07<<16);
    SET_BIT(WTIMER0_IMR_R ,2);//enable capture mode interrput
    SET_BIT(NVIC_EN2_R,30);//enable interupt from Nvic
    SET_BIT(WTIMER0_CTL_R,0);enable Timer
}
*/

void WTimer_0_Inputcapture_INIT(void)
{
    SET_BIT(SYSCTL_RCGCWTIMER_R,0);/*enable clock to timer 0*/
    while(!GET_BIT(SYSCTL_RCGCWTIMER_R,0)); /*wait for clock to initialize*/
    CLR_BIT(WTIMER0_CTL_R,0);/*timer A disabled from counting or captured*/
    WTIMER0_CFG_R=0x04;/*enable Timer 32 bit mode*/
    WTIMER0_TAMR_R=0x03;/*capture mode*/
    SET_BIT(WTIMER0_TAMR_R,2);/*to make edge time*/
    SET_BIT(WTIMER0_TAMR_R,4);/*count up*/
    WTIMER0_CTL_R|=(1<<3)|(1<<2);/*enable BOTH edge*/

    SET_BIT(GPIO_PORTC_AFSEL_R,4);/*
                                   *  make pin from Gpio to alternating function
                                   */
    GPIO_PORTC_PCTL_R|= (0x07<<16);
    CLR_BIT(WTIMER0_IMR_R ,2);//enable capture mode interrput
    SET_BIT(NVIC_EN2_R,30);//enable interupt from Nvic
    SET_BIT(WTIMER0_CTL_R,0);/*enable Timer*/
}
