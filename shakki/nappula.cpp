#include <list>
#include <string>
#include <iostream>
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
	int y = ruutu->getRivi();
	int x = ruutu->getSarake();
	
	int nappulanvari = vari;
		//asema->_lauta[x][y]->getVari();
	// toisenvari siis loppuruudussa olevan nappulan väri
	int toisenvari;
	int xt, yt;
	xt = x + 1;
	yt = y + 1;

	//siirrot oikealle
	for (xt = x + 1; xt < 99; xt++) {
		if (xt < 0 || xt > 7) {
			//menee yli
			break;
		}
		// ei mitääm tässä, tähän voi mennä
		if (asema->_lauta[xt][y] == NULL) {
			lista.push_back(Siirto(*ruutu, Ruutu(xt, y)));
		}
		//tässä nappula, katsotaan voiko syyä
		if (asema->_lauta[xt][y] != NULL) {
			toisenvari = asema->_lauta[xt][y]->getVari();
			//oma, ei voi syyä
			if (nappulanvari == toisenvari) {
				break;
			}
			//ei oma, voi syyä
			if (nappulanvari != toisenvari) {
				lista.push_back(Siirto(*ruutu, Ruutu(xt, y)));
				break;
			}

		}

	}

	//siirrot vasemmalle
	for (xt = x - 1, yt = y + 1; xt < 99; xt--) {
		if (xt < 0 || xt > 7) {
			//menee yli
			break;
		}
		// ei mitääm tässä, tähän voi mennä
		if (asema->_lauta[xt][y] == NULL) {
			lista.push_back(Siirto(*ruutu, Ruutu(xt, y)));
		}
		//tässä nappula, katsotaan voiko syyä
		if (asema->_lauta[xt][yt] != NULL) {
			toisenvari = asema->_lauta[xt][y]->getVari();
			//oma, ei voi syyä
			if (nappulanvari == toisenvari) {
				break;
			}
			//ei oma, voi syyä
			if (nappulanvari != toisenvari) {
				lista.push_back(Siirto(*ruutu, Ruutu(xt, y)));
				break;
			}

		}

	}

	//siirrot ylös
	for (yt = y + 1; xt < 99; yt++) {
		if (yt < 0 || yt > 7) {
			//menee yli
			break;
		}
		// ei mitääm tässä, tähän voi mennä
		if (asema->_lauta[x][yt] == NULL) {
			lista.push_back(Siirto(*ruutu, Ruutu(x, yt)));
		}
		//tässä nappula, katsotaan voiko syyä
		if (asema->_lauta[x][yt] != NULL) {
			toisenvari = asema->_lauta[x][yt]->getVari();
			//oma, ei voi syyä
			if (nappulanvari == toisenvari) {
				break;
			}
			//ei oma, voi syyä
			if (nappulanvari != toisenvari) {
				lista.push_back(Siirto(*ruutu, Ruutu(x, yt)));
				break;
			}

		}

	}

	//siirrot alas
	for (yt = y - 1; xt < 99; yt--) {
		if (xt < 0 || xt > 7 || yt < 0 || yt > 7) {
			//menee yli
			break;
		}
		// ei mitääm tässä, tähän voi mennä
		if (asema->_lauta[x][yt] == NULL) {
			lista.push_back(Siirto(*ruutu, Ruutu(x, yt)));
		}
		//tässä nappula, katsotaan voiko syyä
		if (asema->_lauta[x][yt] != NULL) {
			toisenvari = asema->_lauta[x][yt]->getVari();
			//oma, ei voi syyä
			if (nappulanvari == toisenvari) {
				break;
			}
			//ei oma, voi syyä
			if (nappulanvari != toisenvari) {
				lista.push_back(Siirto(*ruutu, Ruutu(x, yt)));
				break;
			}

		}

	}

}


