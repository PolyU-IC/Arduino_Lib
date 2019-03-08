#ifndef _PLC_H
#define _PLC_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#define X_OFS 2
#define X0 0
#define X1 1
#define X2 2
#define X3 3
#define X4 4


#define Y_OFS 7
#define Y0 0
#define Y1 1
#define Y2 2
#define Y3 3
class PLC { 
public:
	PLC();
	~PLC();
    void DQ(int addr, int value);
    int DI(int addr);
    void IOP();
};

#endif