#include <iostream>
#include "util.h"

using namespace std;

int main () {
	int entero;
	float flotante;
	double doble;
	// util::setConfig(false, true, true);

	cout << "Estoy en " << ((util::CONF.win()) ? "windows" : "linux") << endl;
	cout << "Este es un mensaje" << endl;
	util::pause();
	util::borrarPantalla();
	entero = util::inputNumber<int>("Ingrese un numero entero: ", 20);
	flotante = util::inputNumber<float>("Ingrese un numero flotante: ");
	doble = util::inputNumber<double>("Ingrese un numero doble: ", 20.005, 0.0001);

	cout << entero << " + " << flotante << " = " << (entero + flotante) << endl;
	cout << doble << " - " << flotante << " = " << (doble - flotante) << endl;
	cout << doble << " * " << 2 << " = " << (doble * 2) << endl;
	util::pause();
}