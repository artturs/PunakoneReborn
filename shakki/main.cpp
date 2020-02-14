#include <iostream>
#include <Windows.h>
#include <io.h>
#include <fcntl.h>
#include <iostream>
#include <string>
#include "kayttoliittyma.h"
#include "Siirto.h"
#include "asema.h"

using namespace std;

int main()
{
	Asema asema;
	Kayttoliittyma::getInstance()->aseta_asema(&asema);
	wcout << "HeippariShakki\n";
	wcout << "Tervetuloa pelaamaan!\n";
	int lopetus = 100;
	Peli peli(Kayttoliittyma::getInstance()->
		kysyVastustajanVari());
	std::list<Siirto> lista;
	system("cls");
	int koneenVari = peli.getKoneenVari();


	lista.clear();
	while (true) {
		
		
		Kayttoliittyma::getInstance()->piirraLauta();
		asema.annaLaillisetSiirrot(lista);
		wcout << "\n";
		Siirto siirto;
		
		siirto = Kayttoliittyma::getInstance()->annaVastustajanSiirto();
		asema.paivitaAsema(&siirto);
		

	}

	return 0;
}
