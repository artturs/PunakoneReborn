#include <list>
#include <string>
#include "asema.h"
#include "nappula.h"
using namespace std;
#pragma optimize("g", on)

Nappula::Nappula(wstring unicode, int vari, int koodi)
{
	_unicode = unicode;
	_vari = vari;
	_koodi = koodi;
}


void Torni::annaSiirrot(concurrency::concurrent_vector<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	int lahtoruutuY = ruutu->getRivi();
	int lahtoruutuX = ruutu->getSarake();

	int lahtoruudunNappulanVari;
	int tuloruudunNappulanVari;

	lahtoruudunNappulanVari = asema->_lauta[lahtoruutuX][lahtoruutuY]->getVari();
	// vaakarivi ruudusta eteenpäin
	siirtoLoop(lista, ruutu, asema, lahtoruutuX, lahtoruutuY, 1, 0, lahtoruudunNappulanVari);

	// vaakarivi ruudusta taaksepäin
	siirtoLoop(lista, ruutu, asema, lahtoruutuX, lahtoruutuY, -1, 0, lahtoruudunNappulanVari);

	// pystyrivi ruudusta eteenpäin
	siirtoLoop(lista, ruutu, asema, lahtoruutuX, lahtoruutuY, 0, 1, lahtoruudunNappulanVari);

	// pystyrivi ruudusta taaksepäin
	siirtoLoop(lista, ruutu, asema, lahtoruutuX, lahtoruutuY, 0, -1, lahtoruudunNappulanVari);
	
}


