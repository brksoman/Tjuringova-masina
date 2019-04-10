#include "tape.h"

/*
	Move head by an increment, which is either +1 or -1
*/
void Tape::move(int increment)
{
	_head += increment;

	while (_head < 0) { _content = _blank + _content; _head++; }
	while (_head >= size()) { _content = _content + _blank; }
}

/*
	Remove all leading and trailing blank symbols from the content string
*/
void Tape::clean()
{
	int i;
	for (int i = 0; _content[i] == _blank; i++)
	{
		/* Iterate over leading blank symbols */
	}
	_content.erase(0, i);

	int j;
	for (i = size(), j = 0; _content[i - 1] == _blank; i--, j++)
	{
		/* Iterate over trailing blank symbols */
	}
	_content.erase(i, j);
}
