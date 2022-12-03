#include <iostream>
#include "util.h"

using namespace std;

int main () {
	int entero;
	float flotante;
	double doble;
	int edad;
	util::setConfig(true, true, true);

	cout << "Este es un mensaje" << endl;
	util::pause();
	util::borrarPantalla();
	cout << "Leyendo informacion de configuracion";
	cout << "Plataforma: " << ((util::CONF.readBool("isWin")) ? "windows" : "linux") << endl;
	cout << "Edad Legal: " << util::CONF.readInt("edadLegal") << endl;
	cout << "Valor de PI: " << util::CONF.readFloat("PI") << endl;
	cout << "Un Double: " << util::CONF.readDouble("doble") << endl;
	cout << "Author: " << (util::CONF.readString("nombre") + util::CONF.readChar("separator") + util::CONF.readString("apellido")) << endl;
	util::pause();
	util::borrarPantalla();

	util::CONF.writeBool("willClear", false);
	util::CONF.writeInt("edadLegal", 20);
	util::CONF.writeFloat("PI", 3);
	util::CONF.writeDouble("doble", 2*util::CONF.readFloat("PI"));
	util::CONF.writeString("nombre", "Yolvan G.");

	cout << "Leyendo informacion de configuracion";
	cout << "Plataforma: " << ((util::CONF.readBool("isWin")) ? "windows" : "linux") << endl;
	cout << "Edad Legal: " << util::CONF.readInt("edadLegal") << endl;
	cout << "Valor de PI: " << util::CONF.readFloat("PI") << endl;
	cout << "Un Double: " << util::CONF.readDouble("doble") << endl;
	cout << "Author: " << (util::CONF.readString("nombre") + util::CONF.readChar("separator") + util::CONF.readString("apellido")) << endl;
	util::pause();
}