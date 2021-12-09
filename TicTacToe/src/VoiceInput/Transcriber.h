#pragma once

#include <string>

#include "Engine/TicTacToe.h"

/* Helper class to transcribe recognized speech string into internal TTTMove struct. */
class Transcriber
{
public:
	/* Transcribes speech string into TTTMove structure. */
	static TTTMove Transcribe(const char* input);
};