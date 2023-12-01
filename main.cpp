#include <SFML/Graphics.hpp>


int main(void) {


    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML PNG Display");

    // Load a texture from a PNG file
    sf::Texture texture;
    if (!texture.loadFromFile("path/to/your/image.png")) {
        // Error handling if the image file cannot be loaded
        return -1;
    }

    // Create a sprite and set its texture
    sf::Sprite sprite;
    sprite.setTexture(texture);

    // Main loop
    while (window.isOpen()) {
        // Handle events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Clear the window
        window.clear();

        // Draw the sprite
        window.draw(sprite);

        // Display the contents of the window
        window.display();
    }

    return 0;
}