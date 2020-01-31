#pragma once
class Ruutu {
public:
	Ruutu(int rivi, int sarake);
	Ruutu() {}
	int getRivi();
	int getSarake();
private:
	int sarake;
	int rivi;
};
class Siirto {
public:
	Siirto(Ruutu, Ruutu);
	Siirto() {}
	Siirto(bool lyhytLinna, bool pitkaLinna); // Poikkeussiirto linnoitusta varten
	Ruutu getAlkuruutu();
	Ruutu getLoppuruutu();
	bool onkoLyhytLinna();
	bool onkoPitkalinna();
private:
	Ruutu alkuRuutu;
	Ruutu loppuRuutu;
	int miksiKorotetaan = 0;
	bool lyhytLinna;
	bool pitkalinna;
};
