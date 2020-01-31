This is a proof of concept for a simple idea I had that worked wonderfully. The idea was that the player would play a basic platformer on wasd but would have to pan the screen themselves using the mouse. Despite the interesting mechanic, I never got around to more than a basic test level.

I'm quite pleased with my method of checking/executing collisions:
1. Find the trajectory of the player.
2. Find any platforms nearby which the play could plausably hit.
3. Check each of these for intersection (determined by simple check.
4. If a collision is found, calculate the point and add it to a list.
5. Find the closest point in the list to the player and move the player there.

My method of checking intersection between two segments was the betwixt funtion:

bool ccw(Vector2f a, Vector2f b, Vector2f c) {
    return (c.y-a.y)*(b.x-a.x) > (b.y-a.y)*(c.x-a.x);
}

bool betwixt(Vector2f a, Vector2f b, Vector2f c, Vector2f d) {
    return ccw(a, c, d) != ccw(b, c, d) && ccw(a, b, c) != ccw(a, b, d);
}

ccw() determines whether points a, b, and c are counter clockwise in the order abc. Betwixt takes in a and b, the two end points of l1 and c and d, the two end point of l2. Because betwixt can calculate whether the two lines cross each other without calculating any points on either line(without multiplication or division) it executes much faster that my previous method.





