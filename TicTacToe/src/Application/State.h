#pragma once

/*
	The base class for all states, which constructs the application finite state machine.
	Only direct member not designed to be implemented in derrived class is m_delete - flag whether this state is to be deleted from application stack.
*/
class State
{
public:
	virtual ~State() = default;

	virtual void Draw() = 0;
	virtual void Update(float deltaTime) = 0;

	bool IsDelete() const { return m_delete; };

protected:
	bool m_delete = false;
};