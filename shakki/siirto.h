#pragma once
#include "ruutu.h"

// Ns. "forward declaration". Nyt Asema-luokassa voidaa esitell� Nappula-osoittimia ilman,
// ett� nappula.h -tiedostoa t�ytyy includoida.
class Nappula;


// Siirto kuvaa nappulan siirtymisen ruudusta toiseen, mukaanlukien erikoissiirrot
// (linnoitus ja ohestaly�nti).
class Siirto
{
public:

	Siirto(Ruutu, Ruutu);
	Siirto() {
		_alkuRuutu = Ruutu(-1, -1);
		_loppuRuutu = Ruutu(-1, -1);
		_pitkaLinna = false;
		_lyhytLinna = false;
	}
	Siirto(bool, bool, bool); // Linnoitus lyhesti (K-siipi) tai pitk�sti (D-siipi)?
	Ruutu getAlkuruutu();
	Ruutu getLoppuruutu();
	bool onkoLyhytLinna();
	bool onkoPitkaLinna();
	bool onkoMahdollinen();

	Nappula* _miksikorotetaan = 0;

private:
	Ruutu _alkuRuutu;
	Ruutu _loppuRuutu;
	bool _lyhytLinna;
	bool _pitkaLinna;
	bool _mahdollinen;
};