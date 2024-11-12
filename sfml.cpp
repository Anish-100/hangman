#include <SFML/Graphics.hpp>

int main() {
    // Create a window
    sf::RenderWindow window(sf::VideoMode(800, 600), "House Drawing");

    // Wall of the house
    sf::RectangleShape wall(sf::Vector2f(200, 200));
    wall.setPosition(300, 300);
    wall.setFillColor(sf::Color(150, 75, 0));  // Brown color

    // Roof of the house
    sf::ConvexShape roof;
    roof.setPointCount(3);
    roof.setPoint(0, sf::Vector2f(275, 300));   // Left corner
    roof.setPoint(1, sf::Vector2f(525, 300));   // Right corner
    roof.setPoint(2, sf::Vector2f(400, 200));   // Top corner
    roof.setFillColor(sf::Color(139, 69, 19));  // Darker brown color

    // Door of the house
    sf::RectangleShape door(sf::Vector2f(50, 100));
    door.setPosition(375, 400);
    door.setFillColor(sf::Color(102, 51, 0));   // Dark brown color

    // Window of the house
    sf::RectangleShape window1(sf::Vector2f(50, 50));
    window1.setPosition(325, 325);
    window1.setFillColor(sf::Color::Blue);

    sf::RectangleShape window2(sf::Vector2f(50, 50));
    window2.setPosition(425, 325);
    window2.setFillColor(sf::Color::Blue);

    while (window.isOpen()) {
        // Process events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Clear the window
        window.clear(sf::Color::White);

        // Draw the house
        window.draw(wall);
        window.draw(roof);
        window.draw(door);
        window.draw(window1);
        window.draw(window2);

        // Display everything
        window.display();
    }

    return 0;
}
