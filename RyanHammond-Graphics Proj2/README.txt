CONTROLS:
W,A,S,D,Q,E move the bear around the scene


Transparency: Multiple amounts of blend transparency.  The two barrels in the scene have different alpha valuse which are difined in their color values.

Transparency: Multiple objects (draw order).  I couldn't implement this because of the way I have set up the drawing of my scene at the moment. Ran out of time to create a sort for my sceneGraph(tree).

Discard transparency: Used the simple fence example.  Created a uniform bool to tell the shader if the object has an "alphaMask" and then uses the alpha mask to do discard transparency.

At least three models must have a combination of two or more textures.  The lamps are variations of different metal textures with some of them mixing with a rusty texture.  The fence uses the mixture of two texture as described above.  The brick wall has a graffiti-like texture ontop of it(didn't turn out quite how I wanted it).

Lots and lots of light: each lamp post has 2 lights placed at the location of the lamps themselves.  As well as one light placed above the scene to act as a "sun" giving off white light.

Ability to show some "debugging info".  press 'F' to turn on wireframe, 'G' to turn it off. 'C' to use lighting, 'V' to use debug colors.