#include <list>
#include <string>
#include "asema.h"
#include "nappula.h"
using namespace std;


Nappula::Nappula(wstring unicode, int vari, int koodi)
{
	this->_unicode = unicode;
	this->_vari = vari;
	this->_koodi = koodi;

}


void Torni::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{

}


void Ratsu::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{

}


void Lahetti::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{

}


void Daami::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{

}


void Kuningas::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	/*perusidea on ett� kaikki viereiset ruudut ovat sallittuja. kuten tornilla ja l�hetill�,
	oman nappulan p��lle ei voi menn� ja vastustajan nappulan voi sy�d�.

	Kaikki muu kuninkaaseen liittyv� tarkistus tehd��n eri paikassa*/



}


void Sotilas::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	int n_i = ruutu->getRivi();
	int n_j = ruutu->getSarake();

	int n_v = vari;


	if (vari == 1)
	{

		//mustan siirrot
		if (asema->_lauta[n_i][n_j--] == NULL) {
			lista.push_back(Siirto(*ruutu, Ruutu(n_i, n_j--)));
		}

		if (asema->_lauta[n_i][n_j--] == NULL && asema->_lauta[n_i][(--n_j)--] == NULL && n_j == 6) {
			lista.push_back(Siirto(*ruutu, Ruutu(n_i, (--n_j)--)));
			asema->kaksoisaskelSarakkeella = n_j;
		}

		if (asema->_lauta[n_i++][n_j--] != NULL && asema->_lauta[n_i++][n_j--]->getVari() != n_v)
		{
			lista.push_back(Siirto(*ruutu, Ruutu(n_i++, n_j--)));
		}

		if (asema->_lauta[n_i--][n_j--] != NULL && asema->_lauta[n_i--][n_j--]->getVari() != n_v)
		{
			lista.push_back(Siirto(*ruutu, Ruutu(n_i--, n_j--)));
		}
	}
	else
	{
		//valkoisen siirrot

	}
}


void Sotilas::lisaaSotilaanKorotukset(Siirto* siirto, std::list<Siirto>& lista, Asema* asema)
{

}
