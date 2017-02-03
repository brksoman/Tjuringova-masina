#include "TM.h"
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

int main()
{
	string ime_fajla_programa;
	do
	{
		cout << "Unesite ime fajla programa (q za zavrsetak programa): ";
		getline(cin, ime_fajla_programa);

		if (ime_fajla_programa != "q")
		{
			// Ucitavanje algoritma iz datoteke
			ifstream program;
			program.open(ime_fajla_programa + ".txt");

			TM tm;
			program >> tm;
			program.close();

			string traka_string;
			do
			{
				cout << "Unesite nepodrazumevani deo trake (q za prelazak na sledecu funkciju):" << "\n\t";
				getline(cin, traka_string);
				if (traka_string != "q")
				{
					Traka t(tm.neutral(), traka_string);

					if (tm(t) == true) { cout << "Zadatak je uspesno izvrsen."; }
					else { cout << "Zadatak nije uspesno izvrsen."; }

					cout << endl << t << endl;
				}
			} while (traka_string != "q");
		}
	} while (ime_fajla_programa != "q");

	cout << endl << "Kraj izvrsavanja programa." << endl;
	return EXIT_SUCCESS;
}