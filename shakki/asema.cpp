#include <iostream>
#include "asema.h"
#include "minMaxPaluu.h"
#include "nappula.h"
#include "ruutu.h"
using namespace std;

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
	{
		for (int j = 0; j < 8; j++)
		{
			_lauta[i][j] = NULL;
		}
	}
	//std::cout << _lauta[10][10];
	// Asetetaan alkuaseman mukaisesti nappulat ruuduille
	/*_lauta[0][1] = vs;
	_lauta[1][1] = vs;
	_lauta[2][1] = vs;
	_lauta[3][1] = vs;
	_lauta[4][1] = vs;
	_lauta[5][1] = vs;
	_lauta[6][1] = vs;
	_lauta[7][1] = vs;*/
	_lauta[0][0] = vt;
	_lauta[1][0] = vr;
	_lauta[2][0] = vl;
	_lauta[3][0] = vd;
	_lauta[4][0] = vk;
	//_lauta[5][0] = vl;
	//_lauta[6][0] = vr;
	_lauta[7][0] = vt;

	_lauta[0][6] = ms;
	_lauta[1][6] = ms;
	_lauta[2][6] = ms;
	_lauta[3][6] = ms;
	_lauta[4][6] = ms;
	_lauta[5][6] = ms;
	_lauta[6][6] = ms;
	_lauta[7][6] = ms;
	_lauta[0][7] = mt;
	_lauta[1][7] = mr;
	_lauta[2][7] = ml;
	//_lauta[3][7] = md;
	//_lauta[5][1] = md;
	_lauta[4][7] = mk;
	_lauta[5][7] = ml;
	_lauta[6][7] = mr;
	_lauta[7][7] = mt;
	_siirtovuoro = 0;
	
}
void Asema::paivitaAsema(Siirto *siirto)
{
	int alkuX, alkuY, loppuX, loppuY;
	alkuX = siirto->getAlkuruutu().getSarake();
	alkuY = siirto->getAlkuruutu().getRivi();
	loppuX = siirto->getLoppuruutu().getSarake();
	loppuY = siirto->getLoppuruutu().getRivi();

	

	// Kaksoisaskel-lippu on oletusarvoisesti pois p‰‰lt‰.
	// Asetetaan myˆhemmin, jos tarvii.


	//Tarkastetaan on siirto lyhyt linna

	if (siirto->onkoLyhytLinna()) {
		if(_siirtovuoro==0){
			_lauta[4][0] = NULL;
			_lauta[6][0] = vk;
			_lauta[7][0] = NULL;
			_lauta[5][0] = vt;
		}
		if(_siirtovuoro==1){
			_lauta[4][7] = NULL;
			_lauta[6][7] = vk;
			_lauta[7][7] = NULL;
			_lauta[5][7] = vt;
		}
	}
	else if(siirto->onkoPitkaLinna()){
		if (_siirtovuoro == 0) {
			_lauta[4][0] = NULL;
			_lauta[2][0] = vk;
			_lauta[0][0] = NULL;
			_lauta[3][0] = vt;
		}
		if (_siirtovuoro == 1) {
			_lauta[4][7] = NULL;
			_lauta[2][7] = vk;
			_lauta[0][7] = NULL;
			_lauta[3][7] = vt;
		}
	}
	else { // Kaikki muut siirrot

		//Ottaa siirron alkuruudussa olleen nappulan talteen		
		Nappula* nappula = _lauta[alkuX][alkuY];

		//Laittaa talteen otetun nappulan uuteen ruutuun

		
		// Tarkistetaan oliko sotilaan kaksoisaskel
		//t‰ss‰ virhe, tai lauseitten takia
		if (_lauta[alkuX][alkuY]->getKoodi() == MS && (alkuY - loppuY) == 2 || _lauta[alkuX][alkuY]->getKoodi() == VS &&  (loppuY - alkuY) == 2)
		{	//_lauta[alkuX][alkuY]->getKoodi() == MS || _lauta[alkuX][alkuY]->getKoodi() == VS && 
			// (asetetaan kaksoisaskel-lippu)
			kaksoisaskelSarakkeella = alkuX;
			std::wcout << "\n kaksoisaskelflag\n";
		}


		// Ohestalyˆnti on tyhj‰‰n ruutuun. Vieress‰ oleva (sotilas) poistetaan.
		
		if (nappula->getKoodi() == VS && _lauta[loppuX][alkuY] != NULL && _lauta[loppuX][loppuY] == NULL && alkuX != loppuX)
		{
			if (_lauta[loppuX][alkuY]->getKoodi() == MS) {
				std::wcout << "\n ohestalyˆnti\n";
				_lauta[loppuX][alkuY] = NULL;
			}
		}
		if (nappula->getKoodi() == MS || _lauta[loppuX][alkuY] != NULL && _lauta[loppuX][loppuY] == NULL && alkuX != loppuX)
		{
			
			if (_lauta[loppuX][alkuY]->getKoodi() == VS) {
				std::wcout << "\n ohestalyˆnti\n";
				_lauta[loppuX][alkuY] = NULL;
			}
		}
		//// Katsotaan jos nappula on sotilas ja rivi on p‰‰tyrivi niin ei vaihdeta nappulaa 
		if (nappula->getKoodi() == MS || nappula->getKoodi() == VS) {
			if (nappula->getKoodi() == MS && loppuY == 0) {

			}
			if (nappula->getKoodi() == VS && loppuY == 7) {

			}

		}
		

		
		////eli alkuruutuun laitetaan null ja loppuruudussa on jo kliittym‰n laittama nappula MIIKKA, ei taida minmaxin kanssa hehkua?
		_lauta[loppuX][loppuY] = nappula;
		_lauta[alkuX][alkuY] = NULL;
		
		//
		////muissa tapauksissa alkuruutuun null ja loppuruutuun sama alkuruudusta l‰htenyt nappula

		// katsotaan jos liikkunut nappula on kuningas niin muutetaan onkoKuningasLiikkunut arvo (molemmille v‰reille)
		if (nappula->getKoodi() == VK )
		{
			_onkoValkeaKuningasLiikkunut = 1;
		}
		if (nappula->getKoodi() == MK)
		{
			_onkoMustaKuningasLiikkunut = 1;
		}
		// katsotaan jos liikkunut nappula on torni niin muutetaan onkoTorniLiikkunut arvo (molemmille v‰reille ja molemmille torneille)
		if (alkuX == 7 && nappula->getKoodi() == VT)
		{
			_onkoValkeaKTliikkunut = 1;
		}
		if (alkuX == 0 && nappula->getKoodi() == VT)
		{
			_onkoValkeaDTliikkunut = 1;
		}
		if (alkuX == 7 && nappula->getKoodi() == MT)
		{
			_onkoMustaKTliikkunut = 1;
		}
		if (alkuX == 0 && nappula->getKoodi() == MT)
		{
			_onkoValkeaDTliikkunut = 1;
		}
		
	}
	//p‰ivitet‰‰n _siirtovuoro
	if (_siirtovuoro = 0) {
		_siirtovuoro = 1;
	}
	if (_siirtovuoro = 1) {
		_siirtovuoro = 0;
	}
	
}



