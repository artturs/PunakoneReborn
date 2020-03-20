#include <iostream>
#include <Windows.h>
#include <io.h>
#include <concurrent_vector.h>
#include <fcntl.h>
#include <iostream>
#include <string>
#include <Vector>
#include <ppl.h>
#include <PPL.h>
#include "kayttoliittyma.h"
#include "siirto.h"
#include "asema.h"
#include "timer.h"
#pragma optimize("g", on)

using namespace std;
using namespace concurrency;

int main()
{
	

	int lopetus = 100;
	Asema asema;
	Kayttoliittyma::getInstance()->aseta_asema(&asema);
	MinMaxPaluu a;
	MinMaxPaluu b;
	a._evaluointiArvo = -INFINITY;
	b._evaluointiArvo = +INFINITY;
	Peli peli(Kayttoliittyma::getInstance()->
		kysyVastustajanVari());

	concurrent_vector<Siirto> lista;
	
	system("cls");
	int koneenVari = peli.getKoneenVari();

	while (lopetus != 0) {

		Timer* timer = new Timer();

		lista.clear();
		Kayttoliittyma::getInstance()->piirraLauta();
		wcout << "\n";
		// Tarkasta onko peli loppu?
		asema.annaLaillisetSiirrot(lista);
		if (lista.size() == 0) {
			lopetus = 0;
			std::wcout << "Peli loppui";
			continue;
		}
		Siirto siirto;
		if (asema.getSiirtovuoro() == koneenVari) {
			MinMaxPaluu paluu;
			if (koneenVari == 0) {
				paluu = asema.MaxAB(3, a, b);
			}
			else {
				paluu = asema.MinAB(3, a, b);
			}
			siirto = paluu._parasSiirto;
		}
		else {
			siirto = Kayttoliittyma::getInstance()->
				annaVastustajanSiirto();
		}
		asema.paivitaAsema(&siirto);

		timer->Stop();
	}


	return 0;
}
