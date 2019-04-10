#ifndef _tape_h_
#define _tape_h_
#include <iostream>
#include <string>
using namespace std;

class Tape
{
	string _content;
	int _head;

	/* The character which represents the blank symbol */
	char _blank;

public:
	Tape(char blank = 'b', string content = "") : _blank(blank), _content(content), _head(0) {}

	Tape& operator += (int increment)
	{
		move(increment);
		return *this;
	}

	Tape& operator = (const string& newContent)
	{
		_content = newContent;
		reset();
		return *this;
	}
	
	char read() const { return _content[_head]; }

	void write(char c) { _content[_head] = c; }

	void clean();

	friend istream& operator >> (istream& in, Tape& t) { return in >> t._content; }
	friend ostream& operator << (ostream& out, const Tape& t) { return out << "[..." << t._content << "...]"; }


private:
	int size() const { return _content.length(); }

	void reset() { _head = 0; }

	void move(int increment);
};


#endif