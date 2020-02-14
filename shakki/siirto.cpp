#include "siirto.h"

Siirto::Siirto(Ruutu alkuRuutu, Ruutu loppuRuutu) {
	this->_alkuRuutu = alkuRuutu;
	this->_loppuRuutu = loppuRuutu;
	this->_lyhytLinna = false;
	this->_pitkaLinna = false;
	this->_mahdollinen = true;
}

Siirto::Siirto(bool lyhytLinna, bool pitkaLinna, bool mahdollinen) {
	this->_lyhytLinna = lyhytLinna;
	this->_pitkaLinna = pitkaLinna;
	this->_mahdollinen = mahdollinen;
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
bool Siirto::onkoMahdollinen() {
	return this->_mahdollinen;
}
