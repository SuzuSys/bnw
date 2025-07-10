#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <filesystem>
#include <iostream>

int main()
{
    sf::ContextSettings settings;
	settings.antiAliasingLevel = 4;
	sf::Window window(sf::VideoMode({ 800, 600 }), "BNW", sf::Style::Default, sf::State::Windowed);

    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);

	window.setActive(true);

    // load resources, initialize the OpenGL states, ...

    bool running = true;
    while (running)
    {
        // handle events
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                running = false;
            }
            else if (const auto* resized = event->getIf<sf::Event::Resized>()) {
                // adjust the viewport when the window is resized
                glViewport(0, 0, resized->size.x, resized->size.y);
            }
        }
        // clear the buffers
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // draw...

        window.display();
    }

    // release resources...
}
