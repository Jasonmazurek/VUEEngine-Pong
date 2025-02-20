#include <string.h>

#include <GameEvents.h>
#include <Printer.h>
// #include <RumbleEffects.h>
// #include <RumbleManager.h>
#include <SoundManager.h>
#include <Sounds.h>

#include "PongManager.h"

void PongManager::constructor(Stage stage)
{
    // Always explicitly call the base's constructor
    Base::constructor();

    this->leftScore = 0;
    this->rightScore = 0;

    PongManager::printScore(this);

	if(!isDeleted(stage))
    {
        Actor disk = Actor::safeCast(Stage::getChildByName(stage, (char*)"Disk", false));

        if(!isDeleted(disk))
        {
            Actor::addEventListener(disk, ListenerObject::safeCast(this), kEventActorDeleted);
        }

        Stage::addActorLoadingListener(stage, ListenerObject::safeCast(this));
    }

	Printer::addEventListener(Printer::getInstance(), ListenerObject::safeCast(this), kEventFontRewritten);
}

void PongManager::destructor()
{
    // Always explicitly call the base's destructor
    Base::destructor();
}

void PongManager::printScore()
{
	Printer::int32(this->leftScore, 24 - 3, 0, NULL);
	Printer::int32(this->rightScore, 24 + 3, 0, NULL);
}

bool PongManager::onEvent(ListenerObject eventFirer __attribute__((unused)), uint16 eventCode)
{
    switch(eventCode)
    {
        case kEventActorDeleted:
        {
            if(0 == strcmp("Disk", Actor::getName(eventFirer)))
            {
				SoundManager::playSound(&PointSoundSpec,  NULL, kSoundPlaybackNormal, NULL);

                if(0 < Actor::getPosition(eventFirer)->x)
                {
                    this->leftScore++;
                }
                else
                {
                    this->rightScore++;
                }

                PongManager::printScore(this);
            }

            return false;
        }

        case kEventActorCreated:
        {
            if(0 == strcmp("Disk", Actor::getName(eventFirer)))
            {
                Actor::addEventListener(eventFirer, ListenerObject::safeCast(this), kEventActorDeleted);
            }

            return true;
        }

		case kEventFontRewritten:
        {
            PongManager::printScore(this);

            return true;
        }
    }

    return Base::onEvent(this, eventFirer, eventCode);
}