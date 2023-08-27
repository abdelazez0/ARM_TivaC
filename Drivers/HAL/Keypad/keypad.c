 /******************************************************************************
 *
 * Module: KEYPAD
 *
 * File Name: keypad.c
 *
 * Description: Source file for the Keypad driver
 *
 * Author: Mohamed Abdelazez
 *
 *******************************************************************************/
#include "keypad.h"
#include "DIO.h"
#include "delay.h"

extern volatile uint32 PORTC_interruptStatusRegister;
extern volatile uint8 PORTC_interruptStatus;
/*******************************************************************************
 *                      Functions Prototypes(Private)                          *
 *******************************************************************************/

/*
 * Function responsible for mapping the switch number in the keypad to
 * its corresponding functional number in the 4x4 keypad
 */
static uint8 KEYPAD_4x4_adjustKeyNumber(uint8 button_number);


/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
void KEYPAD_init(void)
{
    /* DIO keypad init */
    DIO_init(KEYPAD_ROW_PORT_ID , 0b00011110 , 0x00);
    DIO_init(KEYPAD_COL_PORT_ID , 0b11110000 , 0x00);

#ifdef INTERRUPT_KEYPAD
    /* DIO keypad pins interrupt enable */
    DIO_EnableInterrupt(KEYPAD_COL_PORT_ID , (KEYPAD_FIRST_COL_PIN_ID + 0) , edge , failingLow);
    DIO_EnableInterrupt(KEYPAD_COL_PORT_ID , (KEYPAD_FIRST_COL_PIN_ID + 1) , edge , failingLow);
    DIO_EnableInterrupt(KEYPAD_COL_PORT_ID , (KEYPAD_FIRST_COL_PIN_ID + 2) , edge , failingLow);
    DIO_EnableInterrupt(KEYPAD_COL_PORT_ID , (KEYPAD_FIRST_COL_PIN_ID + 3) , edge , failingLow);
#endif
}


uint8 KEYPAD_getPressedKey(void)
{
	uint8 col = 0;
	uint8 row = 0;

#ifdef POLLING_KEYPAD

	while(1)
	{
		for(row=0 ; row < KEYPAD_NUM_ROWS ; row++) /* loop for rows */
		{
			/* 
			 * Each time setup the direction for all keypad port as input pins,
			 * except this row will be output pin
			 */
			DIO_PinDirection(KEYPAD_ROW_PORT_ID,KEYPAD_FIRST_ROW_PIN_ID+row,outputPin);

			/* Set/Clear the row output pin */
			DIO_WritePin(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID+row, KEYPAD_BUTTON_PRESSED);

			for(col=0 ; col<KEYPAD_NUM_COLS ; col++) /* loop for columns */
			{
				/* Check if the switch is pressed in this column */
				if(DIO_ReadPin(KEYPAD_COL_PORT_ID,KEYPAD_FIRST_COL_PIN_ID+col) == KEYPAD_BUTTON_PRESSED)
				{
					return KEYPAD_4x4_adjustKeyNumber((row*KEYPAD_NUM_COLS)+col+1);
				}
			}
			DIO_PinDirection(KEYPAD_ROW_PORT_ID,KEYPAD_FIRST_ROW_PIN_ID+row, inputPin);
		}
	}	
#endif

#ifdef INTERRUPT_KEYPAD

	while(PORTC_interruptStatus == INTERRUPT_FALSE)
	{
	    for(row=0 ; row < KEYPAD_NUM_ROWS ; row++)
	    {
	        DIO_PinDirection(KEYPAD_ROW_PORT_ID,KEYPAD_FIRST_ROW_PIN_ID+row,outputPin);            /* the direction for all keypad port as input pins except this row will be output pin */
	        DIO_WritePin(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID+row, KEYPAD_BUTTON_PRESSED);  /* Set/Clear the row output pin */

	        if(PORTC_interruptStatus == INTERRUPT_TRUE)
	        {
	            DIO_PinDirection(KEYPAD_ROW_PORT_ID,KEYPAD_FIRST_ROW_PIN_ID+row, inputPin);        /* make the pin input again */
	            break;
	        }

	        DIO_PinDirection(KEYPAD_ROW_PORT_ID,KEYPAD_FIRST_ROW_PIN_ID+row, inputPin);            /* make the pin input again */
	    }
	}

    PORTC_interruptStatus = INTERRUPT_FALSE;

    switch((PORTC_interruptStatusRegister >> 4) << 4)
    {
    case (1 << (KEYPAD_FIRST_COL_PIN_ID + 0)):      col = 0;        break;

    case (1 << (KEYPAD_FIRST_COL_PIN_ID + 1)):      col = 1;        break;

    case (1 << (KEYPAD_FIRST_COL_PIN_ID + 2)):      col = 2;        break;

    case (1 << (KEYPAD_FIRST_COL_PIN_ID + 3)):      col = 3;        break;

    default:
    break;
    }

    PORTC_interruptStatusRegister = 0;
    return KEYPAD_4x4_adjustKeyNumber((row*KEYPAD_NUM_COLS)+col+1);

#endif
}

/*
 * Description :
 * Update the keypad pressed button value with the correct one in keypad 4x4 shape
 */
static uint8 KEYPAD_4x4_adjustKeyNumber(uint8 button_number)
{
	uint8 keypad_button = 0;
	switch(button_number)
	{
		case 1: keypad_button = '1';
				break;
		case 2: keypad_button = '2';
				break;
		case 3: keypad_button = '3';
				break;
		case 4: keypad_button = '+';
				break;
		case 5: keypad_button = '4';
				break;
		case 6: keypad_button = '5';
				break;
		case 7: keypad_button = '6';
				break;
		case 8: keypad_button = '-';
				break;		
		case 9: keypad_button = '7';
				break;
		case 10: keypad_button = '8';
				break;
		case 11: keypad_button = '9';
				break;
		case 12: keypad_button = '*';
				break;
		case 13: keypad_button = '%';
				break;			
		case 14: keypad_button = '0';
				break;
		case 15: keypad_button = '=';
				break;
		case 16: keypad_button = '/';
				break;
		default: keypad_button = button_number;
				break;
	}
	return keypad_button;
} 