void Ratsu::annaSiirrot(concurrency::concurrent_vector<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	int lahtoruutuY = ruutu->getRivi();
	int lahtoruutuX = ruutu->getSarake();

	int lahtoruudunNappulanVari;
	int tuloruudunNappulanVari;

	lahtoruudunNappulanVari = asema->_lauta[lahtoruutuX][lahtoruutuY]->getVari();

	// Pitää huomioida että kokeiltavat ruudut ovat vielä laudalla
	if (lahtoruutuX + 1 < 8 && lahtoruutuY + 2 < 8) {
		if (asema->_lauta[lahtoruutuX + 1][lahtoruutuY + 2] == NULL) {
			lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX + 1, lahtoruutuY + 2)));
		}
		else if (asema->_lauta[lahtoruutuX + 1][lahtoruutuY + 2] != NULL) {
			tuloruudunNappulanVari = asema->_lauta[lahtoruutuX + 1][lahtoruutuY + 2]->getVari();
			// jos oman värinen niin lisätään törmayslistaan
			if (lahtoruudunNappulanVari == tuloruudunNappulanVari) {
			}
			// jos vastujan nappula niin lisätään listaan
			if (lahtoruudunNappulanVari != tuloruudunNappulanVari) {
				lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX + 1, lahtoruutuY + 2)));
			}
		}
	}
	if (lahtoruutuX + 1 < 8 && lahtoruutuY - 2 >= 0) {
		if (asema->_lauta[lahtoruutuX + 1][lahtoruutuY - 2] == NULL) {
			lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX + 1, lahtoruutuY - 2)));
		}
		else if (asema->_lauta[lahtoruutuX + 1][lahtoruutuY - 2] != NULL) {
			tuloruudunNappulanVari = asema->_lauta[lahtoruutuX + 1][lahtoruutuY - 2]->getVari();
			// jos oman värinen niin lisätään törmayslistaan
			if (lahtoruudunNappulanVari == tuloruudunNappulanVari) {
			}
			// jos vastujan nappula niin lisätään listaan
			if (lahtoruudunNappulanVari != tuloruudunNappulanVari) {
				lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX + 1, lahtoruutuY - 2)));
			}
		}
	}
	if (lahtoruutuX - 1 >= 0 && lahtoruutuY + 2 < 8) {
		if (asema->_lauta[lahtoruutuX - 1][lahtoruutuY + 2] == NULL) {
			lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX - 1, lahtoruutuY + 2)));
		}
		else if (asema->_lauta[lahtoruutuX - 1][lahtoruutuY + 2] != NULL) {
			tuloruudunNappulanVari = asema->_lauta[lahtoruutuX - 1][lahtoruutuY + 2]->getVari();
			// jos oman värinen niin lisätään törmayslistaan
			if (lahtoruudunNappulanVari == tuloruudunNappulanVari) {
			}
			// jos vastujan nappula niin lisätään listaan
			if (lahtoruudunNappulanVari != tuloruudunNappulanVari) {
				lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX - 1, lahtoruutuY + 2)));
			}
		}
	}
	if (lahtoruutuX - 1 >= 0 && lahtoruutuY - 2 >= 0) {
		if (asema->_lauta[lahtoruutuX - 1][lahtoruutuY - 2] == NULL) {
			lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX - 1, lahtoruutuY - 2)));
		}
		else if (asema->_lauta[lahtoruutuX - 1][lahtoruutuY - 2] != NULL) {
			tuloruudunNappulanVari = asema->_lauta[lahtoruutuX - 1][lahtoruutuY - 2]->getVari();
			// jos oman värinen niin lisätään törmayslistaan
			if (lahtoruudunNappulanVari == tuloruudunNappulanVari) {
			}
			// jos vastujan nappula niin lisätään listaan
			if (lahtoruudunNappulanVari != tuloruudunNappulanVari) {
				lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX - 1, lahtoruutuY - 2)));
			}
		}
	}
	if (lahtoruutuX + 2 < 8 && lahtoruutuY + 1 < 8) {
		if (asema->_lauta[lahtoruutuX + 2][lahtoruutuY + 1] == NULL) {
			lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX + 2, lahtoruutuY + 1)));
		}
		else if (asema->_lauta[lahtoruutuX + 2][lahtoruutuY + 1] != NULL) {
			tuloruudunNappulanVari = asema->_lauta[lahtoruutuX + 2][lahtoruutuY + 1]->getVari();
			// jos oman värinen niin lisätään törmayslistaan
			if (lahtoruudunNappulanVari == tuloruudunNappulanVari) {
			}
			// jos vastujan nappula niin lisätään listaan
			if (lahtoruudunNappulanVari != tuloruudunNappulanVari) {
				lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX + 2, lahtoruutuY + 1)));
			}
		}
	}
	if (lahtoruutuX + 2 < 8 && lahtoruutuY - 1 >= 0) {
		if (asema->_lauta[lahtoruutuX + 2][lahtoruutuY - 1] == NULL) {
			lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX + 2, lahtoruutuY - 1)));
		}
		else if (asema->_lauta[lahtoruutuX + 2][lahtoruutuY - 1] != NULL) {
			tuloruudunNappulanVari = asema->_lauta[lahtoruutuX + 2][lahtoruutuY - 1]->getVari();
			// jos oman värinen niin lisätään törmayslistaan
			if (lahtoruudunNappulanVari == tuloruudunNappulanVari) {
			}
			// jos vastujan nappula niin lisätään listaan
			if (lahtoruudunNappulanVari != tuloruudunNappulanVari) {
				lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX + 2, lahtoruutuY - 1)));
			}
		}
	}
	if (lahtoruutuX - 2 >= 0 && lahtoruutuY + 1 < 8) {
		if (asema->_lauta[lahtoruutuX - 2][lahtoruutuY + 1] == NULL) {
			lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX - 2, lahtoruutuY + 1)));
		}
		else if (asema->_lauta[lahtoruutuX - 2][lahtoruutuY + 1] != NULL) {
			tuloruudunNappulanVari = asema->_lauta[lahtoruutuX - 2][lahtoruutuY + 1]->getVari();
			// jos oman värinen niin lisätään törmayslistaan
			if (lahtoruudunNappulanVari == tuloruudunNappulanVari) {
			}
			// jos vastujan nappula niin lisätään listaan
			if (lahtoruudunNappulanVari != tuloruudunNappulanVari) {
				lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX - 2, lahtoruutuY + 1)));
			}
		}
	}
	if (lahtoruutuX - 2 >= 0 && lahtoruutuY - 1 >= 0) {
		if (asema->_lauta[lahtoruutuX - 2][lahtoruutuY - 1] == NULL) {
			lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX - 2, lahtoruutuY - 1)));
		}
		else if (asema->_lauta[lahtoruutuX - 2][lahtoruutuY - 1] != NULL) {
			tuloruudunNappulanVari = asema->_lauta[lahtoruutuX - 2][lahtoruutuY - 1]->getVari();
			// jos oman värinen niin lisätään törmayslistaan
			if (lahtoruudunNappulanVari == tuloruudunNappulanVari) {
			}
			// jos vastujan nappula niin lisätään listaan
			if (lahtoruudunNappulanVari != tuloruudunNappulanVari) {
				lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX - 2, lahtoruutuY - 1)));
			}
		}
	}
	/*for (auto s : lista)
	{
	std::wcout << L"Ratsu";
	std::wcout << s.getAlkuruutu().getSarake();
	std::wcout << s.getAlkuruutu().getRivi() << "-";

	std::wcout << s.getLoppuruutu().getSarake();
	std::wcout << s.getLoppuruutu().getRivi() << "\n";
	}*/
}


