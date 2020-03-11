#pragma once

#include <list>
#include <string>
#include "asema.h"
#include "siirto.h"


// Vakioarvot nappulatyypeille.
enum
{
	VT, VR, VL, VD, VK, VS,
	MT, MR, ML, MD, MK, MS
};


// Yliluokka shakkinappuloille.
class Nappula
{

private:
	std::wstring	_unicode;	// nappulaa vastaava unicode-merkki
	int				_vari;		// valkea = 0, musta = 1
	int				_koodi;		// VT, VR, MT tms
	Nappula*			_empty[1][2] = { {nullptr, nullptr} };



public:
	Nappula(std::wstring, int, int);
	Nappula() {}

	// Siirtojen generointi. Puhdas virtuaalifunktio, eli aliluokat toteuttavat tämän
	// omalla tavallaan.
	virtual void annaSiirrot(std::list<Siirto>& lista, Ruutu*, Asema*, int vari) = 0;

	void setUnicode(std::wstring unicode) { _unicode = unicode; }
	std::wstring getUnicode() { return _unicode; }
	void setVari(int vari) { _vari = vari; }
	int getVari() { return _vari; }
	int getKoodi() { return _koodi; }
	void setKoodi(int koodi) { _koodi = koodi; }

	int siirtoLoop(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int paikkaX, int paikkaY, int suuntaX, int suuntaY, int nappulanVari)
	{
		int _alkuX = paikkaX; //oman nappulan paikka (X)
		int _alkuY = paikkaY; //oman nappulan paikka (Y)
		int _uusiX, _uusiY; //tarkistettava paikka

		int _omaVari = nappulanVari; //oman nappulan väri (lähtöruudussa oleva)
		int _toisenVari; //toisessa ruudussa olevan nappulan väri

		int _xSuunta = suuntaX; //-1 , 0 tai 1
		int _ySuunta = suuntaY; //-1 , 0 tai 1

		//alustetaan paikka, jotta nappula ei tutki omaa paikkaansa
		
		_uusiY = _alkuY + _ySuunta;
		_uusiX = _alkuX + _xSuunta;
		for (int i = 0; i < 8 ; i++)
		{

			if (_uusiX < 0 || _uusiX > 7 || _uusiY < 0 || _uusiY > 7) 
			{
				//menee yli
				return 0;
			}
			// ei mitääm tässä, tähän voi mennä
			if (asema->_lauta[_uusiX][_uusiY] == NULL){
				lista.push_back(Siirto(*ruutu, Ruutu(_uusiX, _uusiY)));
				
			}
			//tässä nappula, katsotaan voiko syyä
			if (asema->_lauta[_uusiX][_uusiY] != NULL)
			{
				//haetaan toisen nappulan väri
				_toisenVari = asema->_lauta[_uusiX][_uusiY]->getVari();
				//oma, ei voi syyä
				if (_omaVari == _toisenVari) 
				{
					return 0;
				}
				//ei oma, voi syyä
				if (_omaVari != _toisenVari) 
				{
					lista.push_back(Siirto(*ruutu, Ruutu(_uusiX, _uusiY)));
					return 0;
				}
				
			}

			

		 _uusiY = _uusiY + _ySuunta;
		 _uusiX = _uusiX + _xSuunta;
		}

		return 1;
	}
};

// Torni-aliluokka. Virtuaalinen perintä tarkoittaa, että kantaluokka peritään moniperinnässä vain kerran
// (koska daami perii sekä tornin että lähetin).
class Torni : public virtual Nappula {
public:
	Torni(std::wstring unicode, int vari, int koodi) : Nappula(unicode, vari, koodi) {}
	void annaSiirrot(std::list<Siirto>& lista, Ruutu*, Asema*, int vari);
};

// Ratsu-aliluokka.
class Ratsu : public Nappula {
public:
	Ratsu(std::wstring unicode, int vari, int koodi) : Nappula(unicode, vari, koodi) {}
	void annaSiirrot(std::list<Siirto>& lista, Ruutu*, Asema*, int vari);
};

// Lähetti-aliluokka. Virtuaalinen perintä tarkoittaa, että kantaluokka peritään moniperinnässä vain kerran
// (koska daami perii sekä tornin että lähetin).
class Lahetti : public virtual Nappula {
public:
	Lahetti(std::wstring unicode, int vari, int koodi) : Nappula(unicode, vari, koodi) {}
	void annaSiirrot(std::list<Siirto>& lista, Ruutu*, Asema*, int vari);
};

// Daami-aliluokka. Perii sekä lähetin että tornin.
class Daami : public Lahetti, public Torni {
public:
	Daami(std::wstring unicode, int vari, int koodi) :
		Nappula(unicode, vari, koodi), Lahetti(unicode, vari, koodi), Torni(unicode, vari, koodi) {}
	void annaSiirrot(std::list<Siirto>& lista, Ruutu*, Asema*, int vari);
};

// Kuningas-aliluokka.
class Kuningas : public Nappula {
public:
	Kuningas(std::wstring unicode, int vari, int koodi) : Nappula(unicode, vari, koodi) {}
	void annaSiirrot(std::list<Siirto>& lista, Ruutu*, Asema*, int vari);
};

// Sotilas-aliluokka.
class Sotilas : public Nappula {
public:
	Sotilas(std::wstring unicode, int vari, int koodi) : Nappula(unicode, vari, koodi) {}
	void annaSiirrot(std::list<Siirto>& lista, Ruutu*, Asema*, int vari);
private:
	void lisaaSotilaanKorotukset(Siirto*, std::list<Siirto>& lista, Asema*);
};


