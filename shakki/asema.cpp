#include <iostream>
#include <ppl.h>
#include "asema.h"
#include "minMaxPaluu.h"
#include "nappula.h"
#include "ruutu.h"

#pragma optimize("g", on)

Nappula* Asema::vk = new Kuningas(L"\u2654", 0, VK);
Nappula* Asema::vd = new Daami(L"\u2655", 0, VD);
Nappula* Asema::vt = new Torni(L"\u2656", 0, VT);
Nappula* Asema::vl = new Lahetti(L"\u2657", 0, VL);
Nappula* Asema::vr = new Ratsu(L"\u2658", 0, VR);
Nappula* Asema::vs = new Sotilas(L"\u2659", 0, VS);

Nappula* Asema::mk = new Kuningas(L"\u265A", 1, MK);
Nappula* Asema::md = new Daami(L"\u265B", 1, MD);
Nappula* Asema::mt = new Torni(L"\u265C", 1, MT);
Nappula* Asema::ml = new Lahetti(L"\u265D", 1, ML);
Nappula* Asema::mr = new Ratsu(L"\u265E", 1, MR);
Nappula* Asema::ms = new Sotilas(L"\u265F", 1, MS);


Asema::Asema()
{
	// Ensin alustetaan kaikki laudan ruudut nappulla "NULL", koska muuten ruuduissa satunnaista tauhkaa
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			_lauta[i][j] = NULL;
	// Asetetaan alkuaseman mukaisesti nappulat ruuduille
	_lauta[0][0] = vt;
	_lauta[1][0] = vr;
	_lauta[2][0] = vl;
	_lauta[3][0] = vd;
	_lauta[4][0] = vk;
	_lauta[5][0] = vl;
	_lauta[6][0] = vr;
	_lauta[7][0] = vt;

	_lauta[0][1] = vs;
	_lauta[1][1] = vs;
	_lauta[2][1] = vs;
	_lauta[3][1] = vs;
	_lauta[4][1] = vs;
	_lauta[5][1] = vs;
	_lauta[6][1] = vs;
	_lauta[7][1] = vs;

	_lauta[0][7] = mt;
	_lauta[1][7] = mr;
	_lauta[2][7] = ml;
	_lauta[3][7] = md;
	_lauta[4][7] = mk;
	_lauta[5][7] = ml;
	_lauta[6][7] = mr;
	_lauta[7][7] = mt;

	_lauta[0][6] = ms;
	_lauta[1][6] = ms;
	_lauta[2][6] = ms;
	_lauta[3][6] = ms;
	_lauta[4][6] = ms;
	_lauta[5][6] = ms;
	_lauta[6][6] = ms;
	_lauta[7][6] = ms;
	// Kunkun testausta varten
	/*_lauta[7][5] = vk;
	_lauta[5][5] = mt;
	_lauta[4][3] = ml;
	_lauta[3][3] = vs;*/

	//_lauta[4][4] = vr;

	_siirtovuoro = 0;
	_onkoValkeaKuningasLiikkunut = false;
	_onkoMustaKuningasLiikkunut = false;
	_onkoValkeaDTliikkunut = false;
	_onkoValkeaKTliikkunut = false;
	_onkoMustaDTliikkunut = false;
	_onkoMustaKTliikkunut = false;

}


