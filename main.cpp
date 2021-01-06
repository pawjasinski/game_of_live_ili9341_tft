#include "mbed.h"
#include "game.h"

// main() runs in its own thread in the OS
int main()
{
    Game game;
    game.initialize();
    game.start();

    while (true) {
        ThisThread::sleep_for(1s);
    }
}

