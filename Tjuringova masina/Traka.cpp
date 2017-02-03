#include "Traka.h"

void Traka::move(int r)
{
	glava += r;

	while (glava < 0)
	{
		s = b + s;
		glava++;
	}
	while (glava >= size())
	{
		s = s + b;
	}
}

void Traka::clean()
{
	int i;
	for (i = 0; s[i] == b; i++);
	s.erase(0, i);

	int j;
	for (i = size(), j = 0; s[i - 1] == b; i--, j++);
	s.erase(i, j);
}
