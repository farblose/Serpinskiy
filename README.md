## Sierpinski
The most effecient Sierpinski triangle chaos game method generator written in C++.

![alt text](https://raw.githubusercontent.com/farblose/Sierpinski/main/work.gif "Example")

Chaos game method for Sierpinski triangle generation is described not formally by the following algorithm:
1. Select three distinct points in a plane and construct an initial triangle with these as the vertices.
2. Select randomly an initial point inside the triangle area and designate it as a main position.
3. Select randomly one of the three triangle vertices.
4. Select as a new main position a middle point in between the main position and the chosen vertex.
5. Repeat steps 3 and 4 iteratively.

## Install and run without CMake
```bash
git clone -q https://github.com/farblose/Sierpinski.git && \
cd Sierpinski && \
sudo apt-get install -y libsfml-dev > /dev/null 2>&1 && \
g++ -o sierpinski main.cpp -lsfml-graphics -lsfml-window -lsfml-system > /dev/null && \
chmod ugo+x sierpinski && \
./sierpinski
```
## Install and run with CMake
```bash
git clone -q https://github.com/farblose/Sierpinski.git && \
cd Sierpinski/build && \
cmake .. && \
make && \
./main
```
