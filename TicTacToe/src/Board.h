#pragma once

#include <cstdint>

struct Board
{
	uint8_t _board[9];

	uint16_t crosses;
	uint16_t circles;

	uint32_t hashKey;
};