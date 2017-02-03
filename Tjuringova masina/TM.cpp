#include "TM.h"

int read_int(istream& in)
{
	char c;
	string int_str = "";
	for (in >> c; (('0' <= c) && (c <= '9') || (c == '-') || (c == '+')); in >> c)
	{
		int_str += c;
	}
	return stoi(int_str);
}

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

istream& operator >> (istream& in, TM::f_pair& f_instance)
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

	f_instance = TM::f_pair(TM::f_in(q1, c1), TM::f_out(q2, c2, r));
	return in;
}

istream& operator >> (istream& in, TM& tm)
{
	in >> tm.b;
	in >> tm.q0 >> tm.q_ok >> tm.q_nok;

	int n;
	in >> n;

	for (int i = 0; i < n; i++)
	{
		getline(in, string());
		TM::f_pair* pf_instance = new TM::f_pair;
		in >> *pf_instance;
		tm += pf_instance;
	}
	return in;
}


void TM::f_list::cop(const f_list& f)
{
	for (Elem* temp = f.prvi; temp != nullptr; temp = temp->sl)
	{
		insert(temp->a);
	}
}

void TM::f_list::del()
{
	while (prvi != nullptr)
	{
		Elem * temp = prvi;
		prvi = prvi->sl;
		delete temp;
	}
	posl = nullptr;
}

TM::f_out TM::f_list::operator () (const f_in& in) const
{
	Elem* temp = prvi;
	while ((temp != nullptr) && (temp->a->in != in)) { temp = temp->sl; }

	if (temp != nullptr) { return temp->a->out; }
	throw char();
}


bool TM::solve(Traka& t) const
{
	string q = q0;

	try
	{
		while ((q != q_ok) && (q != q_nok))
		{
			f_out next = f(q, t.read());
			q = next.q;
			t.put(next.a);
			t += next.r;
		}
	}
	catch (char) { q = q_nok; }

	t.clean();
	return q == q_ok;
}