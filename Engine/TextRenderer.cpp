#include "TextRenderer.h"
#include "Engine.h"
#include "ResourceModule.h"

TextRenderer::TextRenderer(std::string path, std::string string)
{

	ResourceModule* resourceModule = Engine::GetModule<ResourceModule>();
	sf::Font& font = resourceModule->GetFont(path);
	text = new sf::Text(font, string, 30);

};

void TextRenderer::Update(float dt)
{

	Transform& transform = owner->GetTransform();
	text->setPosition(transform.pos);
	text->setRotation(sf::degrees(transform.rot));
	text->setScale(transform.scale);
	text->setOrigin(sf::Vector2f(
		text->getLocalBounds().size.x * transform.origin.x,
		text->getLocalBounds().size.y * transform.origin.y
	));



}

void TextRenderer::Render(sf::RenderWindow* window)
{

	sf::View currentView = window->getView();
	window->setView(window->getDefaultView());

	window->draw(*text);

	window->setView(currentView);

}