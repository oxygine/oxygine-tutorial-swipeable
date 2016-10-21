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

    getStage()->addEventListener(TouchEvent::TOUCH_DOWN, [=](Event* ev) {
        log::messageln("touch down");

        TouchEvent *touch = (TouchEvent*)ev;
        downPos = touch->localPosition;
        pressed = true;
    });


    getStage()->addEventListener(TouchEvent::TOUCH_UP, [=](Event*) {
        log::messageln("touch up");
        //sprite->addTween(Actor::TweenX(0), 1000);
        pressed = false;
    });

    getStage()->addEventListener(TouchEvent::MOVE, [=](Event* ev) {
        if (!pressed)
            return;

        TouchEvent *touch = (TouchEvent*)ev;
        Vector2 dir = touch->localPosition - downPos;
        if (dir.x < -50)
        {
            pressed = false;
            log::messageln("swipe left");
            sprite->addTween(Actor::TweenX(sprite->getX() - sprite->getWidth()), 300);
        }
        if (dir.x > 50)
        {
            pressed = false;
            log::messageln("swipe right");
            sprite->addTween(Actor::TweenX(sprite->getX() + sprite->getWidth()), 300);
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
