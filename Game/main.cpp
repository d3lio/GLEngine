#include "engine.h"
#include "window.h"

//using namespace Engine;

Engine::Core engine("game.cfg");

int main (int argc, char** argv)
{
    engine.setWindowName("Game");
    engine.initGLFW();
    engine.initGLEW();
    int retVal = engine.renderLoop();
    
    return 0;
}