void Lahetti::annaSiirrot(concurrency::concurrent_vector<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	int lahtoruutuY = ruutu->getRivi();
	int lahtoruutuX = ruutu->getSarake();

	int lahtoruudunNappulanVari;
	int tuloruudunNappulanVari;

	int j;

	lahtoruudunNappulanVari = asema->_lauta[lahtoruutuX][lahtoruutuY]->getVari();

	// viistorivi ruudusta oikealle ylös
	siirtoLoop(lista, ruutu, asema, lahtoruutuX, lahtoruutuY, 1, 1, lahtoruudunNappulanVari);

	// viistorivi ruudusta oikealle alas
	siirtoLoop(lista, ruutu, asema, lahtoruutuX, lahtoruutuY, 1, -1, lahtoruudunNappulanVari);

	// viistorivi ruudusta vasemmalle ylös
	siirtoLoop(lista, ruutu, asema, lahtoruutuX, lahtoruutuY, -1, 1, lahtoruudunNappulanVari);

	// viistorivi ruudusta vasemmalle alas
	siirtoLoop(lista, ruutu, asema, lahtoruutuX, lahtoruutuY, -1, -1, lahtoruudunNappulanVari);
	
}


void Daami::annaSiirrot(concurrency::concurrent_vector<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	this->Lahetti::annaSiirrot(lista, ruutu, asema, vari);
	this->Torni::annaSiirrot(lista, ruutu, asema, vari);
	/*for (auto s : lista)
	{
	std::wcout << L"Daami";
	std::wcout << s.getAlkuruutu().getSarake();
	std::wcout << s.getAlkuruutu().getRivi() << "-";

	std::wcout << s.getLoppuruutu().getSarake();
	std::wcout << s.getLoppuruutu().getRivi() << "\n";
	}*/
}


