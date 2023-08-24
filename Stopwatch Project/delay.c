/*
 * delay.c
 *
 *  Created on: Aug 19, 2023
 *      Author: ZYZ
 */
#include "std_types.h"

void _delay_ms(uint32 n)
{
    uint32 i,j;
    for(i=0; i<n ; i++)
        for(j=0;j<3180;j++)
        {}
}