void Ratsu::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	int y = ruutu->getRivi();
	int x = ruutu->getSarake();
	int nappulanvari = vari;
		//asema->_lauta[x][y]->getVari();
	int toisenvari;

	//määritetään miten ratsun koordinaatit voivat muuttua
	const int koord_deltat[8][2] =
	{
		{-1,2},{-1,-2},{1,2},{1,-2},{-2,1},{-2,-1},{2,1},{2,-1}
	};
	//käydään kaikki määritetyt vaihtoehdot läpi
	for (int d = 0; d < 8; d++) {
		int dx = koord_deltat[d][0];
		int dy = koord_deltat[0][d];

		int tmpX = x + dx;
		int tmpY = y + dy;

		if (tmpY > 7 || tmpY < 0 || tmpX > 7 || tmpX < 0) {
			//ei kelpuuteta
			continue;
		}
		if (asema->_lauta[tmpX][tmpY] == NULL){
			//nice, tähän voi mennä
			lista.push_back(Siirto(*ruutu, Ruutu(tmpX, tmpY)));

		}
		else {
			toisenvari = asema->_lauta[tmpX][tmpY]->getVari();
			//oma, ei voi syyä
			if (nappulanvari == toisenvari) {
				continue;
			}
			//ei oma, voi syyä
			if (nappulanvari != toisenvari) {
				lista.push_back(Siirto(*ruutu, Ruutu(tmpX, tmpY)));
				continue;
			}

		}
	}

}


void Lahetti::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	
	int x = ruutu->getRivi();
	int y = ruutu->getSarake();

	
	wcout << "\n x:" << x << " y:" << y;
	int nappulanvari = vari;

	// toisenvari siis loppuruudussa olevan nappulan väri
	int toisenvari;
	int xt, yt;
	xt = x + 1;
	yt = y + 1;


	//siirrot yläoikea
	

	for (xt = x + 1, yt = y + 1; xt < 99; xt++, yt++) {
		if (xt < 0 || xt > 7 || yt < 0 || yt > 7) {
			//menee yli
			break;
		}
		// ei mitääm tässä, tähän voi mennä
		if (asema->_lauta[xt][yt] == NULL) {
			lista.push_back(Siirto(*ruutu, Ruutu(xt, yt)));
		}
		//tässä nappula, katsotaan voiko syyä
		if (asema->_lauta[xt][yt] != NULL) {
			toisenvari = asema->_lauta[xt][yt]->getVari();
			//oma, ei voi syyä
			if (nappulanvari == toisenvari) {
				break;
			}
			//ei oma, voi syyä
			if (nappulanvari != toisenvari) {
				lista.push_back(Siirto(*ruutu, Ruutu(xt, yt)));
				break;
			}

		}
			
	}
	
	//siirrot ylävasen
	for (xt = x - 1, yt = y + 1; xt < 99; xt--, yt++) {
		if (xt < 0 || xt > 7 || yt < 0 || yt > 7) {
			//menee yli
			break;
		}
		// ei mitääm tässä, tähän voi mennä
		if (asema->_lauta[xt][yt] == NULL) {
			lista.push_back(Siirto(*ruutu, Ruutu(xt, yt)));
		}
		//tässä nappula, katsotaan voiko syyä
		if (asema->_lauta[xt][yt] != NULL) {
			toisenvari = asema->_lauta[xt][yt]->getVari();
			//oma, ei voi syyä
			if (nappulanvari == toisenvari) {
				break;
			}
			//ei oma, voi syyä
			if (nappulanvari != toisenvari) {
				lista.push_back(Siirto(*ruutu, Ruutu(xt, yt)));
				break;
			}

		}

	}

	//siirrot alaoikea
	for (xt = x + 1, yt = y - 1; xt < 99; xt++, yt--) {
		if (xt < 0 || xt > 7 || yt < 0 || yt > 7) {
			//menee yli
			break;
		}
		// ei mitääm tässä, tähän voi mennä
		if (asema->_lauta[xt][yt] == NULL) {
			lista.push_back(Siirto(*ruutu, Ruutu(xt, yt)));
		}
		//tässä nappula, katsotaan voiko syyä
		if (asema->_lauta[xt][yt] != NULL) {
			toisenvari = asema->_lauta[xt][yt]->getVari();
			//oma, ei voi syyä
			if (nappulanvari == toisenvari) {
				break;
			}
			//ei oma, voi syyä
			if (nappulanvari != toisenvari) {
				lista.push_back(Siirto(*ruutu, Ruutu(xt, yt)));
				break;
			}

		}

	}

	//siirrot alavasen
	for (xt = x - 1, yt = y - 1; xt < 99; xt--, yt--) {
		if (xt < 0 || xt > 7 || yt < 0 || yt > 7) {
			//menee yli
			break;
		}
		// ei mitääm tässä, tähän voi mennä
		if (asema->_lauta[xt][yt] == NULL) {
			lista.push_back(Siirto(*ruutu, Ruutu(xt, yt)));
		}
		//tässä nappula, katsotaan voiko syyä
		if (asema->_lauta[xt][yt] != NULL) {
			toisenvari = asema->_lauta[xt][yt]->getVari();
			//oma, ei voi syyä
			if (nappulanvari == toisenvari) {
				break;
			}
			//ei oma, voi syyä
			if (nappulanvari != toisenvari) {
				lista.push_back(Siirto(*ruutu, Ruutu(xt, yt)));
				break;
			}

		}

	}
}


