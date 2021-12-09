#include "Transcriber.h"

#include <string>
#include <sstream>
#include <vector>

std::string ignore[] =
{
	"IN", "ON", "AT", "THE", "PLACE"
};

int SplitString(const char* input, std::vector<std::string>& output)
{
	int res = 0;
	std::stringstream strIn(input);

	std::string seg;
	while (std::getline(strIn, seg, ' ') && res < 3)
	{
		if (seg[0] != 'I' && seg[0] != 'O' && seg[0] != 'A' && seg[0] != 'P')
		{
			if (seg[0] == 'T' && seg == "TOP")
			{
				output.push_back(seg);
				res++;
			}
			else
			{
				output.push_back(seg);
				res++;
			}
		}
	}

	return res;
}

TTTMove Transcriber::Transcribe(const char* input)
{
	TTTMove result = { TTTPlayer::Invalid, TTTSquare::NoSquare };

	/*if (input == "(null)")
		return result;*/

	std::vector<std::string> command;
	command.reserve(3);
	int cmdCount = SplitString(input, command);

	if (command[0] == "CIRCLE")
	{
		result.player = TTTPlayer::Circle;
	}
	else if (command[0] == "CROSS")
	{
		result.player = TTTPlayer::Cross;
	}

	if (cmdCount == 2)
	{
		if (command[1] == "TOP")
			result.place = TTTSquare::Top;
		else if (command[1] == "LEFT")
			result.place = TTTSquare::Left;
		else if (command[1] == "MIDDLE")
			result.place = TTTSquare::Centre;
		else if (command[1] == "CENTER")
			result.place = TTTSquare::Centre;
		else if (command[1] == "RIGHT")
			result.place = TTTSquare::Right;
		else if (command[1] == "BOTTOM")
			result.place = TTTSquare::Bottom;
	}
	else if (cmdCount == 3)
	{
		if (command[1] == "TOP")
		{
			if (command[2] == "LEFT")
				result.place = TTTSquare::TopLeft;
			else if (command[2] == "RIGHT")
				result.place = TTTSquare::TopRight;
			else
				result.place = TTTSquare::Top;
		}
		else if (command[1] == "BOTTOM")
		{
			if (command[2] == "LEFT")
				result.place = TTTSquare::BottomLeft;
			else if (command[2] == "RIGHT")
				result.place = TTTSquare::BottomRight;
			else
				result.place = TTTSquare::Bottom;
		}
	}

	return result;
}
