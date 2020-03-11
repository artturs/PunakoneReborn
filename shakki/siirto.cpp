#include "siirto.h"

#pragma optimize("g", on)

Siirto::Siirto(Ruutu alkuRuutu, Ruutu loppuRuutu) {
	this->_alkuRuutu = alkuRuutu;
	this->_loppuRuutu = loppuRuutu;
	this->_lyhytLinna = false;
	this->_pitkaLinna = false;
}

Siirto::Siirto(bool lyhytLinna, bool pitkaLinna) {
	this->_lyhytLinna = lyhytLinna;
	this->_pitkaLinna = pitkaLinna;
}

Ruutu Siirto::getAlkuruutu() {
	return _alkuRuutu;
}
Ruutu Siirto::getLoppuruutu() {
	return _loppuRuutu;
}
bool Siirto::onkoLyhytLinna() {
	return this->_lyhytLinna;
}
bool Siirto::onkoPitkaLinna() {
	return this->_pitkaLinna;
}
