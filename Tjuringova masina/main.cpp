#include "turing-machine.h"
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

/*
	Choose language
*/
#define SRBSKI
//#define ENGRISH

int main()
{
	// Phase 1
	string fileName;
	do
	{
#ifdef SRBSKI
		cout << "Unesite ime fajla programa (q za zavrsetak programa): ";
#elif ENGRISH
		cout << "Enter file name (q - quit program): ";
#endif
		getline(cin, fileName);

		if (fileName != "q")
		{
			/* Read algorithm from file */
			ifstream program;
			program.open(fileName + ".txt");

			Turing_machine tm;
			program >> tm;
			program.close();

			// Phase 2
			string tapeString;
			do
			{
#ifdef SRBSKI
				cout << "Unesite nepodrazumevani deo trake (q za prelazak na sledecu funkciju):" << "\n\t";
#elif ENGRISH
				cout << "Enter the main part of the tape (q - enter new algorithm):" << "\n\t";
#endif
				getline(cin, tapeString);
				if (tapeString != "q")
				{
					Tape t(tm.neutral(), tapeString);

					if (tm(t) == true)
					{
#ifdef SRBSKI
						cout << "Zadatak je uspesno izvrsen.";
#elif ENGRISH
						cout << "Success.";
#endif
					}
					else
					{
#ifdef SRBSKI
						cout << "Zadatak nije uspesno izvrsen.";
#elif ENGRISH
						cout << "Fail.";
#endif
					}

					cout << endl << t << endl;
				}
			} while (tapeString != "q");
		}
	} while (fileName != "q");

#ifdef SRBSKI
	cout << endl << "Kraj izvrsavanja programa." << endl;
#elif ENGRISH
	cout << endl << "Program end." << endl;
#endif
	return EXIT_SUCCESS;
}