int Asema::getSiirtovuoro()
{
	return _siirtovuoro;
}


void Asema::setSiirtovuoro(int vuoro)
{

}


bool Asema::getOnkoValkeaKuningasLiikkunut()
{
	return false;
}


bool Asema::getOnkoMustaKuningasLiikkunut()
{
	return false;
}


bool Asema::getOnkoValkeaDTliikkunut()
{
	return _onkoValkeaDTliikkunut;
}


bool Asema::getOnkoValkeaKTliikkunut()
{
	return _onkoValkeaKTliikkunut;
}


bool Asema::getOnkoMustaDTliikkunut()
{
	return false;
}


bool Asema::getOnkoMustaKTliikkunut()
{
	return false;
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
	float evaluaatio = 0;
	for (int x = 0; x < 8; x++)
	{
		for (int y = 0; y < 8; y++)
		{
			if (this->_lauta[x][y] == NULL) {
				continue;
			}
			if (this->_lauta[x][y]->getKoodi() == VS) {
				evaluaatio++;
			}
			if (this->_lauta[x][y]->getKoodi() == MS) {
				evaluaatio--;
			}
			if (this->_lauta[x][y]->getKoodi() == VR) {
				evaluaatio += 3;
			}
			if (this->_lauta[x][y]->getKoodi() == MR) {
				evaluaatio -= 3;
			}
			if (this->_lauta[x][y]->getKoodi() == VL) {
				evaluaatio += 3.25;
			}
			if (this->_lauta[x][y]->getKoodi() == ML) {
				evaluaatio -= 3.25;
			}
			if (this->_lauta[x][y]->getKoodi() == VT) {
				evaluaatio += 5;
			}
			if (this->_lauta[x][y]->getKoodi() == MT) {
				evaluaatio -= 5;
			}
			if (this->_lauta[x][y]->getKoodi() == VD) {
				evaluaatio += 9;
			}
			if (this->_lauta[x][y]->getKoodi() == MD) {
				evaluaatio -= 9;
			}
		}
	}
	return evaluaatio;

	
}


double Asema::laskeNappuloidenArvo(int vari)
{
	
	return 0;

}


