#include "LineEdit.h"
#include <iostream>

using namespace sf;
using namespace featureLineEdit;

lineEdit::lineEdit(::sf::Vector2f const& position, Assets &assets)
{
	BoxInitialize(position);
	TextInitialize(position, assets);
}

void lineEdit::BoxInitialize(::sf::Vector2f const& position)
{
	box.setSize(SIZE_LINE_EDIT);
	box.setFillColor(BACK_COLOR_NOT_CHANGED);

	box.setOutlineThickness(THIKNESS);
	box.setOutlineColor(BORDER_COLOR_NOT_CHANGED);
	box.setPosition(position);
}

void lineEdit::TextInitialize(Vector2f const& position, Assets & assets)
{
	Vector2f positionText = { position.x + SHIFT_TEXT, position.y };
	text.setPosition(positionText);
	text.setFont(assets.fontMain);
	text.setCharacterSize(SIZE_TEXT);

	text.setString("");
}

bool lineEdit::DoesHit(sf::Vector2f const& point) const
{
	return box.getGlobalBounds().contains(point);
}

void lineEdit::Draw(RenderWindow& window)
{
	window.draw(box);
	window.draw(text);
}

bool lineEdit::mouseButtonHits(Event const& event)
{
	Vector2f mousePoint(float(event.mouseButton.x), float(event.mouseButton.y));
	return (event.mouseButton.button == sf::Mouse::Left) && DoesHit(mousePoint);
}

bool lineEdit::mouseMoveHits(Event const& event)
{
	Vector2f mousePoint(float(event.mouseMove.x), float(event.mouseMove.y));
	return DoesHit(mousePoint);
}

bool lineEdit::OnEvent(const Event& event)
{
	switch (event.type) {
	case Event::MouseMoved:
		if (state != Focus) {
			SetState(mouseMoveHits(event) ? Hovered : NoFocus);
		}
		break;
	case Event::MouseButtonReleased:
		if (state == Hovered) {
			SetState(mouseButtonHits(event) ? Focus : NoFocus);
			return true;
		}
		else if (state == Focus) {
			SetState(mouseButtonHits(event) ? Focus : NoFocus);
			return true;
		}
		break;
	case Event::TextEntered:
		if (state == Focus) {
			enterText(event);
		}
		break;
	case Event::KeyPressed:
		if(event.key.code == sf::Keyboard::BackSpace) {
			if (state == Focus) {
				deleteText();
			}
		}
		break;
	default:
		break;
	}

	return false;
}

void lineEdit::SetState(State newState)
{
	state = newState;
	switch (newState) {
	case NoFocus:
		box.setFillColor(BACK_COLOR_NOT_CHANGED);
		box.setOutlineColor(BORDER_COLOR_NOT_CHANGED);
		text.setColor(BORDER_COLOR_NOT_CHANGED);
		break;
	case Hovered:
		box.setFillColor(BACK_COLOR_HOVERED);
		box.setOutlineColor(BORDER_COLOR_HOVERED);
		text.setColor(BORDER_COLOR_HOVERED);
		break;
	case Focus:
		box.setFillColor(BACK_COLOR_CHANGED);
		box.setOutlineColor(BORDER_COLOR_CHANGED);
		text.setColor(BORDER_COLOR_CHANGED);
		break;
	}
}

void lineEdit::enterText(Event const& event)
{
	std::wstring currentString = text.getString();

	wchar_t inputChar = event.text.unicode;

	if (iswprint(inputChar)) {
		currentString += inputChar;

		// Делим на 2 чтобы получить нужный размер
		unsigned int characterSize = text.getCharacterSize() / 2;
		size_t sizeString = (currentString.size() + 2) * characterSize;
		if (sizeString < (SIZE_LINE_EDIT.x - THIKNESS * 5)) {
			text.setString(currentString);
		}
	}

}

void lineEdit::deleteText()
{
	String currentString = text.getString();
	size_t sizeString = currentString.getSize();
	if (sizeString) {
		currentString.erase(sizeString - 1);
		text.setString(currentString);
	}
}