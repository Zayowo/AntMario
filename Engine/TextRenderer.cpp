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
	text->setOrigin(text->getLocalBounds().size * 0.5f);

}

void TextRenderer::Render(sf::RenderWindow* window)
{

	window->draw(*text);

}