void Kuningas::annaSiirrot(concurrency::concurrent_vector<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	/*perusidea on että kaikki viereiset ruudut ovat sallittuja. kuten tornilla ja lähetillä,
	oman nappulan päälle ei voi mennä ja vastustajan nappulan voi syödä.

	Kaikki muu kuninkaaseen liittyvä tarkistus tehdään eri paikassa*/


	int lahtoruutuY = ruutu->getRivi();
	int lahtoruutuX = ruutu->getSarake();

	int lahtoruudunNappulanVari;
	int tuloruudunNappulanVari;

	lahtoruudunNappulanVari = asema->_lauta[lahtoruutuX][lahtoruutuY]->getVari();


	// Käydään perussiirtojen tyhjät ruudut läpi 
	// Pitää tarkistaa että ehdokas ruutu vielä laudalla
	if (lahtoruutuX + 1 < 8) {
		if (asema->_lauta[lahtoruutuX + 1][lahtoruutuY] == NULL) {

			lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX + 1, lahtoruutuY)));


		}
		else if (asema->_lauta[lahtoruutuX + 1][lahtoruutuY] != NULL) {
			tuloruudunNappulanVari = asema->_lauta[lahtoruutuX + 1][lahtoruutuY]->getVari();
			if (lahtoruudunNappulanVari != tuloruudunNappulanVari) {
				lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX + 1, lahtoruutuY)));
			}


		}
	}

	if (lahtoruutuX + 1 < 8 && lahtoruutuY + 1 < 8) {
		if (asema->_lauta[lahtoruutuX + 1][lahtoruutuY + 1] == NULL) {

			lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX + 1, lahtoruutuY + 1)));

		}
		else if (asema->_lauta[lahtoruutuX + 1][lahtoruutuY + 1] != NULL) {
			tuloruudunNappulanVari = asema->_lauta[lahtoruutuX + 1][lahtoruutuY + 1]->getVari();
			if (lahtoruudunNappulanVari != tuloruudunNappulanVari) {

				lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX + 1, lahtoruutuY + 1)));

			}
		}
	}

	if (lahtoruutuX + 1 < 8 && lahtoruutuY - 1 >= 0) {
		if (asema->_lauta[lahtoruutuX + 1][lahtoruutuY - 1] == NULL) {

			lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX + 1, lahtoruutuY - 1)));

		}
		else if (asema->_lauta[lahtoruutuX + 1][lahtoruutuY - 1] != NULL) {
			tuloruudunNappulanVari = asema->_lauta[lahtoruutuX + 1][lahtoruutuY - 1]->getVari();
			if (lahtoruudunNappulanVari != tuloruudunNappulanVari) {

				lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX + 1, lahtoruutuY - 1)));

			}
		}
	}

	if (lahtoruutuX - 1 >= 0) {
		if (asema->_lauta[lahtoruutuX - 1][lahtoruutuY] == NULL) {

			lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX - 1, lahtoruutuY)));

		}
		else if (asema->_lauta[lahtoruutuX - 1][lahtoruutuY] != NULL) {
			tuloruudunNappulanVari = asema->_lauta[lahtoruutuX - 1][lahtoruutuY]->getVari();
			if (lahtoruudunNappulanVari != tuloruudunNappulanVari) {

				lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX - 1, lahtoruutuY)));

			}
		}
	}

	if (lahtoruutuX - 1 >= 0 && lahtoruutuY + 1 < 8) {
		if (asema->_lauta[lahtoruutuX - 1][lahtoruutuY + 1] == NULL) {

			lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX - 1, lahtoruutuY + 1)));

		}
		else if (asema->_lauta[lahtoruutuX - 1][lahtoruutuY + 1] != NULL) {
			tuloruudunNappulanVari = asema->_lauta[lahtoruutuX - 1][lahtoruutuY + 1]->getVari();
			if (lahtoruudunNappulanVari != tuloruudunNappulanVari) {

				lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX - 1, lahtoruutuY + 1)));

			}
		}
	}

	if (lahtoruutuX - 1 >= 0 && lahtoruutuY - 1 >= 0) {
		if (asema->_lauta[lahtoruutuX - 1][lahtoruutuY - 1] == NULL) {

			lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX - 1, lahtoruutuY - 1)));

		}
		else if (asema->_lauta[lahtoruutuX - 1][lahtoruutuY - 1] != NULL) {
			tuloruudunNappulanVari = asema->_lauta[lahtoruutuX - 1][lahtoruutuY - 1]->getVari();
			if (lahtoruudunNappulanVari != tuloruudunNappulanVari) {

				lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX - 1, lahtoruutuY - 1)));

			}
		}
	}

	if (lahtoruutuY + 1 < 8) {
		if (asema->_lauta[lahtoruutuX][lahtoruutuY + 1] == NULL) {

			lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX, lahtoruutuY + 1)));

		}
		else if (asema->_lauta[lahtoruutuX][lahtoruutuY + 1] != NULL) {
			tuloruudunNappulanVari = asema->_lauta[lahtoruutuX][lahtoruutuY + 1]->getVari();
			if (lahtoruudunNappulanVari != tuloruudunNappulanVari) {

				lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX, lahtoruutuY + 1)));

			}
		}
	}

	if (lahtoruutuY - 1 >= 0) {
		if (asema->_lauta[lahtoruutuX][lahtoruutuY - 1] == NULL) {

			lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX, lahtoruutuY - 1)));

		}
		else if (asema->_lauta[lahtoruutuX][lahtoruutuY - 1] != NULL) {
			tuloruudunNappulanVari = asema->_lauta[lahtoruutuX][lahtoruutuY - 1]->getVari();
			if (lahtoruudunNappulanVari != tuloruudunNappulanVari) {

				lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX, lahtoruutuY - 1)));

			}
		}
	}
}


