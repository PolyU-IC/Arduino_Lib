#include "PLC.h" //include the declaration for this class

int Y_BUF[8];
int X_BUF[8];

//<<constructor>> setup the LED, make pin 13 an OUTPUT
PLC::PLC(){
    pinMode(Y0+Y_OFS, OUTPUT); //make that pin an OUTPUT
    pinMode(Y1+Y_OFS, OUTPUT); //make that pin an OUTPUT
    pinMode(Y2+Y_OFS, OUTPUT); //make that pin an OUTPUT
    pinMode(Y3+Y_OFS, OUTPUT); //make that pin an OUTPUT

    pinMode(X0+X_OFS, INPUT); //make that pin an OUTPUT
    pinMode(X1+X_OFS, INPUT); //make that pin an OUTPUT
    pinMode(X2+X_OFS, INPUT); //make that pin an OUTPUT
    pinMode(X3+X_OFS, INPUT); //make that pin an OUTPUT
    pinMode(X4+X_OFS, INPUT); //make that pin an OUTPUT
}

//<<destructor>>
PLC::~PLC(){/*nothing to destruct*/}


void PLC::IOP()
{
   int X1_BUF[8];
   int X2_BUF[8];
   int X3_BUF[8];

   int i=0, value = 0;
   for (i=0; i < 4; i++)
      {
         value= Y_BUF[i];
        if (value == 0) 
          digitalWrite(i+Y_OFS,HIGH); //set the pin HIGH and thus turn LED on
        else
          digitalWrite(i+Y_OFS,LOW); //set the pin HIGH and thus turn LED on

      }   


   for (i=0; i < 5; i++)
     {
        X1_BUF[i]= digitalRead(i+X_OFS);
     }
   delay(5);
   for (i=0; i < 5; i++)
     {
        X2_BUF[i]= digitalRead(i+X_OFS);
     }
   delay(5);
   for (i=0; i < 5; i++)
     {
        X3_BUF[i]= digitalRead(i+X_OFS);
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