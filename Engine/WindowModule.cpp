#include "WindowModule.h"
#include "Engine.h"

void WindowModule::Init()
{

    window = new sf::RenderWindow(sf::VideoMode({ 1280, 720 }), "Ant Mario");

}

void WindowModule::Update()
{

    while (const std::optional event = window->pollEvent())
    {
        if (event->is<sf::Event::Closed>()) {
            Engine::GetInstance()->Stop();
            window->close();
        }

    }

    window->clear();

}

void WindowModule::Render()
{

    window->display();

}

sf::RenderWindow* WindowModule::GetRenderWindow()
{

    return window;

}