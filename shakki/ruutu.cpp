#include "ruutu.h"


Ruutu::Ruutu(int rivi, int sarake) {
	this->rivi = rivi;
	this->sarake = sarake;
}
int Ruutu::getSarake() {
	return sarake;
}
int Ruutu::getRivi() {
	return rivi;
}
void Ruutu::setRivi(int rivi)
{
	this->rivi = rivi;
}


void Ruutu::setSarake(int sarake)
{
	this->sarake = sarake;
}



