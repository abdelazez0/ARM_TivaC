#ifndef GPTM_REGISTERS_H_
#define GPTM_REGISTERS_H_

#define GPTMCFG      *((volatile uint32*)(0x40031000))

#define GPTMTAMR     *((volatile uint32*)(0x40031004))
#define GPTMTAMR_TAMR            0
#define GPTMTAMR_TACDIR          4
#define GPTMTAMR_TAMIE           5

#define GPTMCTL      *((volatile uint32*)(0x4003100C))
#define GPTMCTL_TAEN             0
#define GPTMCTL_TASTALL          1

#define GPTMIMR      *((volatile uint32*)(0x40031018))
#define GPTMIMR_TATOIM       0

#define GPTMRIS      *((volatile uint32*)(0x4003101C))
#define GPTMRIS_TATORIS        0

#define GPTMTAILR    *((volatile uint32*)(0x40031028))

#define GPTMTAPR     *((volatile uint32*)(0x40031038))

#define GPTMTAV      *((volatile uint32*)(0x40031050))

#define GPTMICR      *((volatile uint32*)(0x40031024))
#define GPTMICR_TATOCINT     0

#endif
