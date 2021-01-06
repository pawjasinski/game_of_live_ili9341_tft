#include "board.h"
#include <cstdint>
#include <cstdlib>
#include <set>
/*
8 bitow 00000001 - oznacza np zywa komorke z 0 sasiadow
8 bitow 000xxxx1 - x oznaczaja liczbe sasiadow 0 - 8 (0-15) // 4 bity, bo zakres 0-8(9 wartosci) nie zmiesci mi sie w 3 bitach (0-7)(8 wartosci)
if nieparzysta
    compress = liczba sasiadow * 2 + 1
    przesuwamy bity o 1 w lewo i dodajemy na koncu 1
    liczba sasiadow = (compress - 1) / 2
    lub przesuwamy bity o 1 w prawo
if nieparzysta
    compress = liczba sasiadow * 2
    przesuwamy bity o 1 w lewo i dodajemy na koncu 0
    liczba sasiadow = compress / 2
    lub przesuwamy bity o 1 w prawo


*/

Board::Board()
{
    table = new uint8_t[boardX * boardY];
}

Board::~Board()
{
}

void Board::start(uint16_t numOfCells)
{
    std::set<uint16_t> rndTable;
    while(rndTable.size() != numOfCells)
    {
        // TO DO better random generator
        uint16_t t = rand() % (boardX * boardY);
        rndTable.insert(t);
    }
    for(std::set<uint16_t>::iterator it = rndTable.begin(); it != rndTable.end(); ++it)
    {
        birthCell(*it);
    }
}

void Board::updateNeighborhood(int16_t ind, bool choice)
{
    if(ind >= boardX*boardY || ind < 0)
        return;
    if(choice)
    {
        *(table + ind) += 2;
    }
    else
    {
        if((*(table + ind) >> 1) > 0)
            *(table + ind) -= 2;
    }
}

void Board::deathCell(uint16_t index)
{
    if(index >= boardX*boardY)
        return;

    if(*(table + index) % 2 == 1)
        *(table + index) -= 1;

    updateNeighborhood(index, false);
    updateNeighborhood(index + 1, false);
    updateNeighborhood(index - 1, false);
    updateNeighborhood(index - boardX, false);
    updateNeighborhood(index - boardX - 1, false);
    updateNeighborhood(index - boardX + 1, false);
    updateNeighborhood(index + boardX, false);
    updateNeighborhood(index + boardX - 1, false);
    updateNeighborhood(index + boardX + 1, false);
}

void Board::birthCell(uint16_t index)
{
    if(index >= boardX*boardY)
        return;

    if(*(table + index) == 0)
        *(table + index) += 1;
    
    updateNeighborhood(index, true);
    updateNeighborhood(index + 1, true);
    updateNeighborhood(index - 1, true);
    updateNeighborhood(index - boardX, true);
    updateNeighborhood(index - boardX - 1, true);
    updateNeighborhood(index - boardX + 1, true);
    updateNeighborhood(index + boardX, true);
    updateNeighborhood(index + boardX - 1, true);
    updateNeighborhood(index + boardX + 1, true);
}

bool Board::nextStep()
{
    // to do check if is no other steps and return false
    for(uint16_t i = 0; i < boardX*boardY; ++i)
    {
        if(*(table + i) %2 == 0 &&  *(table + i) >> 1 == 3)
        {
            birthCell(i);
            return true;
        }

        if(*(table + i) %2 == 1 && *(table + i) >> 1 != 2 && *(table + i) >> 1 != 3)
        {
            deathCell(i);
            return true;
        }
    }
    return false;
}