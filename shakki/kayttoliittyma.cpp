#include <Windows.h>
#include <iostream>
#include <string>
#include <fcntl.h>
#include <io.h>
#include <iostream>
#include "kayttoliittyma.h"

using namespace std;


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
		Kaksinkertainen for silmukka joka k‰y asema-olion laudan l‰pi ja jos 
		siin‰ on nappula olio, niin kysyt‰‰n sen nimi
		ja tulostetaan se muussa tapauksessa tulostetaan 2 tyhj‰‰ v‰lilyˆnti‰.
		Parillisuuteen perustuen v‰rj‰t‰‰n jokatoisen "ruudun" taustav‰ri
	*/
	int color = 0;
	
	for (int j = 0; j < 8; j++)
	{
			std::wcout << 8 - j;
			
		
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