bool Asema::onkoAvausTaiKeskipeli(int vari)
{
	return 0;
	// Jos upseereita 3 tai v‰hemm‰n on loppupeli
	// mutta jos daami laudalla on loppueli vasta kun kuin vain daami j‰ljell‰

	//Jos vari on 0 eli valkoiset
	//niin on keskipeli jos mustalla upseereita yli 2 tai jos daami+1


}


double Asema::nappuloitaKeskella(int vari)
{
	return 0;

	//sotilaat ydinkeskustassa + 0.25/napa
	//ratsut ydinkeskustassa + 0.25/napa
	//sotilaat laitakeskustassa + 0.11/napa
	//ratsut laitakeskustassa + 0.11/napa

	//valkeille ydinkeskusta



	//valkeille laitakeskusta



	//mustille ydinkeskusta

	//mustille laitakeskusta

}


double Asema::linjat(int vari)
{
	return 0;

	//valkoiset

	//mustat

}


// https://chessprogramming.wikispaces.com/Minimax MinMax-algoritmin pseudokoodi (lis‰sin parametrina aseman)
//int maxi(int depth, asema a) 
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
	MinMaxPaluu paluuarvo;

	// Generoidaan aseman lailliset siirrot.
	std::list<Siirto> siirrot;
	annaLaillisetSiirrot(siirrot);

	// Rekursion kantatapaus 1: peli on loppu
	if (siirrot.size() == 0)
	{
		// *** TODO ***
		//
		// Laillisia siirtoja ei ole. Jos siirtovuoroisen pelaajan
		// kuningas on uhattu, on h‰n h‰vinnyt (matti). Jos kuningas
		// ei ole uhattu, on peli tasapeli (patti).
		//
		// Aseta sopiva paluuarvo (valkean voitto, mustan voitto, tasapeli),
		// eli esim. 1, -1, tai 0.
		//
		paluuarvo._evaluointiArvo = 0;
		return paluuarvo;
	}

	// Rekursion kantatapaus 2: katkaisusyvyydess‰
	if (syvyys == 0)
	{
		// Pyydet‰‰n evaluointifunktion arvio nykyisest‰ asemasta.
		// Evaluointifunktion arvojen pit‰‰ olla ‰‰rip‰iden (voitto, h‰viˆ)
		// v‰lilt‰, ts. esim. ]0,1[.
		//
		paluuarvo._evaluointiArvo = evaluoi();
		return paluuarvo;
	}

	// Rekursioaskel: kokeillaan jokaista laillista siirtoa s.
	// Alustetaan paluuarvo huonoimmaksi mahdolliseksi siirto-
	// vuoroisen pelaajan kannalta, jotta parempi siirto varmasti
	// lˆytyy.
	//
	paluuarvo._evaluointiArvo = (_siirtovuoro == 0 ? -1000 : 1000);
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

	// Palautetaan paras lˆydetty siirto/minimax-arvo
	return paluuarvo;
}


MinMaxPaluu Asema::maxi(int syvyys)
{
	MinMaxPaluu paluu;
	return paluu;
}


MinMaxPaluu Asema::mini(int syvyys)
{
	MinMaxPaluu paluu;
	return paluu;
}


bool Asema::onkoRuutuUhattu(Ruutu* ruutu, int vastustajanVari)
{
	bool eihuolta = true;
	list<Siirto> vastustajanSiirrot;
	//ker‰t‰‰n vihulaisen siirrot
	for (int x = 0; x < 8; x++) 
	{
		for (int y = 0; y < 8; y++) 
		{
			if (this->_lauta[x][y] == NULL) {
				continue;
			}
			if (this->_lauta[x][y]->getVari() == vastustajanVari) {
				this->_lauta[x][y]->annaSiirrot(vastustajanSiirrot, &Ruutu(x, y), this, vastustajanVari);
			}
		}
	}

	for (auto volvo : vastustajanSiirrot)
	{
		//katsotaan voiko vihulaisen nappula menn‰ ruutuun
		if (ruutu->getSarake() == volvo.getLoppuruutu().getSarake() && ruutu->getRivi() == volvo.getLoppuruutu().getRivi())
		{
			eihuolta = false;
			break;
		}
	}


	return eihuolta;
}


