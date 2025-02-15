#include <list>
#include <string>
#include "asema.h"
#include "nappula.h"
using namespace std;


Nappula::Nappula(wstring unicode, int vari, int koodi)
{
	_unicode = unicode;
	_vari = vari;
	_koodi = koodi;

}


void Torni::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	int lahtoruutuY = ruutu->getRivi();
	int lahtoruutuX = ruutu->getSarake();

	int lahtoruudunNappulanVari;

	lahtoruudunNappulanVari = asema->_lauta[lahtoruutuX][lahtoruutuY]->getVari();
	// vaakarivi ruudusta eteenp�in
	siirtoLoop(lista, ruutu, asema, lahtoruutuX, lahtoruutuY, 1, 0, lahtoruudunNappulanVari);
	// vaakarivi ruudusta taaksep�in
	siirtoLoop(lista, ruutu, asema, lahtoruutuX, lahtoruutuY, -1, 0, lahtoruudunNappulanVari);
	// pystyrivi ruudusta eteenp�in
	siirtoLoop(lista, ruutu, asema, lahtoruutuX, lahtoruutuY, 0, 1, lahtoruudunNappulanVari);
	// pystyrivi ruudusta taaksep�in
	siirtoLoop(lista, ruutu, asema, lahtoruutuX, lahtoruutuY, 0, -1, lahtoruudunNappulanVari);
	
}


void Ratsu::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	int lahtoruutuY = ruutu->getRivi();
	int lahtoruutuX = ruutu->getSarake();

	int lahtoruudunNappulanVari;
	int tuloruudunNappulanVari;

	lahtoruudunNappulanVari = asema->_lauta[lahtoruutuX][lahtoruutuY]->getVari();

	// Pit�� huomioida ett� kokeiltavat ruudut ovat viel� laudalla
	if (lahtoruutuX + 1 < 8 && lahtoruutuY + 2 < 8) {
		if (asema->_lauta[lahtoruutuX + 1][lahtoruutuY + 2] == NULL) {
			lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX + 1, lahtoruutuY + 2)));
		}
		else if (asema->_lauta[lahtoruutuX + 1][lahtoruutuY + 2] != NULL) {
			tuloruudunNappulanVari = asema->_lauta[lahtoruutuX + 1][lahtoruutuY + 2]->getVari();
			// jos oman v�rinen niin lis�t��n t�rmayslistaan
			if (lahtoruudunNappulanVari == tuloruudunNappulanVari) {
			}
			// jos vastujan nappula niin lis�t��n listaan
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
			// jos oman v�rinen niin lis�t��n t�rmayslistaan
			if (lahtoruudunNappulanVari == tuloruudunNappulanVari) {
			}
			// jos vastujan nappula niin lis�t��n listaan
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
			// jos oman v�rinen niin lis�t��n t�rmayslistaan
			if (lahtoruudunNappulanVari == tuloruudunNappulanVari) {
			}
			// jos vastujan nappula niin lis�t��n listaan
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
			// jos oman v�rinen niin lis�t��n t�rmayslistaan
			if (lahtoruudunNappulanVari == tuloruudunNappulanVari) {
			}
			// jos vastujan nappula niin lis�t��n listaan
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
			// jos oman v�rinen niin lis�t��n t�rmayslistaan
			if (lahtoruudunNappulanVari == tuloruudunNappulanVari) {
			}
			// jos vastujan nappula niin lis�t��n listaan
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
			// jos oman v�rinen niin lis�t��n t�rmayslistaan
			if (lahtoruudunNappulanVari == tuloruudunNappulanVari) {
			}
			// jos vastujan nappula niin lis�t��n listaan
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
			// jos oman v�rinen niin lis�t��n t�rmayslistaan
			if (lahtoruudunNappulanVari == tuloruudunNappulanVari) {
			}
			// jos vastujan nappula niin lis�t��n listaan
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
			// jos oman v�rinen niin lis�t��n t�rmayslistaan
			if (lahtoruudunNappulanVari == tuloruudunNappulanVari) {
			}
			// jos vastujan nappula niin lis�t��n listaan
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


void Lahetti::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	int lahtoruutuY = ruutu->getRivi();
	int lahtoruutuX = ruutu->getSarake();

	int lahtoruudunNappulanVari;
	int tuloruudunNappulanVari;

	int j;

	lahtoruudunNappulanVari = asema->_lauta[lahtoruutuX][lahtoruutuY]->getVari();

	// viistorivi ruudusta oikealle yl�s
	siirtoLoop(lista, ruutu, asema, lahtoruutuX, lahtoruutuY, 1, 1, lahtoruudunNappulanVari);

	// viistorivi ruudusta oikealle alas
	siirtoLoop(lista, ruutu, asema, lahtoruutuX, lahtoruutuY, 1, 0, lahtoruudunNappulanVari);

	// viistorivi ruudusta vasemmalle yl�s
	siirtoLoop(lista, ruutu, asema, lahtoruutuX, lahtoruutuY, 1, 0, lahtoruudunNappulanVari);
	// viistorivi ruudusta vasemmalle alas
	siirtoLoop(lista, ruutu, asema, lahtoruutuX, lahtoruutuY, 1, 0, lahtoruudunNappulanVari);
	
}


