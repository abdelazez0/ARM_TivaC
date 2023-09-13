#ifndef GPTM_CFG_H_
#define GPTM_CFG_H_

typedef enum 
{
    _32_64_Bit_Timer,
	_32_64_Bit_Timer_RTC,
	_16_32_Bit_Timer=4,
}Timer_CFG;

typedef enum 
{
	ONE_SHOT_MODE=1,
	Periodic_Mode,
	Capture_Mode,
}Timer_Mode;


typedef enum 
{
	DOWN,
	UP_starts_0x0,	
}Timer_Direction;

#endif
