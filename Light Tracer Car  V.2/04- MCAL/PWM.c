/*
 * PWM.c outputs PWM signal on pins PF1 and PF2 of TIVA-C4123GH6PM
 *
 *  Created on: Sep 9, 2023
 *  Author: Marco Ashraf
 */

/*includes*/
#include "tm4c123gh6pm.h"
#include "bitwise_operation.h"
#include "std_types.h"
#include "PWM.h"
#include "DIO.h"

/*************************************************************************************************************************************/
/*************************************************************************************************************************************/
/*PWM initialization function*/
/*INPUTS: NONE*/
/*OUTPUTS: NONE*/
/*Description: Initializes the PWM1 module of the TIVA-C on PINS PF1 and PF2*/
/*************************************************************************************************************************************/
/*************************************************************************************************************************************/

void PWM_INIT(void)
{
    /*Clock the PWM*/
    SET_BIT(SYSCTL_RCGCPWM_R, 1);
    /*wait for the PWM to be ready*/
    while(!GET_BIT(SYSCTL_RCGCPWM_R, 1));

    /*use the system clock as is (16MHZ)*/
    CLR_BIT(SYSCTL_RCC_R, 20);

    /* initialization for port */
    DIO_init(PORTF, 0x00 , 0x06);

    /*select alternative function*/
    SET_BIT(GPIO_PORTF_AFSEL_R, PF1);
    SET_BIT(GPIO_PORTF_AFSEL_R, PF2);

    /*select PWM function*/
    SET_BIT(GPIO_PORTF_PCTL_R, 4);
    SET_BIT(GPIO_PORTF_PCTL_R, 6);
    SET_BIT(GPIO_PORTF_PCTL_R, 8);
    SET_BIT(GPIO_PORTF_PCTL_R, 10);

    /*Enable Output on the pins*/
    SET_BIT(GPIO_PORTF_DEN_R, PF1);
    SET_BIT(GPIO_PORTF_DEN_R, PF2);

    /*For Pin PF1 PWM signal comes from PWM module 1 generator 2 (pwm2B)*/
    /*For Pin PF2 PWM signal comes from PWM module 1 generator 3 (pwm3A)*/
    /*Disable PWM1 Generator 2,3 selecting Count down Mode and for changes to be updated automatically*/
    PWM1_2_CTL_R = PWM_configs;
    PWM1_3_CTL_R = PWM_configs;

    /*OUTPUT HIGH when the counter reaches the LOAD B value, OUPUT LOW when the counter reaches Comparator B value*/
    /*OUTPUT HIGH when the counter reaches the LOAD B value*/
    SET_BIT(PWM1_2_GENB_R, 2);
    SET_BIT(PWM1_2_GENB_R, 3);
    /*OUPUT LOW when the counter reaches Comparator B value*/
    CLR_BIT(PWM1_2_GENB_R, 6);
    SET_BIT(PWM1_2_GENB_R, 11);

    /*OUTPUT HIGH when the counter reaches the LOAD A value, OUPUT LOW when the counter reaches Comparator A value*/
    /*OUTPUT HIGH when the counter reaches the LOAD A value*/
    SET_BIT(PWM1_3_GENA_R, 2);
    SET_BIT(PWM1_3_GENA_R, 3);
    /*OUPUT LOW when the counter reaches Comparator A value*/
    CLR_BIT(PWM1_3_GENA_R, 6);
    SET_BIT(PWM1_3_GENA_R, 7);

    /*For a 10KHz Frequency Load value =  ((1/10*10^3)/(1/16*10^6))-1 = 1599*/
    PWM1_2_LOAD_R = Load_Value;
    PWM1_3_LOAD_R = Load_Value;
    /*Duty Cycle is calculated inversely so for a 25% duty cycle cmpa = 1599*0.75 ~= 1200*/
    PWM1_2_CMPB_R = DUTY_CYCLE;
    PWM1_3_CMPA_R = DUTY_CYCLE;
    /*Start PWM generator 0*/
    SET_BIT(PWM1_2_CTL_R, 0);
    SET_BIT(PWM1_3_CTL_R, 0);
    /*Enable M1PWM5 & M1PWM6 output*/
    SET_BIT(PWM1_ENABLE_R,5);
    SET_BIT(PWM1_ENABLE_R,6);
}

/*************************************************************************************************************************************/
/*************************************************************************************************************************************/
/*PWM Duty Cycle Function*/
/*INPUTS: unsigned integer 0-100 represents the percentage of the cycle*/
/*OUTPUTS: NONE*/
/*Description: Changes the Duty Cycle of the PWM For PINS PF1 and PF2*/
/*************************************************************************************************************************************/
/*************************************************************************************************************************************/

void Duty_Cycle(uint8 value)
{
    PWM1_2_CMPB_R = (Load_Value - (Load_Value*value/100));
    PWM1_3_CMPA_R = (Load_Value - (Load_Value*value/100));
}
