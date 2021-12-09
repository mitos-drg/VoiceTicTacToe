#pragma once

#include <SFML/Graphics.hpp>

/**
	\brief This namespace contains an application-level functions for tic-tac-toe game

	This namespace contains game main loop, as well as a initialization and cleanup instructions.
	It also is container for global-like scope object, is responsible for managing game and UI.
*/
namespace TicTacToe
{
	void Initialize();
	void Run();
	void Clean();
}