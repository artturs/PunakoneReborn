#include <iostream>
#include <Windows.h>
#include <io.h>
#include <fcntl.h>
#include <iostream>
#include <fstream>
#include <string>
#include "kayttoliittyma.h"
#include "Siirto.h"
#include "asema.h"
           

using namespace std;
void printAllAvailableMoves(list<Siirto> lista, Asema asema)
{
	char xCoordInCharAlku;
	char xCoordInCharLoppu;

	wcout << "\n\nMahdolliset siirrot:(" << lista.size() << "kpl)\n";

	for (auto v : lista)
	{
		if (v.onkoLyhytLinna()) { wcout << "\n lyhyt linna"; continue; }
		if (v.onkoPitkaLinna()) { wcout << "\n pitkä linna"; continue; }

		switch (v.getAlkuruutu().getSarake()) {
		case 0:
			xCoordInCharAlku = 'a';
			break;
		case 1:
			xCoordInCharAlku = 'b';
			break;
		case 2:
			xCoordInCharAlku = 'c';
			break;
		case 3:
			xCoordInCharAlku = 'd';
			break;
		case 4:
			xCoordInCharAlku = 'e';
			break;
		case 5:
			xCoordInCharAlku = 'f';
			break;
		case 6:
			xCoordInCharAlku = 'g';
			break;
		case 7:
			xCoordInCharAlku = 'h';
			break;
		default:
			xCoordInCharAlku = '-';
		}

		switch (v.getLoppuruutu().getSarake()) {
		case 0:
			xCoordInCharLoppu = 'a';
			break;
		case 1:
			xCoordInCharLoppu = 'b';
			break;
		case 2:
			xCoordInCharLoppu = 'c';
			break;
		case 3:
			xCoordInCharLoppu = 'd';
			break;
		case 4:
			xCoordInCharLoppu = 'e';
			break;
		case 5:
			xCoordInCharLoppu = 'f';
			break;
		case 6:
			xCoordInCharLoppu = 'g';
			break;
		case 7:
			xCoordInCharLoppu = 'h';
			break;
		default:
			xCoordInCharLoppu = '-';
		}

		std::wcout << "\n(" << xCoordInCharAlku << v.getAlkuruutu().getRivi() + 1 << "-" << xCoordInCharLoppu << v.getLoppuruutu().getRivi() + 1 << ")";
	}
	


}
int main()
{
	Asema asema;
	Kayttoliittyma::getInstance()->aseta_asema(&asema);
	
	

	int lopetus = 100;
	Peli peli(Kayttoliittyma::getInstance()->
		kysyVastustajanVari());
	std::list<Siirto> lista;
	system("cls");
	int koneenVari = peli.getKoneenVari();
	int vastustajanVari = 0;


	
	while (true) {
		
		lista.clear();
		Kayttoliittyma::getInstance()->piirraLauta();
		asema.annaLaillisetSiirrot(lista);
		printAllAvailableMoves(lista, asema);
		wcout << "\n";
		Siirto siirto;
		
		

		if (asema.getSiirtovuoro() != koneenVari) {
			siirto = Kayttoliittyma::getInstance()->annaVastustajanSiirto();

			while (siirto.onkoMahdollinen() == false)
			{
				siirto = Kayttoliittyma::getInstance()->annaVastustajanSiirto();
			}
		}
		else {
			double evaluaatio = asema.evaluoi();
			MinMaxPaluu paluu = asema.minimax(2);
			siirto = paluu._parasSiirto;
		}
		
		
		asema.paivitaAsema(&siirto);
		//wcout << "\Evaluaatio: " << asema.evaluoi() << "\n";
		

		if (asema.getSiirtovuoro() == koneenVari) { asema.setSiirtovuoro(vastustajanVari); }
		else{ asema.setSiirtovuoro(koneenVari); }
	}

	return 0;
}

