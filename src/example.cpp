#include "oxygine-framework.h"
#include <functional>
using namespace oxygine;

Resources gameResources;

void example_preinit() {}

//called from main.cpp
void example_init()
{
    //load xml file with resources definition
    gameResources.loadXML("res.xml");

}


//called each frame from main.cpp
void example_update()
{
}

//called each frame from main.cpp
void example_destroy()
{
    //free previously loaded resources
    gameResources.free();
}
