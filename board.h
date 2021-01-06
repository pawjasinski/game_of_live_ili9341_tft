#ifndef __BOARD_H___
#define __BOARD_H___
#include "mbed.h"
#include <cstdint>

#define boardX 40
#define boardY 50
#define colorDead 0xC618; // light grey
#define colorLive 0x07E0; // green

struct Cell
{
    bool isAlive;
    uint8_t numOfNeighbors;
    Cell() { isAlive = false; numOfNeighbors = 0; }
};

class Board
{
protected:
    uint16_t numOfLines = boardX;
    uint16_t numOfColumns = boardY;

    // 0 means dead ,1 means live, in the next step we can compress this to the bytes
    uint8_t* table;

    uint16_t background = 0xFFFF; // Color white
    uint16_t grid = 0x0000;
    void deathCell(uint16_t index);
    void birthCell(uint16_t index);
    void updateNeighborhood(int16_t ind, bool choice);
public:
    Board();
    virtual ~Board();
    inline uint8_t* bufferDisplay() { return table; }
    void start(uint16_t numOfCells);
    bool nextStep();
};




#endif