#ifndef __CELL__H_
#define __CELL__H_
#include "mbed.h"
#include <cstdint>

class Cell
{
protected:
    uint8_t numOfNeighbors;
    bool isAlive;
public:
    Cell();
    virtual ~Cell() {}
    inline bool getIsAlive() { return isAlive; }
};


#endif