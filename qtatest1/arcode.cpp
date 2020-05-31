
//api

static const int HIGH = 1, LOW = 0;
static const int INPUT = 0, OUTPUT = 1;

extern unsigned long millis();

extern void delay(unsigned long ms);

extern int digitalRead(int pin, int defVal = LOW);

extern void digitalWrite(int pin, int value);

void pinMode(int pin, int mode);

//CODE

//void _pre_setup() //non-api

#define _TEST_MODE

#include "/home/genya/Arduino/23.02.17/sketch_2ins_2outs/sketch_2ins_2outs.ino"
