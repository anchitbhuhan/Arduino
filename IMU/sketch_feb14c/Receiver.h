#ifndef Receiver_h
#define Receiver_h
#include "Arduino.h"


#define MPU6050_ADDRESS 0x68
#define MPU6050_REG_TEMP_OUT_H    (0x41)




class Receiver
{
    public:
                int readRegister16(byte reg);
};

#endif
