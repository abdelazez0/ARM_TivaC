/*
 * adc.h
 *
 *  Created on: Sep 10, 2023
 *      Author: Mohamed Abdelazez
 */

#ifndef MCAL_ADC_H_
#define MCAL_ADC_H_

#define ADC0_BASE                0
#define ADC1_BASE                1

#define SAMPLE_SEQUENCER0        0
#define SAMPLE_SEQUENCER1        1
#define SAMPLE_SEQUENCER2        2
#define SAMPLE_SEQUENCER3        3

#define PROCESSOR_TRIGGER        0x0
#define ALWAYS_TRIGGERED         0xF

#define ADC_CTL_END              1
#define ADC_CTL_IE               2

void ADC0_initLDR(void);

void ADC0_initTempSensor(void);

uint16 ADC0_TempSensorAnalogReading(void);

uint16 ADC0_rightLDRAnalogReading(void);

uint16 ADC0_leftLDRAnalogReading(void);

#endif /* MCAL_ADC_H_ */
