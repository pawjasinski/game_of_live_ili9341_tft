#ifndef __GAME_H___
#define __GAME_H___
#include "board.h"
#include "sgl_ili9341.h"
#include "Arial12x12.h"
#include <cstdint>

#define interval 1s // in miliseconds
#define cellDimension 5 // width and height one cell

class Game
{
public:
    Game();
    virtual ~Game();
    virtual void initialize();
    virtual void start();
    virtual void stop();
    virtual void reset();

    virtual void drawScreen();
protected:
    Board* board;
    SGLILI9341* displayContoller;
    bool play;
    uint16_t round;
    Arial12x12Font* font;

};


#endif