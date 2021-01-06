#include "game.h"
#include <cstdint>
#include <cstdio>



Game::Game()
{
    board = nullptr;
    displayContoller = nullptr;
    font = nullptr;
    play = false;
    round = 0;
}

Game::~Game()
{
    if(displayContoller != nullptr)
        delete displayContoller;
    if(board != nullptr)
        delete board;
    if(font != nullptr)
        delete font;
}

void Game::initialize()
{
    displayContoller = new SGLILI9341(PA_14, PA_13, PA_15, PC_12, PC_11, PC_10);
    board = new Board();
    Arial12x12Font* font = new Arial12x12Font();
    displayContoller->set_font(font);
    displayContoller->init();
    
}

void Game::start()
{
    play = true;
    board->start(800);
    while(play)
    {
        round++;
        if(board->nextStep())
        {
            //ok do nothing
        }
        else {
        {
            play = false;
        }
        }
// TO DO        
// Here we draw screen
        drawScreen();
        
        ThisThread::sleep_for(200);
    }
    // TO DO
    //displayContoller->drawBitmap(board->bufferDisplay());
    // TO DO
}
void Game::stop()
{
    play = false;
}
void Game::reset()
{
    play = false;
    if(board != nullptr)
        delete board;
    board = new Board();
}

void Game::drawScreen()
{
    displayContoller->fill_screen2(ILI9341_DARKGREY);
    char buff[30];
    // board;
    // displayContoller;
    int size_table = boardX*boardY;
    int16_t x=219;
    // rysujemy pionowe czarne linie
    while(x >= 19)
    {
        displayContoller->draw_vertical_line(x, 34, 250, 0x0000);
        x -= 4;
    }
    //rysujemy poziome czarne linie
    int16_t y = 285;
    while(y >= 33)
    {
        displayContoller->draw_horizontal_line(19, y, 200, 0x0000);
        y -= 4;
    }
    std::sprintf(buff, "Licznik: %d", round);
    displayContoller->draw_string(buff, 10, 10);
}