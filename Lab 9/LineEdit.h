#pragma once
#include <SFML/Graphics.hpp>
#include "Assets.h"

namespace featureLineEdit
{
	const sf::Vector2f SIZE_LINE_EDIT = { 175.f, 25.f };
	const float THIKNESS = 3.f;

	const sf::Color BACK_COLOR_NOT_CHANGED(255, 255, 255, 255);
	const sf::Color BORDER_COLOR_NOT_CHANGED(0, 200, 0, 255);

	const sf::Color BACK_COLOR_HOVERED(255, 200, 200, 255);
	const sf::Color BORDER_COLOR_HOVERED(200, 200, 0, 255);

	const sf::Color BACK_COLOR_CHANGED(255, 255, 255, 255);
	const sf::Color BORDER_COLOR_CHANGED(0, 200, 200, 255);

	const unsigned int SIZE_TEXT = unsigned int(SIZE_LINE_EDIT.y - THIKNESS * 2);
	const int SHIFT_TEXT = int(THIKNESS);
}

struct lineEdit {
	enum State {
		NoFocus,
		Hovered,
		Focus
	};

	sf::RectangleShape box;
	sf::Text text;

	void BoxInitialize(sf::Vector2f const& position);
	void TextInitialize(sf::Vector2f const& position, Assets &assets);

	lineEdit(sf::Vector2f const& position, Assets &assets);
	bool DoesHit(sf::Vector2f const& point) const;

	void Draw(sf::RenderWindow &window);

	bool mouseButtonHits(sf::Event const& event);
	bool mouseMoveHits(sf::Event const& event);
	bool OnEvent(sf::Event const& event);
	void SetState(State newState);

	void enterText(sf::Event const& event);
	void deleteText();
	State state;
};