void Asema::paivitaAsema(Siirto *siirto)
{

	// Kaksoisaskel-lippu on oletusarvoisesti pois p‰‰lt‰.
	// Asetetaan myˆhemmin, jos tarvii.
	this->kaksoisaskelSarakkeella = -1;

	//Tarkastetaan on siirto lyhyt linna
	if (siirto->onkoLyhytLinna()) {
		if (_siirtovuoro == 0) {
			_lauta[4][0] = NULL; // kuninkaan paikalle tyhj‰
			_lauta[6][0] = vk; // kuningas uudelle paikalle
			_lauta[7][0] = NULL; // tornin paikalle tyhj‰
			_lauta[5][0] = vt; // torni uudella paikalle
		}
		if (_siirtovuoro == 1) {
			_lauta[4][7] = NULL; // kuninkaan paikalle tyhj‰
			_lauta[6][7] = mk; // kuningas uudelle paikalle
			_lauta[7][7] = NULL; // tornin paikalle tyhj‰
			_lauta[5][7] = mt; // torni uudella paikalle
		}
	}

	// onko pitk‰ linna
	else if (siirto->onkoPitkaLinna()) {
		if (_siirtovuoro == 0) {
			_lauta[4][0] = NULL; // kuninkaan paikalle tyhj‰
			_lauta[2][0] = vk; // kuningas uudelle paikalle
			_lauta[0][0] = NULL; // tornin paikalle tyhj‰
			_lauta[3][0] = vt; // torni uudella paikalle
		}
		if (_siirtovuoro == 1) {
			_lauta[4][7] = NULL; // kuninkaan paikalle tyhj‰
			_lauta[2][7] = mk; // kuningas uudelle paikalle
			_lauta[0][7] = NULL; // tornin paikalle tyhj‰
			_lauta[3][7] = mt; // torni uudella paikalle
		}

	}
	else {// Kaikki muut siirrot

		int alkuRiviInt;
		int alkuSarakeInt;
		int loppuRiviInt;
		int loppuSarakeInt;

		//Ottaa siirron alkuruudussa olleen nappulan talteen 
		alkuRiviInt = siirto->getAlkuruutu().getRivi();
		alkuSarakeInt = siirto->getAlkuruutu().getSarake();
		Nappula* nappula = _lauta[alkuSarakeInt][alkuRiviInt];

		//Laittaa talteen otetun nappulan uuteen ruutuun
		loppuRiviInt = siirto->getLoppuruutu().getRivi();
		loppuSarakeInt = siirto->getLoppuruutu().getSarake();

		// Tarkistetaan oliko sotilaan kaksoisaskel
		// (asetetaan kaksoisaskel-lippu)
		if
			(
			(_lauta[alkuSarakeInt][alkuRiviInt]->getKoodi() == VS || _lauta[alkuSarakeInt][alkuRiviInt]->getKoodi() == MS) &&
				(alkuRiviInt - loppuRiviInt == 2 || alkuRiviInt - loppuRiviInt == -2)
				)
			kaksoisaskelSarakkeella = alkuSarakeInt;

		// Ohestalyˆnti on tyhj‰‰n ruutuun. Vieress‰ oleva (sotilas) poistetaan.
		if
			(
			(_lauta[alkuSarakeInt][alkuRiviInt]->getKoodi() == VS || _lauta[alkuSarakeInt][alkuRiviInt]->getKoodi() == MS) &&
				(alkuSarakeInt != loppuSarakeInt) &&
				(_lauta[loppuSarakeInt][loppuRiviInt] == NULL)
				)
			_lauta[loppuSarakeInt][alkuRiviInt] = NULL;

		//// Katsotaan jos nappula on sotilas ja rivi on p‰‰tyrivi niin ei vaihdeta nappulaa 
		////eli alkuruutuun laitetaan null ja loppuruudussa on jo kliittym‰n laittama nappula MIIKKA, ei taida minmaxin kanssa hehkua?
		//if ((nappula->getKoodi() == VS || nappula->getKoodi() == MS) && (loppuRiviInt == 0 || loppuRiviInt == 7)) {
		//	_lauta[alkuSarakeInt][alkuRiviInt] = NULL;
		//}
		////muissa tapauksissa alkuruutuun null ja loppuruutuun sama alkuruudusta l‰htenyt nappula
		//else {
		_lauta[alkuSarakeInt][alkuRiviInt] = NULL;
		_lauta[loppuSarakeInt][loppuRiviInt] = nappula;
		if (siirto->_miksikorotetaan != NULL)
			_lauta[loppuSarakeInt][loppuRiviInt] = siirto->_miksikorotetaan;
		//		}
				// katsotaan jos liikkunut nappula on kuningas niin muutetaan onkoKuningasLiikkunut arvo (molemmille v‰reille)
		if (nappula->getKoodi() == VK) {
			_onkoValkeaKuningasLiikkunut = true;
		}
		if (nappula->getKoodi() == MK) {
			_onkoMustaKuningasLiikkunut = true;
		}
		// katsotaan jos liikkunut nappula on torni niin muutetaan onkoTorniLiikkunut arvo (molemmille v‰reille ja molemmille torneille)
		if (nappula->getKoodi() == VT && alkuSarakeInt == 7 && alkuRiviInt == 0) {
			_onkoValkeaKTliikkunut = true;
		}
		if (nappula->getKoodi() == VT && alkuSarakeInt == 0 && alkuRiviInt == 0) {
			_onkoValkeaDTliikkunut = true;
		}
		if (nappula->getKoodi() == MT && alkuSarakeInt == 7 && alkuRiviInt == 7) {
			_onkoMustaKTliikkunut = true;
		}
		if (nappula->getKoodi() == VT && alkuSarakeInt == 0 && alkuRiviInt == 7) {
			_onkoMustaDTliikkunut = true;
		}
	}
	//p‰ivitet‰‰n _siirtovuoro
	if (_siirtovuoro == 0)
		_siirtovuoro = 1;
	else
		_siirtovuoro = 0;
}
/*Nappula Asema::annaNappulaRuudusta(Ruutu *ruutu){
	int sarake = ruutu->getSarake();
	int rivi = ruutu->getRivi();
	return *_lauta[rivi][sarake];
}*/


int Asema::getSiirtovuoro()
{
	return this->_siirtovuoro;
}


void Asema::setSiirtovuoro(int vuoro)
{
	this->_siirtovuoro = vuoro;
}


bool Asema::getOnkoValkeaKuningasLiikkunut()
{
	return this->_onkoValkeaKuningasLiikkunut;
}


bool Asema::getOnkoMustaKuningasLiikkunut()
{
	return this->_onkoMustaKuningasLiikkunut;
}


bool Asema::getOnkoValkeaDTliikkunut()
{
	return this->_onkoValkeaDTliikkunut;
}


bool Asema::getOnkoValkeaKTliikkunut()
{
	return this->_onkoValkeaKTliikkunut;
}


bool Asema::getOnkoMustaDTliikkunut()
{
	return this->_onkoMustaDTliikkunut;
}