void Sotilas::annaSiirrot(concurrency::concurrent_vector<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	int lahtoruutuY = ruutu->getRivi();
	int lahtoruutuX = ruutu->getSarake();
	int lahtoruudunNappulanVari;
	int tuloruudunNappulanVari;
	lahtoruudunNappulanVari = asema->_lauta[lahtoruutuX][lahtoruutuY]->getVari();

	// jos sotilas rivillä 2 ja sotilas valkea tai sotilas rivillä 7 ja sotilas musta sillä on kaksois askel mahdollisuus
	// muilla riveillä sotilaalla yksöis aske
	// sotilas voi myös syödä etuviistoon ruudustaan
	// sotilas voi korottua jos se saavuttaa rivin 8 valkeilla ja vastaavasti rivin 1 mustilla

	// valkea rivillä 2
	if (lahtoruutuY == 1 && lahtoruudunNappulanVari == 0) {
		for (int i = lahtoruutuY + 1; i < lahtoruutuY + 3; i++) {
			// Jos tyhjä ruutu niin lisätään listaan
			if (asema->_lauta[lahtoruutuX][i] == NULL) {
				lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX, i)));
			}
			else
				break;
		}
	}

	// musta rivillä 7
	if (lahtoruutuY == 6 && lahtoruudunNappulanVari == 1) {
		for (int i = lahtoruutuY - 1; i > lahtoruutuY - 3; i--) {
			// Jos tyhjä ruutu niin lisätään listaan
			if (asema->_lauta[lahtoruutuX][i] == NULL) {
				lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX, i)));
			}
			else
				break;
		}
	}
	// perusruudut valkeille 
	if ((lahtoruutuY == 2 || lahtoruutuY == 3 || lahtoruutuY == 4 || lahtoruutuY == 5 || lahtoruutuY == 6) && lahtoruudunNappulanVari == 0) {
		//siirtymät eteenpäin
		if (asema->_lauta[lahtoruutuX][lahtoruutuY + 1] == NULL) {
			if (lahtoruutuY < 6)
				lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX, lahtoruutuY + 1)));
			else
				lisaaSotilaanKorotukset(&Siirto(*ruutu, Ruutu(lahtoruutuX, lahtoruutuY + 1)), lista, asema);
		}
		//syönnit viistoon
		if (lahtoruutuX + 1 < 8) { // tarkastetaan että pysytään laudalla
			if (asema->_lauta[lahtoruutuX + 1][lahtoruutuY + 1] != NULL) {
				// Tarkistetaan että jos lähtöruudussa olevan nappulan väri on sama kuin tarkastelun alaisessa ruudussa, niin silloin on oma nappula
				tuloruudunNappulanVari = asema->_lauta[lahtoruutuX + 1][lahtoruutuY + 1]->getVari();
				if (lahtoruudunNappulanVari == tuloruudunNappulanVari) {
				}
				// jos vastujan nappula niin poistutaan for silmukasta. Lisätään listaan
				if (lahtoruudunNappulanVari != tuloruudunNappulanVari) {
					if (lahtoruutuY < 6)
						lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX + 1, lahtoruutuY + 1)));
					else
						lisaaSotilaanKorotukset(&Siirto(*ruutu, Ruutu(lahtoruutuX + 1, lahtoruutuY + 1)), lista, asema);
				}
			}
		}
		if (lahtoruutuX - 1 >= 0) {
			if (asema->_lauta[lahtoruutuX - 1][lahtoruutuY + 1] != NULL) {
				// Tarkistetaan että jos lähtöruudussa olevan nappulan väri on sama kuin tarkastelun alaisessa ruudussa, niin silloin on oma nappula
				tuloruudunNappulanVari = asema->_lauta[lahtoruutuX - 1][lahtoruutuY + 1]->getVari();
				if (lahtoruudunNappulanVari == tuloruudunNappulanVari) {
				}
				// jos vastustajan nappula niin lisätään listaan
				if (lahtoruudunNappulanVari != tuloruudunNappulanVari) {
					if (lahtoruutuY < 6)
						lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX - 1, lahtoruutuY + 1)));
					else
						lisaaSotilaanKorotukset(&Siirto(*ruutu, Ruutu(lahtoruutuX - 1, lahtoruutuY + 1)), lista, asema);
				}
			}
		}
	}
	// perusruudut mustille 
	if ((lahtoruutuY == 5 || lahtoruutuY == 4 || lahtoruutuY == 3 || lahtoruutuY == 2 || lahtoruutuY == 1) && lahtoruudunNappulanVari == 1) {
		//siirtymät eteenpäin
		if (asema->_lauta[lahtoruutuX][lahtoruutuY - 1] == NULL) {
			if (lahtoruutuY > 1)
				lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX, lahtoruutuY - 1)));
			else
				lisaaSotilaanKorotukset(&Siirto(*ruutu, Ruutu(lahtoruutuX, lahtoruutuY - 1)), lista, asema);
		}
		//syönnit viistoon
		if (lahtoruutuX + 1 < 8) { // tarkastetaan että pysytään laudalla
			if (asema->_lauta[lahtoruutuX + 1][lahtoruutuY - 1] != NULL) {
				// Tarkistetaan että jos lähtöruudussa olevan nappulan väri on sama kuin tarkastelun alaisessa ruudussa, niin silloin on oma nappula
				tuloruudunNappulanVari = asema->_lauta[lahtoruutuX + 1][lahtoruutuY - 1]->getVari();
				if (lahtoruudunNappulanVari == tuloruudunNappulanVari) {
				}
				// jos vastujan nappula niin poistutaan for silmukasta. Lisätään listaan
				if (lahtoruudunNappulanVari != tuloruudunNappulanVari) {
					if (lahtoruutuY > 1)
						lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX + 1, lahtoruutuY - 1)));
					else
						lisaaSotilaanKorotukset(&Siirto(*ruutu, Ruutu(lahtoruutuX + 1, lahtoruutuY - 1)), lista, asema);
				}
			}
		}
		if (lahtoruutuX - 1 >= 0) {
			if (asema->_lauta[lahtoruutuX - 1][lahtoruutuY - 1] != NULL) {
				// Tarkistetaan että jos lähtöruudussa olevan nappulan väri on sama kuin tarkastelun alaisessa ruudussa, niin silloin on oma nappula
				tuloruudunNappulanVari = asema->_lauta[lahtoruutuX - 1][lahtoruutuY - 1]->getVari();
				if (lahtoruudunNappulanVari == tuloruudunNappulanVari) {
				}
				// jos vastujan nappula niin poistutaan for silmukasta. Lisätään listaan
				if (lahtoruudunNappulanVari != tuloruudunNappulanVari) {
					if (lahtoruutuY > 1)
						lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX - 1, lahtoruutuY - 1)));
					else
						lisaaSotilaanKorotukset(&Siirto(*ruutu, Ruutu(lahtoruutuX - 1, lahtoruutuY - 1)), lista, asema);
				}
			}
		}
	}

	// Ohestalyönti on mahdollinen, jos jollain sarakkeella on viimeksi
	// tapahtunut sotilaan kaksoisaskel.
	if (asema->kaksoisaskelSarakkeella != -1)
	{
		if (vari == 0 && lahtoruutuY == 4)
		{
			if (asema->_lauta[asema->kaksoisaskelSarakkeella][4] && asema->_lauta[asema->kaksoisaskelSarakkeella][4]->getKoodi() == MS)
				lista.push_back(Siirto(*ruutu, Ruutu(asema->kaksoisaskelSarakkeella, 5)));
		}
		if (vari == 1 && lahtoruutuY == 3)
		{
			if (asema->_lauta[asema->kaksoisaskelSarakkeella][3] && asema->_lauta[asema->kaksoisaskelSarakkeella][3]->getKoodi() == VS)
				lista.push_back(Siirto(*ruutu, Ruutu(asema->kaksoisaskelSarakkeella, 2)));
		}
	}
}


