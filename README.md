## Sierpinski
The most effecient Sierpinski triangle chaos game method generator written in C++.

Chaos game method for Sierpinski triangle generation is described not formally by the following algorithm:
1. Select three distinct points in a plane and construct an initial triangle with these as his vertices.
2. Select randomly an initial point inside the triangle area and designate is as a current position.
3. Select randomly one of the three triangle vertices.
4. Move halfway from the "Main Position" to the chosen vertex and designate the resulting position as the current position.
5. Repeat steps 3 through 4 iteratively.