bool Asema::getOnkoMustaKTliikkunut()
{
	return this->_onkoMustaKTliikkunut;
}


/* 1. Laske nappuloiden arvo
Daami = 9
Torni = 5
L‰hetti = 3,25
Ratsu = 3
Sotilas = 1

2. Kuninkaan hyvyys
Jos avaus tai keskipeli, niin hyv‰ ett‰ kunigas g1 tai b1/c1
Loppupeliss‰ vaikea sanoa halutaanko olla auttamassa omaa sotilasta korottumaan
vai olla est‰m‰ss‰ vastustajan korotusta siksi ei oteta kantaa
3. Arvosta keskustaa sotilailla ja ratsuilla
4. Arvosta pitki‰ linjoja daami, torni ja l‰hetti
*/
double Asema::evaluoi()
{
	double valkeaArvo = 0;
	double mustaArvo = 0;

	//kertoimet asetettu sen takia ett‰ niiden avulla asioiden painoarvoa voidaan s‰‰t‰‰ helposti yhdest‰ paikasta
	double kuningasKerroin = 1;
	double keskustaKerroin = 1;
	double linjaKerroin = 0.05;
	//1. Nappuloiden arvo
	valkeaArvo += laskeNappuloidenArvo(0);
	mustaArvo += laskeNappuloidenArvo(1);
	//2. Kuningas turvassa
	//if (onkoAvausTaiKeskipeli(asema, 0)) {
	//	// Jos lyhell‰ puolella saa lis‰arvoa 2 edellytt‰‰ ett‰ f ja g sotilas  paikallaan 
	//	if (this->_lauta[6][0] != NULL && this->_lauta[5][1] != NULL && this->_lauta[6][1] != NULL) {
	//		if (this->_lauta[6][0]->getKoodi() == VK && (this->_lauta[5][1]->getKoodi() == VS && (this->_lauta[6][1]->getKoodi() == VS)))
	//			valkeaArvo += 2 * kuningasKerroin;
	//	}
	//	// Jos pitk‰ll‰ puolella saa lis‰arvooa 1 edelytt‰‰ ett‰  c ja b sotilas paikallaan
	//	if (this->_lauta[1][0] != NULL && this->_lauta[2][0] != NULL && this->_lauta[1][1] != NULL && this->_lauta[2][1] != NULL) {
	//		if (this->_lauta[1][0]->getKoodi() == VK || this->_lauta[2][0]->getKoodi() == VK && (this->_lauta[1][1]->getKoodi() == VS && (this->_lauta[2][1]->getKoodi() == VS)))
	//			valkeaArvo += 1 * kuningasKerroin;
	//	}
	//}
	//if (onkoAvausTaiKeskipeli(asema, 1)) {
	//	// Jos lyhell‰ puolella saa lis‰arvoa 2 edellytt‰‰ ett‰ f ja g sotilas  paikallaan 
	//	if (this->_lauta[6][7] != NULL && this->_lauta[5][6] != NULL && this->_lauta[6][6] != NULL) {
	//		if (this->_lauta[6][7]->getKoodi() == MK && (this->_lauta[5][6]->getKoodi() == MS && (this->_lauta[6][6]->getKoodi() == MS)))
	//			valkeaArvo += 2 * kuningasKerroin;
	//	}
	//	// Jos pitk‰ll‰ puolella saa lis‰arvooa 1 edelytt‰‰ ett‰  c ja b sotilas paikallaan
	//	if (this->_lauta[1][7] != NULL && this->_lauta[2][7] != NULL && this->_lauta[1][7] != NULL && this->_lauta[2][7] != NULL) {
	//		if (this->_lauta[1][7]->getKoodi() == MK || this->_lauta[2][7]->getKoodi() == MK && (this->_lauta[1][7]->getKoodi() == MS && (this->_lauta[2][7]->getKoodi() == MS)))
	//			valkeaArvo += 1 * kuningasKerroin;
	//	}
	//}
	//3. Arvosta keskustaa
	valkeaArvo = nappuloitaKeskella(0) * keskustaKerroin;
	mustaArvo = nappuloitaKeskella(1) * keskustaKerroin;
	// 4. Arvosta linjoja
	valkeaArvo = linjaKerroin * linjat(0);
	mustaArvo = linjaKerroin * linjat(1);

	return valkeaArvo - mustaArvo;
}


double Asema::laskeNappuloidenArvo(int vari)
{
	double valkeaArvo = 0;
	double mustaArvo = 0;
	for (int x = 0; x < 8; x++) {
		for (int y = 0; y < 8; y++) {
			if (this->_lauta[x][y] != NULL) {
				int nappulanNimi = this->_lauta[x][y]->getKoodi();
				//Valkoiset
				if (nappulanNimi == VD)
					valkeaArvo += 9;
				if (nappulanNimi == VT)
					valkeaArvo += 5;
				if (nappulanNimi == VL)
					valkeaArvo += 3.25;
				if (nappulanNimi == VR)
					valkeaArvo += 3;
				if (nappulanNimi == VS)
					valkeaArvo += 1;
				//Mustat
				if (nappulanNimi == MD)
					mustaArvo += 9;
				if (nappulanNimi == MT)
					mustaArvo += 5;
				if (nappulanNimi == ML)
					mustaArvo += 3.25;
				if (nappulanNimi == MR)
					mustaArvo += 3;
				if (nappulanNimi == MS)
					mustaArvo += 1;
			}
		}
	}
	if (vari == 0)
		return valkeaArvo;
	else
		return mustaArvo;
}


