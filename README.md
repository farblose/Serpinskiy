## sierpinski
The most effecient Sierpinski triangle chaos game method generator written in C++.

Chaos game method for Sierpinski triangle generation is described not formally by the following algorithm:
1. Select three distinct points in a plane and construct an initial triangle with these as the vertices.
2. Select randomly an initial point inside the triangle area and designate it as a main position.
3. Select randomly one of the three triangle vertices.
4. Select as a new main position a middle point in between the main position and the chosen vertex.
5. Repeat steps 3 through 4 iteratively.

## Installation
```bash
git clone -q https://github.com/farblose/sierpinski.git && \
cd sierpinski && \
sudo apt-get install -y libsfml-dev > /dev/null 2&1 && \
g++ -o sierpinski main.cpp -lsfml-graphics -lsfml-window -lsfml-system > /dev/null && \
chmod ugo+x sierpinski && \
echo 'Installation is complete'
```

## Usage
```bash
./sierpinski
```