void Daami::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	this->Lahetti::annaSiirrot(lista, ruutu, asema, vari);
	this->Torni::annaSiirrot(lista, ruutu, asema, vari);
}


void Kuningas::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	int y = ruutu->getRivi();
	int x = ruutu->getSarake();
	int nappulanvari = vari;
		//asema->_lauta[x][y]->getVari();
	// toisenvari siis loppuruudussa olevan nappulan väri
	int toisenvari;
	int xt, yt;
	

	//ylös
	xt = x;
	yt = y + 1;
	if(xt < 8 && xt > 0 && yt < 8 && yt > 0){
		if (asema->_lauta[xt][yt] == NULL) {
			//tyhjä, voi mennä
			lista.push_back(Siirto(*ruutu, Ruutu(xt, yt)));
		}
		else {
			if (nappulanvari == toisenvari) {
				
			}
			//ei oma, voi syyä
			if (nappulanvari != toisenvari) {
				lista.push_back(Siirto(*ruutu, Ruutu(xt, yt)));
			}

		}
	}

	//ylös oikealle
	xt = x + 1;
	yt = y + 1;
	if (xt < 8 && xt > 0 && yt < 8 && yt > 0) {
		if (asema->_lauta[xt][yt] == NULL) {
			//tyhjä, voi mennä
			lista.push_back(Siirto(*ruutu, Ruutu(xt, yt)));
		}
		else {
			if (nappulanvari == toisenvari) {
				
			}
			//ei oma, voi syyä
			if (nappulanvari != toisenvari) {
				lista.push_back(Siirto(*ruutu, Ruutu(xt, yt)));
			}

		}
	}

	//oikealle
	xt = x + 1;
	yt = y;
	if (xt < 8 && xt > 0 && yt < 8 && yt > 0) {
		if (asema->_lauta[xt][yt] == NULL) {
			//tyhjä, voi mennä
			lista.push_back(Siirto(*ruutu, Ruutu(xt, yt)));
		}
		else {
			if (nappulanvari == toisenvari) {
				
			}
			//ei oma, voi syyä
			if (nappulanvari != toisenvari) {
				lista.push_back(Siirto(*ruutu, Ruutu(xt, yt)));
			}

		}
	}

	//alas oikealle
	xt = x + 1;
	yt = y - 1;
	if (xt < 8 && xt > 0 && yt < 8 && yt > 0) {
		if (asema->_lauta[xt][yt] == NULL) {
			//tyhjä, voi mennä
			lista.push_back(Siirto(*ruutu, Ruutu(xt, yt)));
		}
		else {
			if (nappulanvari == toisenvari) {
				
			}
			//ei oma, voi syyä
			if (nappulanvari != toisenvari) {
				lista.push_back(Siirto(*ruutu, Ruutu(xt, yt)));
			}

		}
	}

	//alas
	xt = x;
	yt = y - 1;
	if (xt < 8 && xt > 0 && yt < 8 && yt > 0) {
		if (asema->_lauta[xt][yt] == NULL) {
			//tyhjä, voi mennä
			lista.push_back(Siirto(*ruutu, Ruutu(xt, yt)));
		}
		else {
			if (nappulanvari == toisenvari) {
				
			}
			//ei oma, voi syyä
			if (nappulanvari != toisenvari) {
				lista.push_back(Siirto(*ruutu, Ruutu(xt, yt)));
			}

		}
	}

	// alas vasemmalle
	xt = x - 1 ;
	yt = y - 1;
	if (xt < 8 && xt > 0 && yt < 8 && yt > 0) {
		if (asema->_lauta[xt][yt] == NULL) {
			//tyhjä, voi mennä
			lista.push_back(Siirto(*ruutu, Ruutu(xt, yt)));
		}
		else {
			if (nappulanvari == toisenvari) {
			}
			//ei oma, voi syyä

			if (nappulanvari != toisenvari) {
				lista.push_back(Siirto(*ruutu, Ruutu(xt, yt)));
			}

		}
	}

	//vasemmalle
	xt = x - 1;
	yt = y;
	if (xt < 8 && xt > 0 && yt < 8 && yt > 0) {
		if (asema->_lauta[xt][yt] == NULL) {
			//tyhjä, voi mennä
			lista.push_back(Siirto(*ruutu, Ruutu(xt, yt)));
		}
		else {
			if (nappulanvari == toisenvari) {
				//ei oma, voi syyä
			}

			if (nappulanvari != toisenvari) {
				lista.push_back(Siirto(*ruutu, Ruutu(xt, yt)));
			}

		}
	}

	//ylös vasemmalle
	xt = x -1;
	yt = y + 1;
	if (xt < 8 && xt > 0 && yt < 8 && yt > 0) {
		if (asema->_lauta[xt][yt] == NULL) {
			//tyhjä, voi mennä
			lista.push_back(Siirto(*ruutu, Ruutu(xt, yt)));
		}
		else {
			if (nappulanvari == toisenvari) {
				
			}
			//ei oma, voi syyä
			if (nappulanvari != toisenvari) {
				lista.push_back(Siirto(*ruutu, Ruutu(xt, yt)));
			}

		}
	}



}