bool Asema::onkoAvausTaiKeskipeli(int vari)
{
	// Jos upseereita 3 tai v‰hemm‰n on loppupeli
	// mutta jos daami laudalla on loppueli vasta kun kuin vain daami j‰ljell‰
	int valkeaUpseeriLkm = 0;
	int mustaUpseeriLkm = 0;
	bool valkeaDaami = false;
	bool mustaDaami = false;
	//for (int x = 0; x < 8; x++) {
	concurrency::parallel_for(size_t(0), size_t(8), [&](size_t i){
		for (int j = 0; j < 8; j++) {
			if (this->_lauta[i][j] == NULL) {
				continue;
			}
			int nappulanNimi = this->_lauta[i][j]->getKoodi();
			//Valkoiset
			if (nappulanNimi == VD) {
				valkeaUpseeriLkm += 1;
				valkeaDaami = true;
			}
			if (nappulanNimi == VT)
				valkeaUpseeriLkm += 1;
			if (nappulanNimi == VL)
				valkeaUpseeriLkm += 1;
			if (nappulanNimi == VR)
				valkeaUpseeriLkm += 1;

			//Mustat
			if (nappulanNimi == MD) {
				valkeaUpseeriLkm += 1;
				mustaDaami = true;
			}
			if (nappulanNimi == MT)
				valkeaUpseeriLkm += 1;
			if (nappulanNimi == ML)
				valkeaUpseeriLkm += 1;
			if (nappulanNimi == MR)
				valkeaUpseeriLkm += 1;
		}
	});
	//Jos vari on 0 eli valkoiset
	//niin on keskipeli jos mustalla upseereita yli 2 tai jos daami+1
	if (vari == 0) {
		if (mustaUpseeriLkm > 2 || (mustaDaami == true && mustaUpseeriLkm > 1))
			return true;
		else
			return false;
	}
	else {
		if (valkeaUpseeriLkm > 2 || (valkeaDaami == true && valkeaUpseeriLkm > 1))
			return true;
		else
			return false;
	}

}


double Asema::nappuloitaKeskella(int vari)
{

	//sotilaat ydinkeskustassa + 0.25/napa
	//ratsut ydinkeskustassa + 0.25/napa
	//sotilaat laitakeskustassa + 0.11/napa
	//ratsut laitakeskustassa + 0.11/napa
	double valkeaKeskella = 0;
	double mustaKeskella = 0;
	//valkeille ydinkeskusta

	if (this->_lauta[3][3] != NULL && (this->_lauta[3][3]->getKoodi() == VS || this->_lauta[3][3]->getKoodi() == VR)) {
		valkeaKeskella += 0.25;
	}
	if (this->_lauta[4][3] && (this->_lauta[4][3]->getKoodi() == VS || this->_lauta[4][3]->getKoodi() == VR)) {
		valkeaKeskella += 0.25;
	}
	if (this->_lauta[3][4] != NULL && (this->_lauta[3][4]->getKoodi() == VS || this->_lauta[3][4]->getKoodi() == VR)) {
		valkeaKeskella += 0.25;
	}
	if (this->_lauta[4][4] != NULL && (this->_lauta[4][4]->getKoodi() == VS || this->_lauta[4][4]->getKoodi() == VR)) {
		valkeaKeskella += 0.25;
	}
	//valkeille laitakeskusta
	for (int x = 2; x < 6; x++) {
		if (this->_lauta[x][2] != NULL && (this->_lauta[x][2]->getKoodi() == VS || this->_lauta[x][2]->getKoodi() == VR)) {
			valkeaKeskella += 0.11;
		}
		if (this->_lauta[x][5] != NULL && (this->_lauta[x][5]->getKoodi() == VS || this->_lauta[x][5]->getKoodi() == VR)) {
			valkeaKeskella += 0.11;
		}
	}
	for (int y = 3; y < 5; y++) {
		if (this->_lauta[2][y] != NULL && (this->_lauta[2][y]->getKoodi() == VS || this->_lauta[2][y]->getKoodi() == VR)) {
			valkeaKeskella += 0.11;
		}
		if (this->_lauta[5][y] != NULL && (this->_lauta[5][y]->getKoodi() == VS || this->_lauta[5][y]->getKoodi() == VR)) {
			valkeaKeskella += 0.11;
		}
	}

	//mustille ydinkeskusta
	if (this->_lauta[3][3] != NULL && (this->_lauta[3][3]->getKoodi() == MS || this->_lauta[3][3]->getKoodi() == MR)) {
		mustaKeskella += 0.25;
	}
	if (this->_lauta[4][3] != NULL && (this->_lauta[4][3]->getKoodi() == MS || this->_lauta[4][3]->getKoodi() == MR)) {
		mustaKeskella += 0.25;
	}
	if (this->_lauta[3][4] != NULL && (this->_lauta[3][4]->getKoodi() == MS || this->_lauta[3][4]->getKoodi() == MR)) {
		mustaKeskella += 0.25;
	}
	if (this->_lauta[4][4] != NULL && (this->_lauta[4][4]->getKoodi() == MS || this->_lauta[4][4]->getKoodi() == MR)) {
		mustaKeskella += 0.25;
	}
	//mustille laitakeskusta
	for (int x = 2; x < 6; x++) {
		if (this->_lauta[x][2] != NULL && (this->_lauta[x][2]->getKoodi() == MS || this->_lauta[x][2]->getKoodi() == MR)) {
			mustaKeskella += 0.11;
		}
		if (this->_lauta[x][5] != NULL && (this->_lauta[x][5]->getKoodi() == MS || this->_lauta[x][5]->getKoodi() == MR)) {
			mustaKeskella += 0.11;
		}
	}
	for (int y = 3; y < 5; y++) {
		if (this->_lauta[2][y] != NULL && (this->_lauta[2][y]->getKoodi() == MS || this->_lauta[2][y]->getKoodi() == MR)) {
			mustaKeskella += 0.11;
		}
		if (this->_lauta[5][y] != NULL && (this->_lauta[5][y]->getKoodi() == MS || this->_lauta[5][y]->getKoodi() == MR)) {
			mustaKeskella += 0.11;
		}
	}
	if (vari == 0)
		return valkeaKeskella;
	else
		return mustaKeskella;
}


