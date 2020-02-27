#include <Windows.h>
#include <iostream>
#include <string>
#include <fcntl.h>
#include <io.h>
#include <string>
#include "kayttoliittyma.h"
#include "siirto.h"
#include "asema.h"

using namespace std;

Kayttoliittyma* Kayttoliittyma::instance = 0;

string secret = "up-up-down-down-<->-<->-B-A";
wstring konami(secret.begin(), secret.end());

Kayttoliittyma* Kayttoliittyma::getInstance()
{
	if (instance == 0)
		instance = new Kayttoliittyma();
	return instance;
}

void Kayttoliittyma::piirraLauta()
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

	//Saa unicode shakkinappulat toimimaan printf kanssa:
	//SetConsoleOutputCP(65001);
	//printf(q);
	//char q[] = "King: \xE2\x99\x94.\n";

	//Saa unicode shakkinappulat toimimaan cout:n kanssa:
	_setmode(_fileno(stdout), _O_U16TEXT);

	/*
		Kaksinkertainen for silmukka joka käy asema-olion laudan läpi ja jos
		siinä on nappula olio, niin kysytään sen nimi
		ja tulostetaan se muussa tapauksessa tulostetaan 2 tyhjää välilyöntiä.
		Parillisuuteen perustuen värjätään jokatoisen "ruudun" taustaväri
	*/
	int color = 0;

	for (int j = 7; j >= 0; j--)
	{
		std::wcout << j + 1;


		for (int i = 0; i < 8; i++, color++)
		{
			if (color % 2 == 0) {
				SetConsoleTextAttribute(console, BACKGROUND_INTENSITY | BACKGROUND_RED |
					BACKGROUND_GREEN | BACKGROUND_BLUE);
			}
			else {
				SetConsoleTextAttribute(console, BACKGROUND_INTENSITY);
			}
			if (_asema->_lauta[i][j] != NULL) {
				std::wstring nimi = _asema->_lauta[i][j]->getUnicode();
				std::wcout << nimi;
			}
			else {
				std::wcout << " ";
			}
		}

		color++;

		std::wcout << "\n";
		SetConsoleTextAttribute(console, BACKGROUND_INTENSITY);
	}
	std::wcout << " ABCDEFGH";


}
Siirto Kayttoliittyma::annaVastustajanSiirto() {
	int lahtoX;
	int lahtoY;
	int loppuX;
	int loppuY;
	wcout << "Anna siirtosi. Esim: Lf1-c4\n";
	wcin >> siirtoString;

	while (true) {
		/* if (siirtoString == konami) {
			for (int i = 0; i < 8; i++)
			{
				for (int j = 0; j < 8; j++)
				{
					if (_asema->_lauta[i][j] != NULL) 
					{
						if(_asema->_lauta[i][j]->getVari == )
						_asema->_lauta[i][j] = NULL;
					}
					
				}
			}
		}
		*/


		if (siirtoString.length() < 4) {
			wcout << "\nAntamasi siirto on väärää muotoa\n";
			return Siirto(false, false, false);
		}


		if (siirtoString == L"0-0" || siirtoString == L"0-0-0")
		{
			if (siirtoString == L"0-0") {
				return Siirto(true, false, true);
				break;
			}
			if (siirtoString == L"0-0-0") {
				return Siirto(false, true, true);
				break;
			}
		}

		else if (siirtoString.length() == 6) {
			siirtoString.erase(0, 1);
		}

		try { lahtoX = siirtoString[0] - 'a'; }
		catch(...) { lahtoX = 100; }
		try { loppuX = siirtoString[3] - 'a'; }
		catch (...) { loppuX = 100; }
		try { lahtoY = siirtoString[1] - '1'; }
		catch(...){ lahtoY = 100; }
		try { loppuY = siirtoString[4] - '1'; }
		catch (...) { loppuY = 100; }

		if (lahtoX > 7 || lahtoX < 0 || lahtoY > 7 || lahtoY < 0 || loppuX > 7 || loppuX < 0 || loppuY > 7 || loppuY < 0) {
			wcout << "\nAntamasi siirto on väärää muotoa\n";
			return Siirto(false, false, false);
		}
		else {
			break;
		}
	}

	
	Ruutu lahtoRuutu(lahtoX, lahtoY);
	Ruutu loppuRuutu(loppuX, loppuY);
	Siirto siirto(lahtoRuutu, loppuRuutu);
	return siirto;
		




	
}
int Kayttoliittyma::kysyVastustajanVari()
{
	return 0;
}

;