void Sotilas::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	int y = ruutu->getRivi();
	int x = ruutu->getSarake();
	int nappulanvari = vari;
		//asema->_lauta[x][y]->getVari();
	// toisenvari siis loppuruudussa olevan nappulan väri
	int toisenvari;

	//alun kaksoisaskeleet
	if (y == 1 && nappulanvari == 0) {
		
		if (asema->_lauta[x][2] == NULL && asema->_lauta[x][3] == NULL) {
			lista.push_back(Siirto(*ruutu, Ruutu(x, y + 2)));
		}
		
	}
	if (y == 6 && nappulanvari == 0) {

		if (asema->_lauta[x][2] == NULL && asema->_lauta[x][4] == NULL) {
			lista.push_back(Siirto(*ruutu, Ruutu(x, y - 2)));
		}

	}

	//valkeiden siirtoja 
	if (y > 1 && y < 7 && nappulanvari == 0) {
		//siirrot yks eteenpäin, checkataan onko tiellä jotain
		if (asema->_lauta[x][y + 1] == NULL) {

				lista.push_back(Siirto(*ruutu, Ruutu(x, y + 1)));
		}
		//syömisiä
		if (x < 7) {
			if (asema->_lauta[x + 1][y + 1] != NULL) {
				toisenvari = asema->_lauta[x + 1][y + 1]->getVari();
				if (toisenvari != nappulanvari) {
						lista.push_back(Siirto(*ruutu, Ruutu(x + 1, y + 1)));
				}
			}
		}
		//ohestalyönti valkea
		if (vari == 0 && y == 4 && asema->kaksoisaskelSarakkeella != -1) {
			if (asema->_lauta[asema->kaksoisaskelSarakkeella][4] && asema->_lauta[asema->kaksoisaskelSarakkeella][4]->getKoodi() == MS)
				lista.push_back(Siirto(*ruutu, Ruutu(asema->kaksoisaskelSarakkeella, 5)));
		}
		
	}
	//mustien siirtoja 
	if (y > 1 && y < 7 && nappulanvari == 1) {
		//siirrot yks eteenpäin, checkataan onko tiellä jotain
		if (asema->_lauta[x][y - 1] == NULL) {

			lista.push_back(Siirto(*ruutu, Ruutu(x, y - 1)));
		}
		//syömisiä
		if (x < 7) {
			if (asema->_lauta[x - 1][y - 1] != NULL) {
				toisenvari = asema->_lauta[x - 1][y - 1]->getVari();
				if (toisenvari != nappulanvari) {
					lista.push_back(Siirto(*ruutu, Ruutu(x - 1, y - 1)));
				}
			}
		}
		//ohestalyönti musta
		if (vari == 1 && y == 3 && asema->kaksoisaskelSarakkeella != -1) {
			if (asema->_lauta[asema->kaksoisaskelSarakkeella][4] && asema->_lauta[asema->kaksoisaskelSarakkeella][4]->getKoodi() == VS)
				lista.push_back(Siirto(*ruutu, Ruutu(asema->kaksoisaskelSarakkeella, 3)));
		}

	}
}


void Sotilas::lisaaSotilaanKorotukset(Siirto* siirto, std::list<Siirto>& lista, Asema* asema) {

}