double Asema::linjat(int vari)
{
	int valkeaLaillisiaSiirtoja = 0;
	int mustaLaillisiaSiirtoja = 0;
	concurrency::concurrent_vector<Siirto> valkealista;
	concurrency::concurrent_vector<Siirto> mustalista;
	//valkoiset
	for (int x = 0; x < 8; x++) {
		for (int y = 0; y < 8; y++) {
			if (this->_lauta[x][y] == NULL) {
				continue;
			}
			if (this->_lauta[x][y]->getKoodi() == VL)
				this->_lauta[x][y]->annaSiirrot(valkealista, &Ruutu(x, y), this, 0);
			if (this->_lauta[x][y]->getKoodi() == VT)
				this->_lauta[x][y]->annaSiirrot(valkealista, &Ruutu(x, y), this, 0);
			if (this->_lauta[x][y]->getKoodi() == VD)
				this->_lauta[x][y]->annaSiirrot(valkealista, &Ruutu(x, y), this, 0);
		}
	}
	//mustat
	for (int x = 0; x < 8; x++) {
		for (int y = 0; y < 8; y++) {
			if (this->_lauta[x][y] == NULL) {
				continue;
			}
			if (this->_lauta[x][y]->getKoodi() == ML)
				this->_lauta[x][y]->annaSiirrot(mustalista, &Ruutu(x, y), this, 0);
			if (this->_lauta[x][y]->getKoodi() == MT)
				this->_lauta[x][y]->annaSiirrot(mustalista, &Ruutu(x, y), this, 0);
			if (this->_lauta[x][y]->getKoodi() == MD)
				this->_lauta[x][y]->annaSiirrot(mustalista, &Ruutu(x, y), this, 0);
		}
	}
	valkeaLaillisiaSiirtoja = valkealista.size();
	mustaLaillisiaSiirtoja = mustalista.size();

	if (vari == 0)
		return valkeaLaillisiaSiirtoja;
	else
		return mustaLaillisiaSiirtoja;
}


// https://chessprogramming.wikispaces.com/Minimax MinMax-algoritmin pseudokoodi (lis‰sin parametrina aseman)
//int maxi(int depth, asema a) {
//	if (depth == 0) return evaluate();
//	int max = -oo;
//	for (all moves ) {
//		score = mini(depth - 1, seuraaja);
//		if (score > max)
//			max = score;
//	}
//	return max;
//}

//int mini(int depth, asema a) {
//	if (depth == 0) return -evaluate();
//	int min = +oo;
//	for (all moves) {
//		score = maxi(depth - 1);
//		if (score < min)
//			min = score;
//	}
//	return min;
//}
MinMaxPaluu Asema::minimax(int syvyys)
{
	MinMaxPaluu paluuarvo;

	// Generoidaan aseman lailliset siirrot.
	concurrency::concurrent_vector<Siirto> siirrot;
	annaLaillisetSiirrot(siirrot);

	// Rekursion kantatapaus 1: peli on loppu
	if (siirrot.size() == 0)
	{
		// *** TODO ***
		// tutki kumpi voitti ja palauta sen mukainen arvo (tasapeli 0).
		paluuarvo._evaluointiArvo = 0;
		return paluuarvo;
	}

	// Rekursion kantatapaus 2: katkaisusyvyydess‰
	if (syvyys == 0)
	{
		paluuarvo._evaluointiArvo = evaluoi();
		return paluuarvo;
	}

	// Rekursioaskel: kokeillaan jokaista laillista siirtoa s
	// (alustetaan paluuarvo huonoimmaksi mahdolliseksi).
	paluuarvo._evaluointiArvo = (_siirtovuoro == 0 ? -1000000 : 100000);
	for (auto s : siirrot)
	{
		// Seuraaja-asema (tehd‰‰n nykyisess‰ asemassa siirto s).
		Asema uusi_asema = *this;
		uusi_asema.paivitaAsema(&s);

		// Rekursiivinen kutsu.
		MinMaxPaluu arvo = uusi_asema.minimax(syvyys - 1);

		// Tutkitaan ollaan lˆydetty uusi paras siirto.
		if
			(
			(_siirtovuoro == 0 && arvo._evaluointiArvo > paluuarvo._evaluointiArvo) ||
				(_siirtovuoro == 1 && arvo._evaluointiArvo < paluuarvo._evaluointiArvo)
				)
		{
			// Lˆydettiin uusi paras siirto.
			paluuarvo._evaluointiArvo = arvo._evaluointiArvo;
			paluuarvo._parasSiirto = arvo._parasSiirto;
		}
	}
	return paluuarvo;
}


