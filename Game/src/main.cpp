#include "Game.h" 

int main(int argc, char** argv)
{
    Game game;
    game.Init();
    game.Update();
    game.Close();

    return 0;
}