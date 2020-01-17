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
	int debug = 0;
	for (int j = 0; j < 8; j++)
	{
		for (int i = 0; i < 8; i++)
		{
			if (_asema->_lauta[i][j] != NULL) {
				std::wstring nimi = _asema->_lauta[i][j]->getUnicode();
				std::wcout << nimi;
			}
			else {
				std::wcout << "  ";
			}
		}
		std::wcout << "\n";
	
	}
	std:wcout << debug;
	
}
