#include <GameState.h>

singleton class PongState : GameState
{
	/// Manager for the pong game's logic
    PongManager pongManager;

	/// Method to get the singleton instance
    /// @return PongState singleton
    static PongState getInstance();

	/// Prepares the object to enter this state.
	/// @param owner: Object that is entering in this state
	override void enter(void* owner);

    /// Prepares the object to exit this state.
    /// @param owner: Object that is exiting this state
    override void exit(void* owner);

	/// Process the provided user input.
    /// @param userInput: Struct with the current user input information
    override void processUserInput(const UserInput* userInput);
}