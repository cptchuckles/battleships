/**
 * IDrawable interface for objects which can draw to screen.
 * I had to roll my own interface because sf::Drawable prevents
 * polymorphism.
 */

#pragma once

#include <SFML/Graphics.hpp>

class IDrawable
{
public:
	virtual void Draw(sf::RenderTarget& target) const = 0;
};
