#include <Actor.h>

mutation class Disk : Actor
{
	/// Make the animated actor ready to starts operating once it has been completely intialized.
    /// @param recursive: If true, the ready call is propagated to its children, grand children, etc.
    override void ready(bool recursive);

	/// Process a newly detected collision by one of the component colliders.
    /// @param collisionInformation: Information struct about the collision to resolve
    /// @return True if the collider must keep track of the collision to detect if it persists and when it
    /// ends; false otherwise
    override bool collisionStarts(const CollisionInformation* collisionInformation);

	/// Update this instance's logic.
    override void update();
}