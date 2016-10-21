#include "oxygine-framework.h"
#include <functional>
using namespace oxygine;

Resources gameResources;

void example_preinit() {}

//called from main.cpp
bool pressed = false;
Vector2 downPos(0,0);

void example_init()
{
    //load xml file with resources definition
    gameResources.loadXML("res.xml");


    spSprite sprite = new Sprite;
    ResAnim *img = gameResources.getResAnim("img1");
    sprite->setResAnim(img);
    sprite->attachTo(getStage());    

    sprite->addEventListener(TouchEvent::TOUCH_DOWN, [=](Event* ev) {
        log::messageln("touch down");

        TouchEvent *touch = (TouchEvent*)ev;
        downPos = touch->localPosition;
        pressed = true;
    });


    sprite->addEventListener(TouchEvent::TOUCH_UP, [=](Event*) {
        log::messageln("touch up");
        //sprite->addTween(Actor::TweenX(0), 1000);
        pressed = false;
    });

    sprite->addEventListener(TouchEvent::MOVE, [=](Event* ev) {
        if (!pressed)
            return;

        TouchEvent *touch = (TouchEvent*)ev;
        Vector2 dir = downPos - touch->localPosition;
        if (dir.x < -50)
        {
            pressed = false;
            log::messageln("swipe right");
        }
        if (dir.x > 50)
        {
            pressed = false;
            log::messageln("swipe left");
        }
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
