#include <Body.h>
#include <InGameTypes.h>
#include <SoundManager.h>
#include <Sounds.h>

#include "Disk.h"

mutation class Disk;

void Disk::ready(bool recursive)
{
    Base::ready(this, recursive);

    if(isDeleted(this->body))
    {
        return;
    }

    int16 angle = Math::random(Math::randomSeed(), 64) - 32;

    Vector3D velocity =
    {
        __FIXED_MULT(Body::getMaximumSpeed(this->body), __FIX7_9_TO_FIXED(__COS(angle))),
        __FIXED_MULT(Body::getMaximumSpeed(this->body), __FIX7_9_TO_FIXED(__SIN(angle))),
        0
    };

    if(50 > Math::random(Math::randomSeed(), 100))
    {
        velocity.x = -velocity.x;
    }

    Disk::setVelocity(this, &velocity, false);
}

bool Disk::collisionStarts(const CollisionInformation* collisionInformation)
{
    bool returnValue = Base::collisionStarts(this, collisionInformation);

    Entity collidingEntity = Collider::getOwner(collisionInformation->otherCollider);

    switch(Entity::getInGameType(collidingEntity))
    {
        case kTypePaddle:
        {
            Vector3D velocity = *Body::getVelocity(this->body);

            fixed_t yDisplacement = this->transformation.position.y - Entity::getPosition(collidingEntity)->y;

            velocity.y += yDisplacement;

            Body::setVelocity(this->body, &velocity);
        }
		case kTypeWall:
        {
            SoundManager::playSound(&BounceSoundSpec,  NULL, kSoundPlaybackNormal, NULL);
        }

        break;
    }

    return returnValue;
}

/// Update this instance's logic.
void Disk::update()
{
	Body::print(this, 0,0);
}