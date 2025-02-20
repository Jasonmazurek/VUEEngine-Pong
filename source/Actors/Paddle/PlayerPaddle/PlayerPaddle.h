#include <Actor.h>

mutation class PlayerPaddle : Actor
{
	/// Default interger message handler for propagateMessage
    /// @param message: Propagated integer message
    /// @return True if the propagation must stop; false if the propagation must reach other containers
    override bool handlePropagatedMessage(int32 message);
}