void Daami::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	this->Lahetti::annaSiirrot(lista, ruutu, asema, vari);
	this->Torni::annaSiirrot(lista, ruutu, asema, vari);
	
}


void Kuningas::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	/*perusidea on ett� kaikki viereiset ruudut ovat sallittuja. kuten tornilla ja l�hetill�,
	oman nappulan p��lle ei voi menn� ja vastustajan nappulan voi sy�d�.

	Kaikki muu kuninkaaseen liittyv� tarkistus tehd��n eri paikassa*/


	int lahtoruutuY = ruutu->getRivi();
	int lahtoruutuX = ruutu->getSarake();

	int lahtoruudunNappulanVari;
	int tuloruudunNappulanVari;

	lahtoruudunNappulanVari = asema->_lauta[lahtoruutuX][lahtoruutuY]->getVari();


	// K�yd��n perussiirtojen tyhj�t ruudut l�pi 
	// Pit�� tarkistaa ett� ehdokas ruutu viel� laudalla
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


void Sotilas::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	int lahtoruutuY = ruutu->getRivi();
	int lahtoruutuX = ruutu->getSarake();
	int lahtoruudunNappulanVari;
	int tuloruudunNappulanVari;
	lahtoruudunNappulanVari = asema->_lauta[lahtoruutuX][lahtoruutuY]->getVari();

	// jos sotilas rivill� 2 ja sotilas valkea tai sotilas rivill� 7 ja sotilas musta sill� on kaksois askel mahdollisuus
	// muilla riveill� sotilaalla yks�is aske
	// sotilas voi my�s sy�d� etuviistoon ruudustaan
	// sotilas voi korottua jos se saavuttaa rivin 8 valkeilla ja vastaavasti rivin 1 mustilla

	// valkea rivill� 2
	if (lahtoruutuY == 1 && lahtoruudunNappulanVari == 0) {
		for (int i = lahtoruutuY + 1; i < lahtoruutuY + 3; i++) {
			// Jos tyhj� ruutu niin lis�t��n listaan
			if (asema->_lauta[lahtoruutuX][i] == NULL) {
				lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX, i)));
			}
			else
				break;
		}
	}

	// musta rivill� 7
	if (lahtoruutuY == 6 && lahtoruudunNappulanVari == 1) {
		for (int i = lahtoruutuY - 1; i > lahtoruutuY - 3; i--) {
			// Jos tyhj� ruutu niin lis�t��n listaan
			if (asema->_lauta[lahtoruutuX][i] == NULL) {
				lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX, i)));
			}
			else
				break;
		}
	}
	// perusruudut valkeille 
	if ((lahtoruutuY == 2 || lahtoruutuY == 3 || lahtoruutuY == 4 || lahtoruutuY == 5 || lahtoruutuY == 6) && lahtoruudunNappulanVari == 0) {
		//siirtym�t eteenp�in
		if (asema->_lauta[lahtoruutuX][lahtoruutuY + 1] == NULL) {
			if (lahtoruutuY < 6)
				lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX, lahtoruutuY + 1)));
			else
				lisaaSotilaanKorotukset(&Siirto(*ruutu, Ruutu(lahtoruutuX, lahtoruutuY + 1)), lista, asema);
		}
		//sy�nnit viistoon
		if (lahtoruutuX + 1 < 8) { // tarkastetaan ett� pysyt��n laudalla
			if (asema->_lauta[lahtoruutuX + 1][lahtoruutuY + 1] != NULL) {
				// Tarkistetaan ett� jos l�ht�ruudussa olevan nappulan v�ri on sama kuin tarkastelun alaisessa ruudussa, niin silloin on oma nappula
				tuloruudunNappulanVari = asema->_lauta[lahtoruutuX + 1][lahtoruutuY + 1]->getVari();
				if (lahtoruudunNappulanVari == tuloruudunNappulanVari) {
				}
				// jos vastujan nappula niin poistutaan for silmukasta. Lis�t��n listaan
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
				// Tarkistetaan ett� jos l�ht�ruudussa olevan nappulan v�ri on sama kuin tarkastelun alaisessa ruudussa, niin silloin on oma nappula
				tuloruudunNappulanVari = asema->_lauta[lahtoruutuX - 1][lahtoruutuY + 1]->getVari();
				if (lahtoruudunNappulanVari == tuloruudunNappulanVari) {
				}
				// jos vastustajan nappula niin lis�t��n listaan
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
		//siirtym�t eteenp�in
		if (asema->_lauta[lahtoruutuX][lahtoruutuY - 1] == NULL) {
			if (lahtoruutuY > 1)
				lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX, lahtoruutuY - 1)));
			else
				lisaaSotilaanKorotukset(&Siirto(*ruutu, Ruutu(lahtoruutuX, lahtoruutuY - 1)), lista, asema);
		}
		//sy�nnit viistoon
		if (lahtoruutuX + 1 < 8) { // tarkastetaan ett� pysyt��n laudalla
			if (asema->_lauta[lahtoruutuX + 1][lahtoruutuY - 1] != NULL) {
				// Tarkistetaan ett� jos l�ht�ruudussa olevan nappulan v�ri on sama kuin tarkastelun alaisessa ruudussa, niin silloin on oma nappula
				tuloruudunNappulanVari = asema->_lauta[lahtoruutuX + 1][lahtoruutuY - 1]->getVari();
				if (lahtoruudunNappulanVari == tuloruudunNappulanVari) {
				}
				// jos vastujan nappula niin poistutaan for silmukasta. Lis�t��n listaan
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
				// Tarkistetaan ett� jos l�ht�ruudussa olevan nappulan v�ri on sama kuin tarkastelun alaisessa ruudussa, niin silloin on oma nappula
				tuloruudunNappulanVari = asema->_lauta[lahtoruutuX - 1][lahtoruutuY - 1]->getVari();
				if (lahtoruudunNappulanVari == tuloruudunNappulanVari) {
				}
				// jos vastujan nappula niin poistutaan for silmukasta. Lis�t��n listaan
				if (lahtoruudunNappulanVari != tuloruudunNappulanVari) {
					if (lahtoruutuY > 1)
						lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX - 1, lahtoruutuY - 1)));
					else
						lisaaSotilaanKorotukset(&Siirto(*ruutu, Ruutu(lahtoruutuX - 1, lahtoruutuY - 1)), lista, asema);
				}
			}
		}
	}

	// Ohestaly�nti on mahdollinen, jos jollain sarakkeella on viimeksi
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


void Sotilas::lisaaSotilaanKorotukset(Siirto* siirto, std::list<Siirto>& lista, Asema* asema) {
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
