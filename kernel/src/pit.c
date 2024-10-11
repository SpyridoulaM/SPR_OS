#include <stdint.h>
#include "utils.h"
#include "vga.h"
#include "pit.h"
#include "idt.h"

uint64_t ticks;
const uint32_t freq=100;

void onIrq0(struct InterruptRegisters* regs)
{
    ticks=ticks+1;
}

void initTimer()
{
    ticks=0;
    irq_install_handler(0,&onIrq0);

    //Ocilator at 1.1931816666 119318.16666 MHz
    //Timer will be off by a little bit so 16666 will not
    //make a lot of difference
    uint32_t divisor = 1193180/freq;

    //0x43 sets the mode of the timer 0011 1100
    //when the clock changes from 0 to 1 (rising edge) we get a tick
    outPortB(0x43,0x36);
    outPortB(0x40,(uint8_t)(divisor & 0xFF));
    outPortB(0x40,(uint8_t)((divisor >> 8) & 0xFF));
    //we send it in chunks
}