MinMaxPaluu Asema::maxi(int syvyys)
{
	concurrency::concurrent_vector<Siirto> lista;
	Ruutu kuninkaanRuutu;
	this->annaLaillisetSiirrot(lista);
	double arvo;
	Asema uusiAsema;
	Siirto _parasSiirto;
	MinMaxPaluu paluu;
	// Tarkasta onko matti tai patti, jos on niin poistu asap, matti -100000, patti 0
	if (lista.size() == 0) {
		//selvit‰ kuninkaan ruutu
		concurrency::parallel_for(size_t(0), size_t(8), [&](size_t i) {
			for (int j = 0; j < 8; j++) {
				if (this->_lauta[i][j] != NULL) {
					if (this->_lauta[i][j]->getKoodi() == VK) {
						kuninkaanRuutu.setSarake(i);
						kuninkaanRuutu.setRivi(j);
					}
				}
			}
		});
		//matti
		if (this->onkoRuutuUhattu(&kuninkaanRuutu, 1)) {
			paluu._evaluointiArvo = -1000000;
			return paluu;
		}
		//patti
		if (!this->onkoRuutuUhattu(&kuninkaanRuutu, 1)) {
			paluu._evaluointiArvo = 0;
			return paluu;
		}
	}
	// Jos ei ole matti tai patti niin k‰y pelipuuta l‰pi rekursiivisesti
	if (syvyys == 0) { // rekursion kanta
		paluu._evaluointiArvo = this->evaluoi();
		return 	paluu;
	}
	double maximi = -100000; // iso arvo jotta varmasti paranee
	for (auto s : lista) {
		uusiAsema = *this;
		uusiAsema.paivitaAsema(&s);
		arvo = uusiAsema.mini(syvyys - 1)._evaluointiArvo;
		if (arvo > maximi) {
			maximi = arvo;
			_parasSiirto = s;
		}
	}
	paluu._evaluointiArvo = maximi;
	paluu._parasSiirto = _parasSiirto;
	return paluu;
}


MinMaxPaluu Asema::mini(int syvyys)
{
	concurrency::concurrent_vector<Siirto> lista;
	Ruutu kuninkaanRuutu;
	this->annaLaillisetSiirrot(lista);
	double arvo;
	Asema uusiAsema;
	Siirto _parasSiirto;
	MinMaxPaluu paluu;
	// Tarkasta onko matti tai patti, jos on niin poistu asap, matti -100000, patti 0
	if (lista.size() == 0) {
		//selvit‰ kuninkaan ruutu
		concurrency::parallel_for(size_t(0), size_t(8), [&](size_t i) {
			for (int j = 0; j < 8; j++) {
				if (this->_lauta[i][j] != NULL) {
					if (this->_lauta[i][j]->getKoodi() == MK) {
						kuninkaanRuutu.setSarake(i);
						kuninkaanRuutu.setRivi(j);
					}
				}
			}
		});
		//matti
		if (this->onkoRuutuUhattu(&kuninkaanRuutu, 0)) {
			paluu._evaluointiArvo = 1000000;
			return paluu;
		}
		//patti
		if (!this->onkoRuutuUhattu(&kuninkaanRuutu, 0)) {
			paluu._evaluointiArvo = 0;
			return paluu;
		}
	}
	// Jos ei ole matti tai patti niin k‰y pelipuuta l‰pi rekursiivisesti
	if (syvyys == 0) { // rekursion kanta
		paluu._evaluointiArvo = this->evaluoi();
		//paluu._parasSiirto = MITƒ
		return 	paluu;
	}
	double minimi = 100000; // iso arvo jotta varmasti paranee
	for (auto s : lista) {
		uusiAsema = *this;
		uusiAsema.paivitaAsema(&s);
		arvo = uusiAsema.maxi(syvyys - 1)._evaluointiArvo;
		if (arvo < minimi) {
			minimi = arvo;
			_parasSiirto = s;
		}
	}
	paluu._evaluointiArvo = minimi;
	paluu._parasSiirto = _parasSiirto;
	return paluu;
}


