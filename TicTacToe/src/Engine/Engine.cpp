#include "Engine.h"

#include <vector>
#include <algorithm>

TTTEngine::TTTEngine(TTTPlayer startingPlayer)
	: m_board(), m_player(startingPlayer)
{
}

TTTEngine::~TTTEngine()
{
}

bool TTTEngine::CheckMove(TTTMove& move)
{
	printf("Checking move...\n");
	if (move.player != m_player) // check whether passed player matches current player to move
	{
		printf("Player does not match\n");
		return false;
	}

	if (move.place == TTTSquare::NoSquare) // check if destination square is valid
	{
		printf("No target square\n");
		return false;
	}

	if (m_board.occupied() & (1 << (uint8_t)move.place)) // check if destination square is empty
	{
		printf("The square was taken\n");
		return false;
	}

	return true;
}

TTTMove TTTEngine::GetBestMove(int maxPly)
{
	// Get all free fields in current board
	uint16_t freeFields = m_board.freeFields();
	int possibleMovesCount = CountBitboard(freeFields);

	// Create vectore to store all possible moves
	std::vector<TTTMove> possibleMoves(possibleMovesCount);
	int bestMoveId = 0;

	int alpha = -256, beta = 256;

	// Generate all possible moves.
	for (int i = 0; i < possibleMovesCount; i++)
	{
		possibleMoves[i] = { m_player, (TTTSquare)PopBitboard(&freeFields) };
	}

	// Perform minimax search for each move to find the best one.
	if (m_player == TTTPlayer::Circle)
	{
		int evaluationResult = -256; // worst possible scenario

		for (int i = 0; i < possibleMovesCount; i++)
		{
			TTTBoard nextPosition = m_board + possibleMoves[i];
			int minimaxResult = Minimax(&nextPosition, maxPly - 1, alpha, beta, false); // since we are circles we want to minimaze moves generated from next position (for Crosses)
			if (evaluationResult < minimaxResult) // if minimax result is greater that current evaluation we found better move
			{
				bestMoveId = i; // set index of best move found
				evaluationResult = minimaxResult; // update best evaluation result
			}
		}
	}
	else
	{
		int evaluationResult = 256;

		for (int i = 0; i < possibleMovesCount; i++)
		{
			TTTBoard nextPosition = m_board + possibleMoves[i];
			int minimaxResult = Minimax(&nextPosition, maxPly - 1, alpha, beta, true); // since we are crosses we want to maximalize moves generated from next position (for Circles)
			if (evaluationResult > minimaxResult) // if minimax result is smaller that current evaluation we found better move
			{
				bestMoveId = i; // set index of best move found
				evaluationResult = minimaxResult; // update best evaluation result
			}
		}
	}

	// return best move.
	return possibleMoves[bestMoveId];
}

int TTTEngine::PerformMove(TTTMove move)
{
	m_board += move; // actually perform move

	// change player
	if (m_player == TTTPlayer::Circle)
		m_player = TTTPlayer::Cross;
	else
		m_player = TTTPlayer::Circle;

	// Check for every win condition on both sides
	for (int i = 0; i < 8; ++i)
	{
		if ((m_board.crosses & winMask[i]) == winMask[i])
		{
			return 2;
		}
		else if ((m_board.circles & winMask[i]) == winMask[i])
		{
			return 1;
		}
	}

	// Check against draw
	if (m_board.occupied() == fullBoard)
		return 3;

	return 0;
}

TTTBoard* TTTEngine::GetBoard()
{
	return &m_board;
}

int TTTEngine::CountBitboard(uint16_t bitboard)
{
	int r = 0;
	for (r = 0; bitboard; r++, bitboard &= bitboard - 1);
	return r;
}

int TTTEngine::PopBitboard(uint16_t* bitboard)
{
	uint16_t leastbit = (*bitboard) & -(*bitboard);
	*bitboard &= (*bitboard - 1);

	return bitTable[((leastbit * 0x0d2f) >> 12) & 15];
}

int TTTEngine::EvaluatePosition(TTTBoard* board)
{
	// Check for every win condition on both sides
	for (int i = 0; i < 8; ++i)
	{
		if ((board->crosses & winMask[i]) == winMask[i])
		{
			return -256;
		}
		else if ((board->circles & winMask[i]) == winMask[i])
		{
			return 255;
		}
	}

	// Check against draw
	if ((board->circles | board->crosses) == fullBoard)
		return 0;

	int res = 0;

	// Count circles and crosses with field weights, circles are maximizing
	for (int i = 0; i < 9; ++i)
	{
		if (board->fields[i] == TTTPlayer::Circle) // is circle, so add
			res += fieldWeight[i];
		else if (board->fields[i] == TTTPlayer::Cross) // is cross, subtract
			res -= fieldWeight[i];
	}

	return res;
}

int TTTEngine::Minimax(TTTBoard* position, int depth, int& alpha, int& beta, bool maximizing) // maximizing for circles
{
	// Check for every win condition on both sides, if any occure return evaluation of it
	for (int i = 0; i < 8; ++i)
	{
		if ((position->crosses & winMask[i]) == winMask[i])
		{
			return -256;
		}
		else if ((position->circles & winMask[i]) == winMask[i])
		{
			return 255;
		}
	}
	// Check wether reached the maximum search depth or the game is over
	// and return evaluation of this position
	if (depth == 0 || position->occupied() == fullBoard)
		return EvaluatePosition(position);

	// Get all free fields in current board
	uint16_t freeFields = position->freeFields();
	int possibleMovesCount = CountBitboard(freeFields);

	// vector to store all generated positions
	std::vector<TTTBoard>* nextPosition = new std::vector<TTTBoard>(possibleMovesCount, *position);

	int result = 0;

	if (maximizing) // maximizing for circles
	{
		result = -256; // worst case

		// Generate possition after every possible move
		for (int i = 0; i < possibleMovesCount; ++i)
		{
			int index = PopBitboard(&freeFields);
			nextPosition->at(i).fields[index] = TTTPlayer::Circle;
			nextPosition->at(i).circles |= setMask[index];
		}

		// Recursion to all positions
		for (auto& pos : *nextPosition)
		{
			int evaluation = Minimax(&pos, depth - 1, alpha, beta, !maximizing);
			result = std::max(evaluation, result);

			alpha = std::max(alpha, evaluation);
			if (beta <= alpha)
				break;
		}
	}
	else // minimazing for crosses
	{
		result = 256; // worst case

		// Generate possition after every possible move
		for (int i = 0; i < possibleMovesCount; ++i)
		{
			int index = PopBitboard(&freeFields);
			nextPosition->at(i).fields[index] = TTTPlayer::Cross;
			nextPosition->at(i).crosses |= setMask[index];
		}

		// Recursion to all positions
		for (auto& pos : *nextPosition)
		{
			int evaluation = Minimax(&pos, depth - 1, alpha, beta, !maximizing);
			result = std::min(evaluation, result);

			beta = std::min(beta, evaluation);
			if (beta <= alpha)
				break;
		}
	}

	return result;
}
