#ifndef _traka_h_
#define _traka_h
#include <iostream>
#include <string>
using namespace std;

class Traka
{
	string s;
	int glava;
	char b;

public:
	Traka(char bb = 'b', string ss = "") : b(bb), s(ss), glava(0) {}

	Traka& operator += (int r)
	{
		move(r);
		return *this;
	}
	Traka& operator = (const string& ss)
	{
		s = ss;
		reset();
		return *this;
	}
	char read() const { return s[glava]; }
	void put(char c) { s[glava] = c; }

	void clean();

	friend istream& operator >> (istream& in, Traka& t) { return in >> t.s; }
	friend ostream& operator << (ostream& out, const Traka& t) { return out << "[..." << t.s << "...]"; }


private:
	int size() const { return s.length(); }
	void reset() { glava = 0; }
	void move(int);
};


#endif