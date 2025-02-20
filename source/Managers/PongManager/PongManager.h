#include <KeypadManager.h>
#include <ListenerObject.h>
#include <Stage.h>

class PongManager : ListenerObject
{
	/// @privatesection

	/// Scoring
	uint32 leftScore;
	uint32 rightScore;

	/// @publicsection

	/// Class' constructor
	void constructor(Stage stage);

	/// Class' destructor
	void destructor();

	// void printScore();

	/// Process an event that the instance is listen for.
    /// @param eventFirer: ListenerObject that signals the event
    /// @param eventCode: Code of the firing event
    /// @return False if the listener has to be removed; true to keep it
    override bool onEvent(ListenerObject eventFirer, uint16 eventCode);
}