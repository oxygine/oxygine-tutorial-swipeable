#include "oxygine-framework.h"
#include <functional>
using namespace oxygine;

Resources gameResources;

void example_preinit() {}

//called from main.cpp
bool pressed = false;
Vector2 downPos(0,0);

int current = 0;
spSprite sprite;
const char* images[] = {"img1", "img2", "img3", "img4"};

void example_init()
{
    //load xml file with resources definition
    gameResources.loadXML("res.xml");


    sprite = new Sprite;
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
            
            spTween tween = sprite->addTween(Actor::TweenX(-sprite->getWidth()), 300);
            tween->setDetachActor(true);

            current = (current + 1) % 4;

            spSprite nextSprite = new Sprite;
            nextSprite->setResAnim(gameResources.getResAnim(images[current]));
            nextSprite->setX(sprite->getWidth());
            nextSprite->addTween(Actor::TweenX(0), 300);
            nextSprite->attachTo(getStage());
            sprite = nextSprite;
        }

        if (dir.x > 50)
        {
            pressed = false;
            log::messageln("swipe right");

            spTween tween = sprite->addTween(Actor::TweenX(sprite->getWidth()), 300);
            tween->setDetachActor(true);

            current = (current - 1 + 4) % 4;


            spSprite nextSprite = new Sprite;
            nextSprite->setResAnim(gameResources.getResAnim(images[current]));
            nextSprite->setX(- nextSprite->getWidth());
            nextSprite->addTween(Actor::TweenX(0), 300);
            nextSprite->attachTo(getStage());
            sprite = nextSprite;
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
