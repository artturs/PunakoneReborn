#include "minMaxPaluu.h"


// Minimax-funktio pelipuun generoimiseksi ja l‰pik‰ymiseksi,
// alkaen nykyisest‰ asemasta (this).
//
// parametri: syvyys - kuinka syv‰lle pelipuuta tutkitaan
// paluuarvo: MinMaxPaluu-objekti, josta lˆytyy aseman
//            minimax-arvo ja aseman paras siirto
//
// Funktion edellytt‰‰, ett‰ ainakin seuraavat komponentit
// on toteutettu:
//
// 1) siirtogeneraattori - Asema::annaLaillisetSiirrot() tms.
// 2) evaluointifunktio  - Asema::evaluoi() tms.
// 3) tapa tarkistaa, onko siirtovuoroisen pelaajan kuningas uhattu
//
// Esimerkki: P‰‰ohjelmassa yll‰pidet‰‰n nykyist‰ asemaa a.
//            Kun halutaan tiet‰‰ mit‰ tietokone siirt‰isi
//            asemassa a, tehd‰‰n kutsu (katkaisusyvyys 4):
//
//                 MinMaxPaluu mma = a.minimax(4);
//
//            Tietokoneen valitsema siirto lˆytyy t‰m‰n j‰lkeen
//
//                 Siirto s = mma._parasSiirto;
//
MinMaxPaluu Asema::minimax(int syvyys)
{
	}