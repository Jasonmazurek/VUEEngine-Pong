#include <string.h>

#include <Messages.h>
#include <Singleton.h>
#include <KeypadManager.h>
#include <PongManager.h>

#include "PongState.h"

extern StageROMSpec PongStageSpec;

void PongState::enter(void* owner __attribute__((unused)))
{
    Base::enter(this, owner);

    // Load stage
    PongState::configureStage(this, (StageSpec*)&PongStageSpec, NULL);

	// Create the Pong game controller
	this->pongManager = new PongManager(this->stage);

	// Start clocks to start animations
    PongState::startClocks(this);

	// Enable the user input
    KeypadManager::enable();
}

void PongState::exit(void* owner __attribute__((unused)))
{
    if(!isDeleted(this->pongManager))
    {
        delete this->pongManager;
    }

    this->pongManager = NULL;

    Base::exit(this, owner);
}

void PongState::processUserInput(const UserInput* userInput)
{
    if(0 != userInput->holdKey)
    {
        PongState::propagateMessage(this, kMessageKeypadHoldDown);
    }
}

void PongState::constructor()
{
    // Always explicitly call the base's constructor
    Base::constructor();

	this->pongManager = NULL;
}

void PongState::destructor()
{
    // Always explicitly call the base's destructor
    Base::destructor();
}