bool Asema::onkoRuutuUhattu(Ruutu* ruutu, int vastustajanVari)
{
	concurrency::concurrent_vector<Siirto> vastustajaSiirrotLista;
	//V‰reitt‰in k‰yd‰‰n l‰pi kaikki ruudut ja niiss‰ olevan nappulan siirrot ker‰t‰‰n vastustajan siirtolistaan
	concurrency::parallel_for(size_t(0), size_t(8), [&](size_t i) {
		for (int j = 0; j < 8; j++) {
			if (this->_lauta[i][j] == NULL) {
				continue;
			}
			if (this->_lauta[i][j]->getVari() == vastustajanVari)
				this->_lauta[i][j]->annaSiirrot(vastustajaSiirrotLista, &Ruutu(i, j), this, vastustajanVari); // myˆh.sidonta
		}
	});
	// K‰yd‰‰n vastustajaSiirtoLista l‰pi ja jos sielt‰ lˆytyy tarkasteltava ruutu niin tiedet‰‰n sen olevan uhattu
	bool ruutuOk = true;
	for (auto s : vastustajaSiirrotLista)
	{
		if (ruutu->getSarake() == s.getLoppuruutu().getSarake() && ruutu->getRivi() == s.getLoppuruutu().getRivi()) {
			ruutuOk = false;
			break;
		}
	}
	return ruutuOk;
}


void Asema::huolehdiKuninkaanShakeista(concurrency::concurrent_vector<Siirto>& lista, int vari)
{
	// poistaa listasta siirrot jotka viev‰t oman kuninkaan shakkiin
	// k‰yd‰‰n saatua siirtolistaa l‰pi ja jos siell‰ oleva siirto asettaa kuninkaan shakkiin, 
	// niin siirto poistetaan listasta
	int kuninkaanX;
	int kuninkaanY;
	if (vari == 0) {
		concurrency::parallel_for(size_t(0), size_t(8), [&](size_t i) {
			for (int j = 0; j < 8; j++) {
				if (this->_lauta[i][j] == NULL)
					continue;
				if (this->_lauta[i][j]->getKoodi() == VK) {
					kuninkaanX = i;
					kuninkaanY = j;
					break;
				}
			}
		});
	}
	if (vari == 1) {
		concurrency::parallel_for(size_t(0), size_t(8), [&](size_t i) {
			for (int j = 0; j < 8; j++) {
				if (this->_lauta[i][j] == NULL)
					continue;
				if (this->_lauta[i][j]->getKoodi() == MK) {
					kuninkaanX = i;
					kuninkaanY = j;
					break;
				}
			}
		});
	}
	// Jotta ei jouduta perumaan oikeaan asemaan tehty‰ siirtoa
	Asema testiAsema;
	concurrency::concurrent_vector<Siirto> siivottuSiirrotLista;
	for (auto s : lista) {
		testiAsema = *this;
		testiAsema.paivitaAsema(&s);
		int x, y;

		// Kuninkaan siirto?
		if (s.onkoLyhytLinna())
		{
			x = 6;
			if (this->getSiirtovuoro() == 0)
				y = 0;
			else
				y = 7;
		}
		else if (s.onkoPitkaLinna())
		{
			x = 2;
			if (this->getSiirtovuoro() == 0)
				y = 0;
			else
				y = 7;
		}
		else
		{
			Nappula* siirtyva = this->_lauta[s.getAlkuruutu().getSarake()][s.getAlkuruutu().getRivi()];
			if (siirtyva->getKoodi() == VK || siirtyva->getKoodi() == MK)
			{
				x = s.getLoppuruutu().getSarake();
				y = s.getLoppuruutu().getRivi();
			}
			else
			{
				// Ei ole, kuninkaan sijainti sama kuin ennen siirron s kokeilua
				x = kuninkaanX;
				y = kuninkaanY;
			}
		}

		// huom !vari
		if (testiAsema.onkoRuutuUhattu(&Ruutu(x, y), !vari) == true) {
			siivottuSiirrotLista.push_back(s);
		}
	}
	lista = siivottuSiirrotLista;
}