void Sotilas::lisaaSotilaanKorotukset(Siirto* siirto, concurrency::concurrent_vector<Siirto>& lista, Asema* asema) {
	if (siirto->getLoppuruutu().getRivi() == 7) {
		// valkea korottaa
		siirto->_miksikorotetaan = asema->vd;
		lista.push_back(*siirto);

		Siirto torniksi = *siirto;
		torniksi._miksikorotetaan = asema->vt;
		lista.push_back(torniksi);

		Siirto lahetiksi = *siirto;
		lahetiksi._miksikorotetaan = asema->vl;
		lista.push_back(lahetiksi);

		Siirto ratsuksi = *siirto;
		ratsuksi._miksikorotetaan = asema->vr;
		lista.push_back(ratsuksi);
	}
	else if (siirto->getLoppuruutu().getRivi() == 0) {
		// musta korottaa
		siirto->_miksikorotetaan = asema->md;
		lista.push_back(*siirto);

		Siirto torniksi = *siirto;
		torniksi._miksikorotetaan = asema->mt;
		lista.push_back(torniksi);

		Siirto lahetiksi = *siirto;
		lahetiksi._miksikorotetaan = asema->ml;
		lista.push_back(lahetiksi);

		Siirto ratsuksi = *siirto;
		ratsuksi._miksikorotetaan = asema->mr;
		lista.push_back(ratsuksi);
	}
}
