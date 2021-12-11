#include "Game.h"


int main()
{
    // Window
    Game game;
    //Game
    while (game.running())
    {

        //Update
        game.update();

        //Render
        game.render();

    }

    return 0;
}