void Asema::annaLinnoitusSiirrot(concurrency::concurrent_vector<Siirto>& lista, int vari)
{
	//// Linnoituksien huomioiminen
	//// 1. Kuningas ei saa olla liikkunut
	//// 2. Torni ei saa olla liikkunut
	//// 3. Kuningas ei saa olla shakattuna
	//// 4. Ruutujen pit‰‰ olla tyhj‰t
	//// 5. Ruudut eiv‰t saa olla uhattuja
	if (vari == 0) {
		//valkean lyhyt linna
		if (!this->getOnkoValkeaKuningasLiikkunut() && !this->getOnkoValkeaKTliikkunut()
			&& this->onkoRuutuUhattu(&Ruutu(4, 0), !vari)
			&& this->onkoRuutuUhattu(&Ruutu(5, 0), !vari) && this->onkoRuutuUhattu(&Ruutu(6, 0), !vari)
			&& this->_lauta[5][0] == NULL && this->_lauta[6][0] == NULL) {
			//p‰ivitet‰‰n listaan lyhytlinna
			lista.push_back(Siirto(true, false)); // lis‰t‰‰n listaan lyhyt linna
		}
		//valkean pitk‰ linna
		if (!this->getOnkoValkeaKuningasLiikkunut() && !this->getOnkoValkeaDTliikkunut()
			&& this->onkoRuutuUhattu(&Ruutu(4, 0), !vari)
			&& this->onkoRuutuUhattu(&Ruutu(3, 0), !vari) && this->onkoRuutuUhattu(&Ruutu(3, 0), !vari)
			&& this->_lauta[3][0] == NULL && this->_lauta[2][0] == NULL) {
			//p‰ivitet‰‰n listaan lyhytlinna
			lista.push_back(Siirto(false, true)); // lis‰t‰‰n listaan lyhyt linna
		}
	}
	if (vari == 1) {
		//mustan lyhyt linna
		if (!this->getOnkoMustaKuningasLiikkunut() && !this->getOnkoMustaKTliikkunut()
			&& this->onkoRuutuUhattu(&Ruutu(4, 7), !vari)
			&& this->onkoRuutuUhattu(&Ruutu(5, 7), !vari) && this->onkoRuutuUhattu(&Ruutu(6, 7), !vari)
			&& this->_lauta[5][7] == NULL && this->_lauta[6][7] == NULL) {
			//p‰ivitet‰‰n listaan lyhytlinna
			lista.push_back(Siirto(true, false)); // lis‰t‰‰n listaan lyhyt linna
		}
		//mustan pitk‰ linna
		if (!this->getOnkoMustaKuningasLiikkunut() && !this->getOnkoMustaDTliikkunut()
			&& this->onkoRuutuUhattu(&Ruutu(4, 7), !vari)
			&& this->onkoRuutuUhattu(&Ruutu(3, 7), !vari) && this->onkoRuutuUhattu(&Ruutu(3, 7), !vari)
			&& this->_lauta[3][7] == NULL && this->_lauta[2][7] == NULL) {
			//p‰ivitet‰‰n listaan lyhytlinna
			lista.push_back(Siirto(false, true)); // lis‰t‰‰n listaan lyhyt linna
		}
	}
}


void Asema::annaLaillisetSiirrot(concurrency::concurrent_vector<Siirto>& lista) {
	int vari = this->getSiirtovuoro();

	//for (int i = 0; i < 8; i++) {
	concurrency::parallel_for(size_t(0), size_t(8), [&](size_t i){
		for (int j = 0; j < 8; j++) {
			//Ei kysele tyhjilt‰ ruuduilta nappulan nime‰
			if (this->_lauta[i][j] == NULL) {
				continue;
			}
			if (this->_lauta[i][j]->getVari() != vari) {
				continue;
			}
			this->_lauta[i][j]->annaSiirrot(lista, &Ruutu(i, j), this, vari); // myˆh‰inen sidonta!
		}
	});
	this->annaLinnoitusSiirrot(lista, vari);
	this->huolehdiKuninkaanShakeista(lista, vari);
}





MinMaxPaluu Asema::MaxAB(int syvyys, MinMaxPaluu alpha, MinMaxPaluu beta) {

	MinMaxPaluu paluu;
	concurrency::concurrent_vector<Siirto> siirrot;
	annaLaillisetSiirrot(siirrot);

	if (siirrot.size() == 0) {
		//paluu._evaluointiArvo = LoppuTulos();
		//return paluu;
	}

	if (syvyys <= 0) {
		paluu._evaluointiArvo = evaluoi();
		return paluu;
	}

	paluu._evaluointiArvo = -INFINITY;

	for (Siirto s : siirrot) {
		Asema uusi = *this;
		uusi.paivitaAsema(&s);
		MinMaxPaluu arvo = uusi.MinAB(syvyys - 1, alpha, beta);
		if (arvo._evaluointiArvo > paluu._evaluointiArvo) { paluu._parasSiirto = s; paluu._evaluointiArvo = arvo._evaluointiArvo; }
		if (arvo._evaluointiArvo >= beta._evaluointiArvo) { return beta; }
		if (arvo._evaluointiArvo > alpha._evaluointiArvo) { alpha._parasSiirto = s; alpha._evaluointiArvo = arvo._evaluointiArvo; }
	}
	return alpha;
}

MinMaxPaluu Asema::MinAB(int syvyys, MinMaxPaluu alpha, MinMaxPaluu beta) {

	MinMaxPaluu paluu;
	concurrency::concurrent_vector<Siirto> siirrot;
	annaLaillisetSiirrot(siirrot);


	if (siirrot.size() == 0) {
		//paluu._evaluointiArvo = LoppuTulos();
		//return paluu;
	}

	if (syvyys <= 0) {
		paluu._evaluointiArvo = evaluoi();
		return paluu;
	}

	paluu._evaluointiArvo = +INFINITY;

	for (Siirto s : siirrot) {
		Asema uusi = *this;
		uusi.paivitaAsema(&s);
		MinMaxPaluu arvo = uusi.MaxAB(syvyys - 1, alpha, beta);
		if (arvo._evaluointiArvo < paluu._evaluointiArvo) { paluu._parasSiirto = s; paluu._evaluointiArvo = arvo._evaluointiArvo; }
		if (arvo._evaluointiArvo <= alpha._evaluointiArvo) { return alpha; }
		if (arvo._evaluointiArvo < beta._evaluointiArvo) { beta._parasSiirto = s; beta._evaluointiArvo = arvo._evaluointiArvo; }
	}
	return beta;
}