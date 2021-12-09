#pragma once

/* Base class for all User Interface elements. */
class UIElement
{
public:
	virtual ~UIElement() = default;

	/* Draws this UI element on application window. */
	virtual void Draw() = 0;
	/* Updates this UI element. */
	virtual void Update(float deltaTime) = 0;
};