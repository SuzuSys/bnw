#include "imgui.h"
#include "imgui-SFML.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <iostream>

int main()
{
    // create the window
    sf::ContextSettings settings;
    settings.antiAliasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({ 800, 600 }), 
        "BNW", 
        sf::Style::Default, 
        sf::State::Windowed, 
        settings);
    window.setFramerateLimit(60);
    
    // ImGui
    if (!ImGui::SFML::Init(window))
        return -1;

    // TGUI
    tgui::Gui gui{ window };
    tgui::Button::Ptr button = tgui::Button::create("Hello");
    button->setPosition("10%", "5%");
    button->setSize("30%", "10%");
    button->onPress([&] { std::cout << "pressed" << std::endl; });
    gui.add(button);

    // View
    sf::View view(sf::FloatRect({ 0,0 }, { 800,600 })); // x,y,dx,dy
    window.setView(view);

    // load a font
    sf::Font font("assets/NotoSansJP-VariableFont_wght.ttf");

    // window size
    unsigned int width = 800;
    unsigned int height = 600;

    // input space
    bool forcus_input = true;
    std::wstring str = L"こんにちは！";

    // run the program as long as the window is open
    sf::Clock deltaClock;
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        while (const std::optional event = window.pollEvent())
        {
            ImGui::SFML::ProcessEvent(window, *event);
            gui.handleEvent(*event);

            // "close requested" event: we close the window
            if (event->is<sf::Event::Closed>()) {
                window.close();
                break;
            }
            // window resize
            else if (const auto* resized = event->getIf<sf::Event::Resized>()) {
                width = resized->size.x;
                height = resized->size.y;
                sf::View view(sf::FloatRect({ 0.f,0.f }, { static_cast<float>(width), static_cast<float>(height) })); // x,y,dx,dy
                window.setView(view);
                std::cout << window.getSize().x << "," << window.getSize().y << std::endl;
            }

            // input letters
            else if (forcus_input) {
                if (const auto* textEntered = event->getIf<sf::Event::TextEntered>()) {
                    char32_t c = textEntered->unicode;
                    if (c == 8)
                        str.erase(str.end() - 1, str.end());
                    else
                        str += c;
                }
            }
        }
        ImGui::SFML::Update(window, deltaClock.restart());
        //ImGui::Begin("Hello, world!");
        //ImGui::Button("Look at this pretty button");
        //ImGui::End();

        // clear the window with black color
        window.clear(sf::Color::Black);

        // create a render-texture
        // sf::RenderTexture renderTexture({ width, height });

        // drawing uses the same functions
        // renderTexture.clear();

        sf::Text text(font);
        text.setString(str);
        text.setCharacterSize(std::round(0.1*height));
        text.setFillColor(sf::Color::White);
        text.setStyle(sf::Text::Bold);
        window.draw(text);

        sf::CircleShape shape(50);
        shape.setFillColor(sf::Color(100, 250, 50));
        window.draw(shape);

        gui.draw();
        ImGui::SFML::Render(window);
        // end the current frame
        window.display();
    }

    ImGui::SFML::Shutdown();
}