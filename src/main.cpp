#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "My window");

    // load a font
	sf::Font font("assets/NotoSansJP-VariableFont_wght.ttf");

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        while (const std::optional event = window.pollEvent())
        {
            // "close requested" event: we close the window
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        // clear the window with black color
        window.clear(sf::Color::Black);

        // create a 500x500 render-texture
        sf::RenderTexture renderTexture({ 500, 500 });

        // drawing uses the same functions
        renderTexture.clear();
        
        sf::Text text(font);
        text.setString(L"Ç±ÇÒÇ…ÇøÇÕê¢äEÅI");
		text.setCharacterSize(24);
		text.setFillColor(sf::Color::White);
		text.setStyle(sf::Text::Bold);
		window.draw(text);

        // end the current frame
        window.display();
    }
}
