#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;

std::random_device random_device;
std::mt19937 generator(random_device());
std::uniform_int_distribution<> x(0, WINDOW_WIDTH);
std::uniform_int_distribution<> y(0, WINDOW_HEIGHT);
std::uniform_int_distribution<> top(0, 2);

struct Point
{
    unsigned long x, y;
};

class Triangle
{
public:
    Point* pnt = new Point[3];
    Triangle(Point f, Point s, Point t)
    {
        pnt[0] = f;
        pnt[1] = s;
        pnt[2] = t;
    }
    float area()
    {
        return abs((pnt[0].x * (pnt[1].y - pnt[2].y) + pnt[1].x * (pnt[2].y - pnt[0].y) + pnt[2].x * (pnt[0].y - pnt[1].y)) / 2.0);
    }
    bool isInside(Point p)
    {
        float trngl = this->area();
        float A = abs((p.x * (pnt[1].y - pnt[2].y) + pnt[1].x * (pnt[2].y - p.y) + pnt[2].x * (p.y - pnt[1].y)) / 2.0);
        A += abs((pnt[0].x * (p.y - pnt[2].y) + p.x * (pnt[2].y - pnt[0].y) + pnt[2].x * (pnt[0].y - p.y)) / 2.0);
        A += abs((pnt[0].x * (pnt[1].y - p.y) + pnt[1].x * (p.y - pnt[0].y) + p.x * (pnt[0].y - pnt[1].y)) / 2.0);
        return trngl == A;
    }
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Serpinskiy triangle");
    window.setFramerateLimit(0);

    Triangle trngl({100, 100}, {700, 100}, {400, 700});
    Point p = {};
    
    while (true)
    {
        p = { x(generator), y(generator)};
        if (trngl.isInside(p))
        {
            break;
        }
    }

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            }
        }
        int top_triangle = top(generator);
        uint64_t x = (trngl.pnt[top_triangle].x + p.x) / 2;
        uint64_t y = (trngl.pnt[top_triangle].y + p.y) / 2;
        sf::CircleShape point(0.5);
        point.setOrigin(0, 0);
        point.setPosition(x, y);
        p = {x, y};
        window.draw(point);
        window.display();
    }
}