#ifndef _tm_h_
#define _tm_h_
#include "Traka.h"
#include <iostream>
#include <string>
using namespace std;

class TM
{
	// Clan domena funkcije algoritma
	struct f_in
	{
		string q;	// Stanje
		char a;		// Slovo

		f_in(const string& qq, char aa) : q(qq), a(aa) {}
		f_in() = default;

		friend bool operator == (const f_in& f1, const f_in& f2) { return (f1.q == f2.q) && (f1.a == f2.a); }
		friend bool operator != (const f_in& f1, const f_in& f2) { return !(f1 == f2); }
		virtual ~f_in() {}
	};
	// Clan koodomena funkcije algoritma
	struct f_out : public f_in
	{
		int r;		// Pomeraj

		f_out(const string& qq, char aa, int rr) : f_in(qq, aa), r(rr) {}
		f_out() = default;
	};
	// Instanca funkcije algoritma - uredjeni par (f_in, f_out) <=> f_in -> f_out
	struct f_pair
	{
		f_in in;
		f_out out;

		f_pair(const f_in& fin, const f_out& fout) : in(fin), out(fout) {}
		f_pair() = default;
	};
	// Funkcija algoritma - lista instanci
	class f_list
	{
		// Cvor liste
		struct Elem
		{
			f_pair* a;
			Elem* sl;

			Elem(f_pair* aa = nullptr, Elem* ssl = nullptr) : a(aa), sl(ssl) {}
			~Elem() { delete a; }
		};

		Elem* prvi, * posl;
		
	public:
		f_list() : prvi(nullptr), posl(nullptr) {}
		// Konstruktori kopiranja i premestanja (potencijalno nepotrebni)
		f_list(const f_list& f) { cop(f); }
		f_list(f_list&& f) { mov(f); }
		~f_list() { del(); }

		// Metode operacije dodeljivanja (potencijalno nepotrebne)
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

		// Operatori za trazenje odgovarajuce instance, u funkciji od clana domena funkcije
		f_out operator () (const f_in&) const;
		f_out operator () (const string& qq, char cc) const { return (*this)(f_in(qq, cc)); }

		// Operatori dodavanja nove instance, preko upucivaca ili pokazivaca
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
		// Pomocne metode
		void mov(f_list& f)
		{
			prvi = f.prvi; f.prvi = nullptr;
			posl = f.posl; f.posl = nullptr;
		}
		void cop(const f_list&);
		void del();
		void insert(f_pair* pf_instance)
		{
			Elem * novi = new Elem(pf_instance);
			if (prvi == nullptr) { prvi = novi; }
			else { posl->sl = novi; }
			posl = novi;
		}
	};


public:
	TM(char bb = 'b', string qq0 = "q0", string qq_ok = "q+", string qq_nok = "q-") : b(bb), q0(qq0), q_ok(qq_ok), q_nok(qq_nok) {}

	const char& neutral() const { return b; }

	// Dodavanje instance u listu instanci
	TM& operator += (const f_pair& f_instance)
	{
		f += f_instance;
		return *this;
	}
	TM& operator += (f_pair* pf_instance)
	{
		f += pf_instance;
		return *this;
	}

	// Operator za "resavanje" trake
	bool operator () (Traka& t) const { return solve(t); }

	// Operatori citanja - nove instance, i celog algoritma
	friend istream& operator >> (istream&, f_pair&);
	friend istream& operator >> (istream&, TM&);


private:
	char b;
	string q0;
	string q_ok;
	string q_nok;
	f_list f;

	bool solve(Traka&) const;
};





#endif