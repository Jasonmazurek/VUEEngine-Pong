#include <Body.h>

#include "AIPaddle.h"

mutation class AIPaddle;

void AIPaddle::update()
{
    Actor disk = Actor::safeCast(AIPaddle::getRelativeByName(this, "Disk"));

    if(!isDeleted(disk))
    {
        fixed_t forceMagnitude = 0;

        fixed_t diskYPosition = Actor::getPosition(disk)->y;

        if(__PIXELS_TO_METERS(2) < __ABS(diskYPosition - this->transformation.position.y))
        {
            if(diskYPosition < this->transformation.position.y)
            {
                forceMagnitude = -__FIXED_MULT(Body::getMass(this->body), Body::getMaximumSpeed(this->body));
            }
            else
            {
                forceMagnitude = __FIXED_MULT(Body::getMass(this->body), Body::getMaximumSpeed(this->body));
            }

            Vector3D force = {0, forceMagnitude, 0};

            AIPaddle::applyForce(this, &force, true);
        }
    }
}