void Asema::huolehdiKuninkaanShakeista(std::list<Siirto>& lista, int vari)
{
	int kuningasX, kuningasY;
	int kuninkaanVari;
	list <Siirto> pareLista;
	Asema tmpAs;

	//tarkistetaan kumpaa kuningasta t‰ytyy etsi‰

	if (vari == 0) {kuninkaanVari = VK;}
	else { kuninkaanVari = MK; }

	//etsit‰‰n edell‰ mainittu kuningas
	for (int x = 0; x < 8; x++) {
		for (int y = 0; y < 8; y++) {

			if (this->_lauta[x][y] == NULL) {
				continue;
			}
			if (this->_lauta[x][y]->getKoodi() == kuninkaanVari) {
				kuningasX = x;
				kuningasY = y;
				break;
			}
			
		}
	}

	for (auto fiat : lista) {
		int x, y;
		tmpAs = *this;
		tmpAs.paivitaAsema(&fiat);
		//Katsotaan onko siirretty nappula kuningas
		Nappula* siirretty;
		siirretty = this->_lauta[fiat.getAlkuruutu().getSarake()][fiat.getAlkuruutu().getRivi()];


		if (fiat.onkoLyhytLinna()) 
		{
			x = 6;
			if (this->getSiirtovuoro() == 0)
				y = 0;
			else
				y = 7;
		}
		else if (fiat.onkoPitkaLinna())
		{
			x = 2;
			if (this->getSiirtovuoro() == 0)
				y = 0;
			else
				y = 7;
		}
		else
		{
			if (siirretty->getKoodi() == MK || siirretty->getKoodi() == VK) {
				x = fiat.getLoppuruutu().getSarake();
				y = fiat.getLoppuruutu().getRivi();

			}
			else {
				x = kuningasX;
				y = kuningasY;
			}
		}
		if (tmpAs.onkoRuutuUhattu(&Ruutu(x, y), !vari) == true) {
			pareLista.push_back(fiat);
		}
	}
	lista = pareLista;
	
}

void Asema::annaLinnoitusSiirrot(std::list<Siirto>& lista, int vari) {

	//valkoinen
	if (vari == 0) 
	{
		//lyhyt linna
		if (this->getOnkoValkeaKuningasLiikkunut() == false && this->getOnkoValkeaKTliikkunut() == false) 
		{
			if (this->_lauta[5][0] == NULL && this->_lauta[6][0] == NULL) {
				if (this->onkoRuutuUhattu(&Ruutu(4, 0), !vari) && this->onkoRuutuUhattu(&Ruutu(5, 0), !vari) 
					&& this->onkoRuutuUhattu(&Ruutu(6, 0), !vari))
				{
					lista.push_back(Siirto(true, false, true)); // lis‰t‰‰n listaan lyhyt linna
				}
			}
		}
		//pitk‰ linna
		if (this->getOnkoValkeaKuningasLiikkunut() == false && this->getOnkoValkeaDTliikkunut() == false)
		{
			if (this->_lauta[4][0] == NULL && this->_lauta[3][0] == NULL) {
				if (this->onkoRuutuUhattu(&Ruutu(4, 0), !vari) && this->onkoRuutuUhattu(&Ruutu(3, 0), !vari))	
				{
					lista.push_back(Siirto(false, true, true)); // lis‰t‰‰n listaan pitk‰ linna
				}
			}
		}
	}
	//musta
	if(vari == 1)
	{
		//lyhyt linna
		if (this->getOnkoValkeaKuningasLiikkunut() == false && this->getOnkoValkeaKTliikkunut() == false)
		{
			if (this->_lauta[5][7] == NULL && this->_lauta[6][7] == NULL) {
				if (this->onkoRuutuUhattu(&Ruutu(4, 7), !vari) && this->onkoRuutuUhattu(&Ruutu(5, 7), !vari)
					&& this->onkoRuutuUhattu(&Ruutu(6, 7), !vari))
				{
					lista.push_back(Siirto(true, false, true)); // lis‰t‰‰n listaan lyhyt linna
				}
			}
		}
		//pitk‰ linna
		if (this->getOnkoValkeaKuningasLiikkunut() == false && this->getOnkoValkeaDTliikkunut() == false)
		{
			if (this->_lauta[4][7] == NULL && this->_lauta[3][7] == NULL) {
				if (this->onkoRuutuUhattu(&Ruutu(4, 7), !vari) && this->onkoRuutuUhattu(&Ruutu(3, 7), !vari))
				{
					lista.push_back(Siirto(false, true, true)); // lis‰t‰‰n listaan pitk‰ linna
				}
			}
		}
	}


}

void Asema::annaLaillisetSiirrot(std::list<Siirto>& lista) {
	
	
	int vari = this->getSiirtovuoro();
	

	//kaikki mahd siirrot
	annaLinnoitusSiirrot(lista, vari);
	for (int x = 0; x < 8; x++) {
		for (int y = 0; y < 8; y++) {
			
			if (this->_lauta[x][y] == NULL) {
				
				continue;
			}
			if (this->_lauta[x][y]->getVari() != vari) {
				
				continue;
			}
			this->_lauta[x][y]->annaSiirrot(lista, &Ruutu(x, y), this, vari);
			
		}
	}
	

}
