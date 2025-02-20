/*
 * Pong
 *
 * © Jason Mazurek
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// INCLUDES
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

#include <string.h>

#include <Camera.h>
#include <CameraEffectManager.h>
#include <KeypadManager.h>
#include <PongState.h>
#include <Singleton.h>
#include <VUEngine.h>

// #include <Camera.h>
// #include <CameraEffectManager.h>
// #include <I18n.h>
// #include <Languages.h>
// #include <Printer.h>
// #include <Singleton.h>
// #include <VIPManager.h>
// #include <VUEngine.h>

#include "TitleScreenState.h"

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' DECLARATIONS
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

extern StageROMSpec TitleScreenStageSpec;

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' PUBLIC METHODS
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void TitleScreenState::enter(void* owner __attribute__((unused)))
{
	Base::enter(this, owner);

	// Load stage
	TitleScreenState::configureStage(this, (StageSpec*)&TitleScreenStageSpec, NULL);

	// Start clocks to start animations
	TitleScreenState::startClocks(this);

	// Print text
	// TitleScreenState::print(this);

	// Enable user input
	KeypadManager::enable();

	// Start fade in effect
	Camera::startEffect(Camera::getInstance(), kHide);
	Camera::startEffect
	(
		Camera::getInstance(),
		kFadeTo,	   // effect type
		0,			   // initial delay (in ms)
		NULL,		   // target brightness
		__FADE_DELAY,  // delay between fading steps (in ms)
		NULL		   // callback scope
	);
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void TitleScreenState::suspend(void* owner)
{
	Camera::startEffect(Camera::getInstance(), kFadeOut, __FADE_DELAY);

	Base::suspend(this, owner);
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void TitleScreenState::resume(void* owner)
{
	Base::resume(this, owner);

	// Print text
	TitleScreenState::print(this);

	// Enable user input
	KeypadManager::enable();

	Camera::startEffect(Camera::getInstance(), kHide);
	Camera::startEffect
	(
		Camera::getInstance(),
		kFadeTo,	   // effect type
		0,			   // initial delay (in ms)
		NULL,		   // target brightness
		__FADE_DELAY,  // delay between fading steps (in ms)
		NULL		   // callback scope
	);
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void TitleScreenState::processUserInput(const UserInput* userInput)
{
	if(0 != (K_STA & userInput->pressedKey))
    {
        // Disable the keypad to prevent processing of more inputs
        KeypadManager::disable();

        // Tell the VUEngine to change the current state
        VUEngine::changeState(GameState::safeCast(PongState::getInstance()));
    }
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' PRIVATE METHODS
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void TitleScreenState::constructor()
{
	// Always explicitly call the base's constructor
	Base::constructor();
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void TitleScreenState::destructor()
{
	// Always explicitly call the base's destructor
	Base::destructor();
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void TitleScreenState::print()
{
	Printer::text("A Pong Clone", (__SCREEN_WIDTH_IN_CHARS >> 1) - 6, 12, "VirtualBoyExt");
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
