#include "ButtonRenderer.h"
#include "Engine.h"
#include "ResourceModule.h"
#include "WindowModule.h"
#include "InputModule.h"

ButtonRenderer::ButtonRenderer(std::string unhoveredPath, std::string hoveredPath, std::string string, std::function<void()> callback) :
	callback(callback)
{

	ResourceModule* resourceModule = Engine::GetModule<ResourceModule>();
	unhoveredTexture = &resourceModule->GetTexture(unhoveredPath);
	hoveredTexture = &resourceModule->GetTexture(hoveredPath);
	sprite = new sf::Sprite(*unhoveredTexture);

	sf::Font& font = resourceModule->GetFont("Assets/UI/Font.ttf");
	text = new sf::Text(font, string, 24);

};

void ButtonRenderer::Update(float dt)
{

	Transform& transform = owner->GetTransform();
	sprite->setPosition(transform.pos);
	sprite->setRotation(sf::degrees(transform.rot));
	sprite->setScale(transform.scale);

	text->setPosition(transform.pos - sf::Vector2f(0.f, 1.5f));
	text->setRotation(sf::degrees(transform.rot));
	text->setScale(transform.scale);
	text->setOrigin(text->getLocalBounds().size * 0.5f);

	// Vérifie si le bouton est survolé
	WindowModule* windowModule = Engine::GetModule<WindowModule>();
	sf::RenderWindow* window = windowModule->GetRenderWindow();
	sf::Vector2f mousePos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));

	if (sprite->getGlobalBounds().contains(mousePos))
	{

		sprite->setTexture(*hoveredTexture);
		text->setFillColor(sf::Color::Black);

	}
	else
	{

		sprite->setTexture(*unhoveredTexture);
		text->setFillColor(sf::Color::White);

	}

	// Si les deux états ont une taille différente, ça reste la même position
	// C'est pour ça que l'origin est appelé après le changement de texture
	sprite->setOrigin(sprite->getLocalBounds().size * 0.5f);

	// Vérifie si le bouton est cliqué
	InputModule* inputModule = Engine::GetModule<InputModule>();
	
	if (sprite->getGlobalBounds().contains(mousePos) && inputModule->Is(sf::Mouse::Button::Left, InputState::RELEASED))
		callback();

}

void ButtonRenderer::Render(sf::RenderWindow* window)
{

	window->draw(*sprite);
	window->draw(*text);

}