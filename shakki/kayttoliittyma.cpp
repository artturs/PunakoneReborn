#include <Windows.h>
#include <iostream>
#include <string>
#include <fcntl.h>
#include <io.h>
#include <string>
#include "kayttoliittyma.h"
#include "siirto.h"

using namespace std;

Kayttoliittyma* Kayttoliittyma::instance = 0;


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
			std::wcout << j+1;
			
		
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
	if (siirtoString == L"0-0" || siirtoString == L"0-0-0")
	{
		//tee jotain
	}
	if (siirtoString.length() == 6) {
		siirtoString.erase(0, 1);
	}
	else {
		lahtoX = siirtoString[0] - 'a';
		loppuX = siirtoString[3] - 'a';
		lahtoY = siirtoString[1] - '1';
		loppuY = siirtoString[4] - '1';
	}
	Ruutu lahtoRuutu(lahtoX, lahtoY);
	Ruutu loppuRuutu(loppuX, loppuY);
	Siirto siirto(lahtoRuutu, loppuRuutu);

}
int Kayttoliittyma::kysyVastustajanVari()
{
	return 0;
}
;
