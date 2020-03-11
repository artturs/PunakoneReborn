#include <Windows.h>
#include <iostream>
#include <string>
#include <fcntl.h>
#include <io.h>
#include <iostream>
#include "kayttoliittyma.h"

using namespace std;


Kayttoliittyma* Kayttoliittyma::instance = 0;


Kayttoliittyma* Kayttoliittyma::getInstance()
{
	if (instance == 0)
		instance = new Kayttoliittyma();
	return instance;
}


void Kayttoliittyma::piirraLauta()
{

	//Saa unicode shakkinappulat toimimaan printf kanssa:
	SetConsoleOutputCP(65001);
	//printf(q);
	//char q[] = "King: \xE2\x99\x94.\n";

	//Saa unicode shakkinappulat toimimaan cout:n kanssa:
	_setmode(_fileno(stdout), _O_U16TEXT);

	/*
		Kaksinkertainen for silmukka joka käy asema-olion laudan läpi ja jos
		siinä on nappula olio, niin kysytään sen nimi
		ja tulostetaan se muussa tapauksessa tulostetaan 2 tyhjää välilyöntiä.
		Parillisuuteen perustuen värjätään jokatoisen "ruudun" taustaväri
	*/
	for (int i = 7; i >= 0; i--) {
		for (int j = 0; j < 8; j++) {
			if (j == 0 && i == 7) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | BACKGROUND_RED |
					BACKGROUND_GREEN | BACKGROUND_BLUE);
				wcout << 8;
			}
			if (j == 0 && i == 6) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | BACKGROUND_RED |
					BACKGROUND_GREEN | BACKGROUND_BLUE);
				wcout << 7;
			}
			if (j == 0 && i == 5) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | BACKGROUND_RED |
					BACKGROUND_GREEN | BACKGROUND_BLUE);
				wcout << 6;
			}
			if (j == 0 && i == 4) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | BACKGROUND_RED |
					BACKGROUND_GREEN | BACKGROUND_BLUE);
				wcout << 5;
			}
			if (j == 0 && i == 3) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | BACKGROUND_RED |
					BACKGROUND_GREEN | BACKGROUND_BLUE);
				wcout << 4;
			}
			if (j == 0 && i == 2) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | BACKGROUND_RED |
					BACKGROUND_GREEN | BACKGROUND_BLUE);
				wcout << 3;
			}
			if (j == 0 && i == 1) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | BACKGROUND_RED |
					BACKGROUND_GREEN | BACKGROUND_BLUE);
				wcout << 2;
			}
			if (j == 0 && i == 0) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | BACKGROUND_RED |
					BACKGROUND_GREEN | BACKGROUND_BLUE);
				wcout << 1;
			}
			if (i % 2 != 0) {
				if (j % 2 == 0)
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | BACKGROUND_RED |
						BACKGROUND_GREEN | BACKGROUND_BLUE);
				else
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN | BACKGROUND_RED);
			}
			else {
				if (j % 2 != 0)
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | BACKGROUND_RED |
						BACKGROUND_GREEN | BACKGROUND_BLUE);
				else
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN | BACKGROUND_RED);
			}

			/*wcout << "|";*/
			if (_asema->_lauta[j][i] != NULL) {
				wcout << " " << _asema->_lauta[j][i]->getUnicode() << " ";
			}
			else {
				wcout << "   ";
			}
			/*if (j == 7)
				wcout << "|";*/
		}
		wcout << "\n";
	}
	wcout << "  " << "a " << " b " << " c " << " d " << " e " << " f " << " g " << " h \n";
}


/*
	Aliohjelma tarkistaa että käyttäjän antama syöte siirroksi on
	muodollisesti korrekti (ei tarkista aseman laillisuutta)
	Ottaa irti myös nappulan kirjaimen (K/D/L/R/T), tarkistaa että kirjain korrekti
*/
Siirto Kayttoliittyma::annaVastustajanSiirto()
{
	int lahtoX;
	int lahtoY;
	int tuloX;
	int tuloY;
	std::wstring siirtoString;
	std::wstring siirtynytNappulaString;

	do
	{
		wcout << "Anna siirtosi esim. (esim. Rg1-f3, linnoitus 0-0 tai 0-0-0)\n";
		wcin >> siirtoString;
		if (siirtoString == L"0-0" || siirtoString == L"0-0-0") {
			if (siirtoString == L"0-0") {
				return Siirto(true, false);
			}
			if (siirtoString == L"0-0-0") {
				return Siirto(false, true);
			}
		}
		else if (siirtoString.length() == 6) {
			siirtynytNappulaString = siirtoString[0];
			siirtoString.erase(0, 1);
		}
		else {
			siirtynytNappulaString = L"s";
		}
		lahtoX = siirtoString[0] - 'a';
		lahtoY = siirtoString[1] - '1';
		tuloX = siirtoString[3] - 'a';
		tuloY = siirtoString[4] - '1';

		if (((lahtoX < 0 || lahtoX >7) || (lahtoY < 0 || lahtoY > 7)) || ((tuloX < 0 || tuloX >7) || (tuloY < 0 || tuloY > 7)))
			wcout << "Siirron täytyy olla muotoa esim. Rf1-f3,\n aakkoset väliltä a-h\n numerot väliltä 1-8,\n Nappula on (K,k),(D,d),(T,t),(R,r),(L,l)\n sotilas jätetään merkitsemättä\n";
	} while (((lahtoX < 0 || lahtoX >7) || (lahtoY < 0 || lahtoY > 7)) || ((tuloX < 0 || tuloX >7) || (tuloY < 0 || tuloY > 7)));

	Ruutu lahtoRuutu(lahtoX, lahtoY);
	Ruutu tuloRuutu(tuloX, tuloY);
	Siirto siirto(lahtoRuutu, tuloRuutu);
	//katsotaan onko kyseessä sotilaan korotus
	std::wstring korotettuNappula;
	if (siirtynytNappulaString == L"s" && (tuloY == 0 || tuloY == 7)) {
		std::wcout << "Miksi nappulaksi haluat korottaa? (esim. D)\n";
		std::wcin >> korotettuNappula;
		if (tuloY == 7) {
			if (korotettuNappula == L"D" || korotettuNappula == L"d") {
				siirto._miksikorotetaan = _asema->vd;
			}
			if (korotettuNappula == L"T" || korotettuNappula == L"t") {
				siirto._miksikorotetaan = _asema->vt;
			}
			if (korotettuNappula == L"R" || korotettuNappula == L"r") {
				siirto._miksikorotetaan = _asema->vr;
			}
			if (korotettuNappula == L"L" || korotettuNappula == L"l") {
				siirto._miksikorotetaan = _asema->vl;
			}
		}

		if (tuloY == 0) {
			if (korotettuNappula == L"D" || korotettuNappula == L"d") {
				siirto._miksikorotetaan = _asema->md;
			}
			if (korotettuNappula == L"T" || korotettuNappula == L"t") {
				siirto._miksikorotetaan = _asema->mt;
			}
			if (korotettuNappula == L"R" || korotettuNappula == L"r") {
				siirto._miksikorotetaan = _asema->mr;
			}
			if (korotettuNappula == L"L" || korotettuNappula == L"l") {
				siirto._miksikorotetaan = _asema->ml;
			}
		}
	}

	return siirto;

}


int Kayttoliittyma::kysyVastustajanVari()
{
	int vari;
	wcout << "Haluatko pelata valkeilla (0) vai mustilla (1)?";
	cin >> vari;
	return vari;
}
