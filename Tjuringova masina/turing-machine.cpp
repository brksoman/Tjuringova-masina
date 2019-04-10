#include "turing-machine.h"

/*
	Read integer from input stream
*/
int read_int(istream& in)
{
	char c;
	string intStr = "";
	for (in >> c; (('0' <= c) && (c <= '9') || (c == '-') || (c == '+')); in >> c)
	{
		intStr += c;
	}
	return stoi(intStr);
}

/*
	Read state name from input stream
*/
string read_elem(istream& in)
{
	char c;
	string elem = "";
	for (in >> c; ((c != '(') && (c != ')') && (c != ',')); in >> c)
	{
		elem += c;
	}
	return elem;
}

/*
	Utility methods
*/
void Turing_machine::f_list::cop(const f_list& f)
{
	for (Elem* temp = f.head; temp != nullptr; temp = temp->next)
	{
		insert(temp->instance);
	}
}

void Turing_machine::f_list::del()
{
	while (head != nullptr)
	{
		Elem * temp = head;
		head = head->next;
		delete temp;
	}
	tail = nullptr;
}

/*
	Return function result
*/
Turing_machine::f_out Turing_machine::f_list::operator () (const f_in& in) const
{
	Elem* temp = head;
	while ((temp != nullptr) && (temp->instance->in != in)) { temp = temp->next; }

	if (temp != nullptr) { return temp->instance->out; }
	throw char();
}

/*
	Solve tape using defined algorithm
*/
bool Turing_machine::solve(Tape& t) const
{
	string q = q0;

	try
	{
		while ((q != q_ok) && (q != q_nok))
		{
			f_out next = f(q, t.read());
			q = next.q;
			t.write(next.a);
			t += next.r;
		}
	}
	catch (char) { q = q_nok; }

	t.clean();
	return q == q_ok;
}

/*
	Read one function instance
*/
istream& operator >> (istream& in, Turing_machine::f_pair& f_instance)
{
	char c, c1, c2;

	in >> c;			// '('
	string q1 = read_elem(in);		// q + ','
	in >> c1;			// c1
	in >> c;			// ')'

	in >> c; in >> c;	// "->"

	in >> c;			// '('
	string q2 = read_elem(in);		// q + ','
	in >> c2;			// c2
	in >> c;			// ','
	int r = read_int(in);		// r + ')'

	f_instance = Turing_machine::f_pair(Turing_machine::f_in(q1, c1), Turing_machine::f_out(q2, c2, r));
	return in;
}

/*
	Read the whole algorithm
*/
istream& operator >> (istream& in, Turing_machine& tm)
{
	in >> tm._blank;
	in >> tm.q0 >> tm.q_ok >> tm.q_nok;

	int n;
	in >> n;

	for (int i = 0; i < n; i++)
	{
		getline(in, string());
		Turing_machine::f_pair* pf_instance = new Turing_machine::f_pair;
		in >> *pf_instance;
		tm += pf_instance;
	}
	return in;
}