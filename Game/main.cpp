#include "engine.h"
#include "window.h"

//using namespace Engine;

Engine::Core engine("Game", "game.cfg");

int main (int argc, char** argv)
{
    int retVal = engine.render();
    
    return 0;
}
