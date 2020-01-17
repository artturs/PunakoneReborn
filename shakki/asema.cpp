#include <iostream>
#include "asema.h"
#include "nappula.h"

Nappula* Asema::vk = new Nappula(L"\u2654", 0, VK);
Nappula* Asema::vd = new Nappula(L"\u2655", 0, VD);
Nappula* Asema::vt = new Nappula(L"\u2656", 0, VT);
Nappula* Asema::vl = new Nappula(L"\u2657", 0, VL);
Nappula* Asema::vr = new Nappula(L"\u2658", 0, VR);
Nappula* Asema::vs = new Nappula(L"\u2659", 0, VS);

Nappula* Asema::mk = new Nappula(L"\u265A", 1, MK);
Nappula* Asema::md = new Nappula(L"\u265B", 1, MD);
Nappula* Asema::mt = new Nappula(L"\u265C", 1, MT);
Nappula* Asema::ml = new Nappula(L"\u265D", 1, ML);
Nappula* Asema::mr = new Nappula(L"\u265E", 1, MR);
Nappula* Asema::ms = new Nappula(L"\u265F", 1, MS);


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
	_lauta[0][1] = vs;
	_lauta[1][1] = vs;
	_lauta[2][1] = vs;
	_lauta[3][1] = vs;
	_lauta[4][1] = vs;
	_lauta[5][1] = vs;
	_lauta[6][1] = vs;
	_lauta[7][1] = vs;
	_lauta[0][0] = vt;
	_lauta[1][0] = vr;
	_lauta[2][0] = vl;
	_lauta[3][0] = vd;
	_lauta[4][0] = vk;
	_lauta[5][0] = vl;
	_lauta[6][0] = vr;
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
	_lauta[3][7] = md;
	_lauta[4][7] = mk;
	_lauta[5][7] = ml;
	_lauta[6][7] = mr;
	_lauta[7][7] = mt;
	
}
