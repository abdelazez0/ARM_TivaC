/*
 * adc.c
 *
 *  Created on: Sep 10, 2023
 *      Author: Mohamed Abdelazez
 */
#include "std_types.h"
#include "bitwise_operation.h"
#include "tm4c123gh6pm.h"
#include "DIO.h"
#include "adc.h"

void ADC0_initLDR(void)
{
    /* ADC init */
    SET_BIT(SYSCTL_RCGCADC_R  , ADC0_BASE);                       /*Initialize the clock for ADC0*/
    while(!GET_BIT(SYSCTL_RCGCADC_R, ADC0_BASE));
    CLR_BIT(ADC0_ACTSS_R , SAMPLE_SEQUENCER1);                    /* Disabling the Needed Sample Sequencers */
    CLR_BIT(ADC0_ACTSS_R , SAMPLE_SEQUENCER2);                    /* Disabling the Needed Sample Sequencers */

    ADC0_EMUX_R |= (PROCESSOR_TRIGGER << SAMPLE_SEQUENCER1 * 4);  /* Configure the trigger event for the sample sequencer 1 */
    ADC0_EMUX_R |= (PROCESSOR_TRIGGER << SAMPLE_SEQUENCER2 * 4);  /* Configure the trigger event for the sample sequencer 2 */

    ADC0_SSMUX1_R = 0x2;
    ADC0_SSMUX2_R = 0x1;

    SET_BIT(ADC0_SSCTL1_R , ADC_CTL_END);                         /* End of the Sequence for Sample Sequencer 1 step 0 */
    SET_BIT(ADC0_SSCTL1_R,  ADC_CTL_IE);                          /* Enabling Sample Interrupt for Sample Sequencer 1 step 0 */

    SET_BIT(ADC0_SSCTL2_R , ADC_CTL_END);                         /* End of the Sequence for Sample Sequencer 1 step 0 */
    SET_BIT(ADC0_SSCTL2_R,  ADC_CTL_IE);                          /* Enabling Sample Interrupt for Sample Sequencer 1 step 0 */

    SET_BIT(ADC0_ACTSS_R , SAMPLE_SEQUENCER1);                    /* Enabling the Sample Sequencer 1 */
    SET_BIT(ADC0_ACTSS_R , SAMPLE_SEQUENCER2);                    /* Enabling the Sample Sequencer 2 */
}

void ADC0_initTempSensor(void)
{
    SET_BIT(SYSCTL_RCGCADC_R  , ADC0_BASE);                       /* Initialize the clock for ADC0*/

    CLR_BIT(ADC0_ACTSS_R , SAMPLE_SEQUENCER3);                    /* Disabling the Needed Sample Sequencers */
    ADC0_EMUX_R |= (PROCESSOR_TRIGGER << SAMPLE_SEQUENCER3 * 4);  /* Configure the trigger event for the sample sequencer 3 */
    SET_BIT(ADC0_SSCTL3_R , ADC_CTL_END);                         /* End of the Sequence for Sample Sequencer 1 step 0 */
    SET_BIT(ADC0_SSCTL3_R,  ADC_CTL_IE);                          /* Enabling Sample Interrupt for Sample Sequencer 1 step 0 */
    SET_BIT(ADC0_ACTSS_R , SAMPLE_SEQUENCER3);                    /* Enabling the Sample Sequencer 3 */
}

uint16 ADC0_TempSensorAnalogReading(void)
{
    uint16 ADC0_Value;                                            /* This value to read the voltage from the ADC*/

    SET_BIT(ADC0_PSSI_R , 3);                                     /* Initiate the ADC conversion for Sample Sequencer 3 */
    while(!GET_BIT(ADC0_RIS_R , 3));                              /* check for conversion completion */
    ADC0_Value = ADC0_SSFIFO3_R;                                  /* This is the register that saves the value of the ADC*/

    return ADC0_Value;
}

uint16 ADC0_rightLDRAnalogReading(void)
{
    uint16 analogReading;

    SET_BIT(ADC0_PSSI_R , SAMPLE_SEQUENCER1);                  /* Initiate the ADC conversion for Sample Sequencer 1 */
    while(!GET_BIT(ADC0_RIS_R , SAMPLE_SEQUENCER1));           /* check for conversion completion */
    analogReading = ADC0_SSFIFO1_R;                            /* Read conversion result */
    SET_BIT(ADC0_ISC_R , SAMPLE_SEQUENCER1);                   /* Clear completion flag */

    return analogReading;
}

uint16 ADC0_leftLDRAnalogReading(void)
{
    uint16 analogReading;

    SET_BIT(ADC0_PSSI_R , SAMPLE_SEQUENCER2);                  /* Initiate the ADC conversion for Sample Sequencer 2 */
    while(!GET_BIT(ADC0_RIS_R , SAMPLE_SEQUENCER2));           /* check for conversion completion */
    analogReading = ADC0_SSFIFO2_R;                            /* Read conversion result */
    SET_BIT(ADC0_ISC_R , SAMPLE_SEQUENCER2);                   /* Clear completion flag */

    return analogReading;
}
