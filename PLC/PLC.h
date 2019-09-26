#ifndef _PLC_H
#define _PLC_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#define PLC_VERSION 3
#define X0 0
#define X1 1
#define X2 2
#define X3 3
#define X4 4


#define Y0 0
#define Y1 1
#define Y2 2
#define Y3 3


class PLC { 
public:
    PLC();
    ~PLC();

    void setDI(int AX0, int AX1, int AX2, int AX3, int AX4);
    void setDQ(int AY0, int AY1, int AY2, int AY3);
    void DQ(int addr, int value);
    int DI(int addr);
    void IOP();
    int VER();
};

#endif