#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <cmath>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;

std::random_device random_device;
std::mt19937 generator(random_device());
std::uniform_int_distribution<> x_dist(0, WINDOW_WIDTH);
std::uniform_int_distribution<> y_dist(0, WINDOW_HEIGHT);
std::uniform_int_distribution<> top_dist(0, 2);

struct Point {
    float x, y;
};

class Triangle {
public:
    Point pnt[3];

    explicit Triangle(Point f, Point s, Point t) {
        pnt[0] = f;
        pnt[1] = s;
        pnt[2] = t;
    }

    // Calculate the area of the triangle
    float area() const {
        return std::fabs((pnt[0].x * (pnt[1].y - pnt[2].y) + pnt[1].x * (pnt[2].y - pnt[0].y) + pnt[2].x * (pnt[0].y - pnt[1].y)) / 2.0f);
    }

    // Check if a point is inside the triangle
    bool isInside(const Point& p) const {
        float trngl = this->area();
        float A = std::fabs((p.x * (pnt[1].y - pnt[2].y) + pnt[1].x * (pnt[2].y - p.y) + pnt[2].x * (p.y - pnt[1].y)) / 2.0f);
        A += std::fabs((pnt[0].x * (p.y - pnt[2].y) + p.x * (pnt[2].y - pnt[0].y) + pnt[2].x * (pnt[0].y - p.y)) / 2.0f);
        A += std::fabs((pnt[0].x * (pnt[1].y - p.y) + pnt[1].x * (p.y - pnt[0].y) + p.x * (pnt[0].y - pnt[1].y)) / 2.0f);
        return std::fabs(trngl - A) < 1e-5; // Allowable error
    }
};

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Sierpinski Triangle");
    if (!window.isOpen()) {
        std::cerr << "Error creating window\n";
        return 1;
    }
    window.setFramerateLimit(0);

    // Define the vertices of the triangle
    Triangle trngl({100, 100}, {700, 100}, {400, 700});
    Point p;

    // Initialize font and text
    sf::Font font;
    if (!font.loadFromFile("Inter-Regular.otf")) {
        std::cerr << "Error loading font\n";
        return 1;
    }

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setPosition(10, 10);

    unsigned int pointCount = 0;

    // Find an initial point inside the triangle
    do {
        p = { static_cast<float>(x_dist(generator)), static_cast<float>(y_dist(generator)) };
    } while (!trngl.isInside(p));

    // Create render texture for drawing points
    sf::RenderTexture renderTexture;
    if (!renderTexture.create(WINDOW_WIDTH, WINDOW_HEIGHT)) {
        std::cerr << "Error creating render texture\n";
        return 1;
    }
    renderTexture.clear(sf::Color::Black);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Choose a random vertex of the triangle
        int top_triangle = top_dist(generator);
        float new_x = (trngl.pnt[top_triangle].x + p.x) / 2.0f;
        float new_y = (trngl.pnt[top_triangle].y + p.y) / 2.0f;

        // Create a new point at the midpoint between the current point and the chosen vertex
        sf::CircleShape point(0.5);
        point.setPosition(new_x, new_y);

        // Update the current point to the new point
        p.x = new_x;
        p.y = new_y;

        // Increment the point counter and update the text
        pointCount++;
        text.setString("Points: " + std::to_string(pointCount));

        // Draw the new point on the render texture
        renderTexture.draw(point);
        renderTexture.display();

        // Clear the window and draw the render texture as a sprite
        window.clear();
        sf::Sprite sprite(renderTexture.getTexture());
        window.draw(sprite);
        
        // Draw the text
        window.draw(text);

        window.display();
    }

    return 0;
}
