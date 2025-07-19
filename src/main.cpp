#include "imgui.h"
#include "imgui-SFML.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "BNW");
    window.setFramerateLimit(60);
    if (!ImGui::SFML::Init(window))
        return -1;

    // load a font
    sf::Font font("assets/NotoSansJP-VariableFont_wght.ttf");

    // run the program as long as the window is open
    sf::Clock deltaClock;
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        while (const std::optional event = window.pollEvent())
        {
            ImGui::SFML::ProcessEvent(window, *event);
            // "close requested" event: we close the window
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        ImGui::SFML::Update(window, deltaClock.restart());
        ImGui::ShowDemoWindow();

        ImGui::Begin("Hello, world!");
        ImGui::Button("Look at this pretty button");
        ImGui::End();

        // clear the window with black color
        window.clear(sf::Color::Black);

        // create a 500x500 render-texture
        sf::RenderTexture renderTexture({ 500, 500 });

        // drawing uses the same functions
        renderTexture.clear();

        sf::Text text(font);
        const std::wstring t = L"こんにちは";
        text.setString(t);

        text.setCharacterSize(24);
        text.setFillColor(sf::Color::White);
        text.setStyle(sf::Text::Bold);


        window.draw(text);
        ImGui::SFML::Render(window);

        // end the current frame
        window.display();
    }

    ImGui::SFML::Shutdown();
}