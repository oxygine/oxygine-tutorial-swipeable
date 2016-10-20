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


    spSprite sprite = new Sprite;
    ResAnim *img = gameResources.getResAnim("img1");
    sprite->setResAnim(img);
    sprite->attachTo(getStage());    

    sprite->addEventListener(TouchEvent::TOUCH_DOWN, [=](Event*) {
        log::messageln("touch down");
        sprite->addTween(Actor::TweenX(500), 500);
    });


    sprite->addEventListener(TouchEvent::TOUCH_UP, [=](Event*) {
        log::messageln("touch up");
        sprite->addTween(Actor::TweenX(0), 1000);
    });
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
