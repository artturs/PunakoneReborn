#pragma once

#include <list>
#include <string>
#include "asema.h"


// Vakioarvot nappulatyypeille.
enum
{
	VT,VR,VL,VD,VK,VS,
	MT,MR,ML,MD,MK,MS
};


// Yliluokka shakkinappuloille.
class Nappula
{

private:
	std::wstring	_unicode;	// nappulaa vastaava unicode-merkki
	int				_vari;		// valkea = 0, musta = 1
	int				_koodi;		// VT, VR, MT tms.

public:
	Nappula(std::wstring unicode, int vari, int koodi)
	{
		_unicode = unicode;
		_vari = vari;
		_koodi = koodi;
	}
	Nappula() {}

	void setUnicode(std::wstring unicode)	{ _unicode = unicode;			}
	std::wstring getUnicode()				{ return _unicode;				}
	void setVari(int vari)					{ _vari = vari;					}
	int getVari()							{ return _vari;					}
	int getKoodi()							{ return _koodi;				}
	void setKoodi(int koodi)				{ _koodi = koodi;				}
};
