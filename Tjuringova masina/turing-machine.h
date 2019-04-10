#ifndef _turing_machine_h_
#define _turing_machine_h_
#include "tape.h"
#include <iostream>
#include <string>
using namespace std;

class Turing_machine
{
	/* Member of the domain of the algorithm function */
	struct f_in
	{
		string q;	// State
		char a;		// Character

		f_in(const string& qq, char aa) : q(qq), a(aa) {}
		f_in() = default;

		friend bool operator == (const f_in& f1, const f_in& f2) { return (f1.q == f2.q) && (f1.a == f2.a); }
		friend bool operator != (const f_in& f1, const f_in& f2) { return !(f1 == f2); }
		virtual ~f_in() {}
	};

	/* Member of the codomain of the algorithm function */
	struct f_out : public f_in
	{
		int r;		// Increment

		f_out(const string& qq, char aa, int rr) : f_in(qq, aa), r(rr) {}
		f_out() = default;
	};

	/* Function instance - ordered pair (f_in, f_out) <=> f_in -> f_out */
	struct f_pair
	{
		f_in in;
		f_out out;

		f_pair(const f_in& fin, const f_out& fout) : in(fin), out(fout) {}
		f_pair() = default;
	};

	/* Algorithm function - list of function instances */
	class f_list
	{
		/* List node */
		struct Elem
		{
			f_pair* instance;
			Elem* next;

			Elem(f_pair* i = nullptr, Elem* n = nullptr) : instance(i), next(n) {}
			~Elem() { delete instance; }
		};

		Elem* head, * tail;
		
	public:
		f_list() : head(nullptr), tail(nullptr) {}
		f_list(const f_list& f) { cop(f); }
		f_list(f_list&& f) { mov(f); }
		~f_list() { del(); }

		f_list& operator = (const f_list& f)
		{
			if (this != &f) { del(); cop(f); }
			return *this;
		}

		f_list& operator = (f_list&& f)
		{
			if (this != &f) { del(); mov(f); }
			return *this;
		}

		/* Function calling methods */
		f_out operator () (const f_in&) const;
		f_out operator () (const string& qq, char cc) const { return (*this)(f_in(qq, cc)); }

		/* Adding new function instances into the algorithm */
		f_list& operator += (const f_pair& f_instance)
		{
			insert(new f_pair(f_instance));
			return *this;
		}
		f_list& operator += (f_pair* pf_instance)
		{
			insert(pf_instance);
			return *this;
		}

	private:
		/* Utils */
		void mov(f_list& f)
		{
			head = f.head; f.head = nullptr;
			tail = f.tail; f.tail = nullptr;
		}
		void cop(const f_list&);
		void del();
		void insert(f_pair* pf_instance)
		{
			Elem * novi = new Elem(pf_instance);
			if (head == nullptr) { head = novi; }
			else { tail->next = novi; }
			tail = novi;
		}
	};


public:
	Turing_machine(char blank = 'b', string qq0 = "q0", string qq_ok = "q+", string qq_nok = "q-")
		: _blank(blank), q0(qq0), q_ok(qq_ok), q_nok(qq_nok) {}

	const char& neutral() const { return _blank; }

	/* Adding new function instances into the algorithm */
	Turing_machine& operator += (const f_pair& f_instance)
	{
		f += f_instance;
		return *this;
	}

	Turing_machine& operator += (f_pair* pf_instance)
	{
		f += pf_instance;
		return *this;
	}

	// Operator za "resavanje" trake
	bool operator () (Tape& t) const { return solve(t); }

	// Operatori citanja - nove instance, i celog algoritma
	friend istream& operator >> (istream&, f_pair&);
	friend istream& operator >> (istream&, Turing_machine&);


private:
	char _blank;
	string q0;
	string q_ok;
	string q_nok;
	f_list f;

	bool solve(Tape&) const;
};





#endif