#include  "CheckBox.h"

using namespace sf;
using namespace featureCheckBox;

checkBox::checkBox(Vector2f const& position)
{
	BoxInitialize(position);
	cross.Initialize(position, SIZE_CHECKBOX);
}

void checkBox::BoxInitialize(sf::Vector2f const& position)
{
	box.setSize(SIZE_CHECKBOX);
	box.setFillColor(BACK_COLOR_NOT_CHANGED);

	box.setOutlineThickness(THIKNESS);
	box.setOutlineColor(BORDER_COLOR_NOT_CHANGED);
	box.setPosition(position);
}

void Cross::Initialize(Vector2f const& position, Vector2f const& sizeBox)
{
	firstShape.setSize(SIZE_CROSS);
	firstShape.setFillColor(CROSS_COLOR);
	firstShape.setRotation(CROSS_ANGLE);
	firstShape.setOrigin(SIZE_CROSS.x / 2, SIZE_CROSS.y / 2);

	secondShape.setSize(SIZE_CROSS);
	secondShape.setFillColor(CROSS_COLOR);
	secondShape.setRotation(-CROSS_ANGLE);
	secondShape.setOrigin(SIZE_CROSS.x / 2, SIZE_CROSS.y / 2);

	Vector2f shiftToCenter = sizeBox;
	shiftToCenter.x /= 2;
	shiftToCenter.y /= 2;

	SetPosition(position, shiftToCenter);
}

void Cross::Draw(sf::RenderWindow& window)
{
	window.draw(firstShape);
	window.draw(secondShape);
}

void Cross::SetPosition(Vector2f const& position, Vector2f const& shiftToCenter)
{
	firstShape.setPosition(position);
	secondShape.setPosition(position);

	firstShape.move(shiftToCenter);
	secondShape.move(shiftToCenter);
}

bool checkBox::DoesHit(sf::Vector2f const& point) const
{
	return box.getGlobalBounds().contains(point);
}

void checkBox::Draw(RenderWindow& window)
{
	window.draw(box);

	if(state == Changed || state == HoveredChanged)
	{
		cross.Draw(window);
	}
}

bool checkBox::mouseButtonHits(Event const& event)
{
	Vector2f mousePoint(float(event.mouseButton.x), float(event.mouseButton.y));
	return (event.mouseButton.button == sf::Mouse::Left) && DoesHit(mousePoint);
}

bool checkBox::mouseMoveHits(Event const& event)
{
	Vector2f mousePoint(float(event.mouseMove.x), float(event.mouseMove.y));
	return DoesHit(mousePoint);
}

bool checkBox::OnEvent(const Event& event)
{
	switch (event.type) {
	case Event::MouseMoved:
		if (state != Changed && state != HoveredChanged) {
			SetState(mouseMoveHits(event) ? Hovered : NotChanged);
		}
		else {
			SetState(mouseMoveHits(event) ? HoveredChanged : Changed);
		}
		break;
	case Event::MouseButtonReleased:
		if (state == Hovered) {
			SetState(mouseButtonHits(event) ? HoveredChanged : NotChanged);
			return true;
		}
		else if(state == Changed) {
			if(mouseButtonHits(event))
			{
				SetState(Hovered);
			}
			return true;
		}
		else if (state == HoveredChanged) {
			SetState(mouseButtonHits(event) ? Hovered : Changed);
			return true;
		}
		else if (state == NotChanged) {
			if (mouseButtonHits(event)) {
				SetState(HoveredChanged);
			}
			return true;
		}
		break;
	default:
		break;
	}

	return false;
}

void checkBox::SetState(State newState)
{
	state = newState;
	switch (newState) {
	case NotChanged:
		box.setFillColor(BACK_COLOR_NOT_CHANGED);
		box.setOutlineColor(BORDER_COLOR_NOT_CHANGED);
		break;
	case Hovered:
		box.setFillColor(BACK_COLOR_HOVERED);
		box.setOutlineColor(BORDER_COLOR_HOVERED);
		break;
	case Changed:
		box.setFillColor(BACK_COLOR_CHANGED);
		box.setOutlineColor(BORDER_COLOR_CHANGED);
		cross.firstShape.setFillColor(BORDER_COLOR_CHANGED);
		cross.secondShape.setFillColor(BORDER_COLOR_CHANGED);

		break;
	case HoveredChanged:
		box.setFillColor(BACK_COLOR_HOVERED_CHANGED);
		box.setOutlineColor(BORDER_COLOR_HOVERED_CHANGED);
		cross.firstShape.setFillColor(BORDER_COLOR_HOVERED_CHANGED);
		cross.secondShape.setFillColor(BORDER_COLOR_HOVERED_CHANGED);
		break;
	}
}

bool checkBox::IsChecked() const
{
	if(state == Changed || state == HoveredChanged)
	{
		return true;
	}
	return false;
}
