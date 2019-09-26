#include "PLC.h" //include the declaration for this class

int Y_BUF[8];
int X_BUF[8];

int X_ADDR[10];
int Y_ADDR[10];

//<<constructor>> setup the LED, make pin 13 an OUTPUT
void XInit()
{
    pinMode(X_ADDR[0], INPUT); //make that pin an OUTPUT
    pinMode(X_ADDR[1], INPUT); //make that pin an OUTPUT
    pinMode(X_ADDR[2], INPUT); //make that pin an OUTPUT
    pinMode(X_ADDR[3], INPUT); //make that pin an OUTPUT
    pinMode(X_ADDR[4], INPUT); //make that pin an OUTPUT
}

void YInit()
{
    pinMode(Y_ADDR[0], OUTPUT); //make that pin an OUTPUT
    pinMode(Y_ADDR[1], OUTPUT); //make that pin an OUTPUT
    pinMode(Y_ADDR[2], OUTPUT); //make that pin an OUTPUT
    pinMode(Y_ADDR[3], OUTPUT); //make that pin an OUTPUT


}


PLC::PLC(){
/* For SMC Training Kit */
    X_ADDR[0]=2;
    X_ADDR[1]=3;
    X_ADDR[2]=4;
    X_ADDR[3]=5;
    X_ADDR[4]=6;
     
    Y_ADDR[0]=7;
    Y_ADDR[1]=8;
    Y_ADDR[2]=9;
    Y_ADDR[3]=10;

    XInit();
    YInit(); 
}

void PLC::setDI(int AX0, int AX1, int AX2, int AX3, int AX4)
{
    X_ADDR[0]=AX0;
    X_ADDR[1]=AX1;
    X_ADDR[2]=AX2;
    X_ADDR[3]=AX3;
    X_ADDR[4]=AX4;
    XInit();

}

void PLC::setDQ(int AY0, int AY1, int AY2, int AY3)
{
    Y_ADDR[0]=AY0;
    Y_ADDR[1]=AY1;
    Y_ADDR[2]=AY2;
    Y_ADDR[3]=AY3;
    YInit(); 
}


//<<destructor>>
PLC::~PLC(){/*nothing to destruct*/}

int PLC::VER()
{
   
   return 100+PLC_VERSION;

}

void PLC::IOP()
{
   int X1_BUF[8];
   int X2_BUF[8];
   int X3_BUF[8];

   int i;
   int value;
   for (i=0; i < 4; i++)
   {
   	value= Y_BUF[i];
	if (value == 0) 
      	  digitalWrite(Y_ADDR[i],HIGH); //set the pin HIGH and thus turn LED on
        else
      	  digitalWrite(Y_ADDR[i],LOW); //set the pin HIGH and thus turn LED on
   }

   
   for (i=0; i < 5; i++)
     {
        X1_BUF[i]= digitalRead(X_ADDR[i]);
     }
   delay(5);
   for (i=0; i < 5; i++)
     {
        X2_BUF[i]= digitalRead(X_ADDR[i]);
     }
   delay(5);
   for (i=0; i < 5; i++)
     {
        X3_BUF[i]= digitalRead(X_ADDR[i]);
        if ((X1_BUF[i]+X2_BUF[i]+X3_BUF[i])>=2)
           X_BUF[i]=1;
        else
           X_BUF[i]=0;       

     }
 
}

void PLC::DQ(int addr, int value){
        Y_BUF[addr]=value;
}


int PLC::DI(int addr){
        return X_BUF[addr];

}