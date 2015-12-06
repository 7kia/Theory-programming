#pragma once
#include "Game.h"

const sf::FloatRect NULL_RECT = sf::FloatRect(0.f, 0.f, 0.f, 0.f);
bool isExitFromWindow(sf::FloatRect const& rectWindow, sf::FloatRect &rectObject);